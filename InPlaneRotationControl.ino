#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "InPlaneRotationController";
const char* password = "microscopy123";

// L9110H
const int pinIA = D1;
const int pinIB = D2;

// Buttons connect to GND when pressed.
const int btnCW = D7;
const int btnCCW = D6;

const int potPin = A0;
const bool REVERSE_MOTOR = true;

const int PWM_MAX = 1023;
const int MIN_SPEED_PERCENT = 15;
// Round upward so the minimum duty is never below 15%.
const int MIN_PWM = (PWM_MAX * MIN_SPEED_PERCENT + 99) / 100;
const unsigned long DEBOUNCE_MS = 25;
const unsigned long REVERSAL_MS = 20;

ESP8266WebServer server(80);

// Web control is OFF at startup.
bool webEnabled = false;

bool webCW = false;
bool webCCW = false;
int webSpeed = 100;

int appliedDirection = 0;
int appliedDuty = 0;
int lastDrivenDirection = 0;
unsigned long stoppedAt = 0;

// Button states
bool rawCW = false;
bool rawCCW = false;
bool stableCW = false;
bool stableCCW = false;

unsigned long cwChangedAt = 0;
unsigned long ccwChangedAt = 0;

// Require released buttons after startup or a mode change.
bool waitForRelease = true;

// Potentiometer
int filteredPot = 0;
unsigned long lastPotRead = 0;

// ---------------- Motor ----------------

void stopMotor() {
  analogWrite(pinIA, 0);
  analogWrite(pinIB, 0);

  if (appliedDirection != 0) {
    stoppedAt = millis();
  }

  appliedDirection = 0;
  appliedDuty = 0;
}

void driveMotor(int direction, int duty) {
  if (direction == 0 || duty == 0) {
    if (appliedDirection != 0 || appliedDuty != 0) {
      stopMotor();
    }
    return;
  }

  if (appliedDirection != 0 &&
      appliedDirection != direction) {
    stopMotor();
  }

  // Brief pause before reversing.
  if (lastDrivenDirection != 0 &&
      lastDrivenDirection != direction &&
      (unsigned long)(millis() - stoppedAt) < REVERSAL_MS) {
    return;
  }

  if (appliedDirection == direction && appliedDuty == duty) {
    return;
  }

  int electricalDirection =
      REVERSE_MOTOR ? -direction : direction;

  if (electricalDirection == 1) {
    analogWrite(pinIB, 0);
    analogWrite(pinIA, duty);
  } else {
    analogWrite(pinIA, 0);
    analogWrite(pinIB, duty);
  }

  appliedDirection = direction;
  appliedDuty = duty;
  lastDrivenDirection = direction;
}

// ---------------- Physical inputs ----------------

void readPhysicalInputs() {
  unsigned long now = millis();

  bool sampleCW = digitalRead(btnCW) == LOW;
  bool sampleCCW = digitalRead(btnCCW) == LOW;

  if (sampleCW != rawCW) {
    rawCW = sampleCW;
    cwChangedAt = now;
  }

  if (sampleCCW != rawCCW) {
    rawCCW = sampleCCW;
    ccwChangedAt = now;
  }

  if ((unsigned long)(now - cwChangedAt) >= DEBOUNCE_MS) {
    stableCW = rawCW;
  }

  if ((unsigned long)(now - ccwChangedAt) >= DEBOUNCE_MS) {
    stableCCW = rawCCW;
  }

  if (waitForRelease &&
      !rawCW && !rawCCW &&
      !stableCW && !stableCCW) {
    waitForRelease = false;
  }

  if ((unsigned long)(now - lastPotRead) >= 20) {
    lastPotRead = now;
    filteredPot = (3 * filteredPot + analogRead(potPin)) / 4;
  }
}

int physicalSpeed() {
  // Keep the existing endpoint dead zones, but map the knob to 15-100%.
  int reading = constrain(filteredPot, 12, 1010);
  return map(reading, 12, 1010, MIN_PWM, PWM_MAX);
}

void updateMotor() {
  // Both physical buttons stop motion even when web control is enabled.
  // Clear web selections so releasing the buttons cannot restart web motion.
  if (stableCW && stableCCW) {
    webCW = webCCW = false;
    waitForRelease = true;
    stopMotor();
    return;
  }

  if (webEnabled) {
    // Both selected or neither selected means STOP.
    int direction = (webCW == webCCW) ? 0 : (webCW ? 1 : -1);
    int duty = (webSpeed * PWM_MAX + 99) / 100;
    driveMotor(direction, duty);
    return;
  }

  int direction = 0;
  if (!waitForRelease) {
    if (stableCW && !stableCCW) direction = 1;
    if (stableCCW && !stableCW) direction = -1;
  }
  driveMotor(direction, physicalSpeed());
}

// ---------------- Web handlers ----------------

void handleMode() {
  String value = server.arg("enabled");

  if (value != "1" && value != "0") {
    server.send(400, "text/plain", "Invalid mode");
    return;
  }

  bool newMode = value == "1";

  if (newMode != webEnabled) {
    stopMotor();
    webCW = webCCW = false;
    webEnabled = newMode;
    waitForRelease = true;
  }

  server.send(200, "text/plain", "OK");
}

void handleDirection() {
  if (!webEnabled) {
    server.send(403, "text/plain", "Web control is OFF");
    return;
  }

  String value = server.arg("value");

  if (value == "cw") {
    webCW = !webCW;
    webCCW = false;
  } else if (value == "ccw") {
    webCCW = !webCCW;
    webCW = false;
  } else if (value == "stop") {
    webCW = webCCW = false;
  } else {
    server.send(400, "text/plain", "Invalid direction");
    return;
  }

  updateMotor();
  server.send(200, "text/plain", "OK");
}

void handleSpeed() {
  if (!webEnabled) {
    server.send(403, "text/plain", "Web control is OFF");
    return;
  }

  String value = server.arg("value");

  if (value.length() == 0 || value.length() > 3) {
    server.send(400, "text/plain", "Invalid speed");
    return;
  }

  for (unsigned int i = 0; i < value.length(); i++) {
    if (value[i] < '0' || value[i] > '9') {
      server.send(400, "text/plain", "Invalid speed");
      return;
    }
  }

  int percent = value.toInt();

  if (percent < MIN_SPEED_PERCENT || percent > 100) {
    server.send(400, "text/plain", "Speed must be 15-100%; lower settings are disabled to reduce motor stalling.");
    return;
  }

  webSpeed = percent;
  updateMotor();
  server.send(200, "text/plain", "OK");
}

void handleStatus() {
  String json = "{\"webEnabled\":";
  json += webEnabled ? "true" : "false";
  json += ",\"webCW\":";
  json += webCW ? "true" : "false";
  json += ",\"webCCW\":";
  json += webCCW ? "true" : "false";
  json += ",\"direction\":" + String(appliedDirection);
  json += ",\"webSpeed\":" + String(webSpeed);
  json += ",\"appliedSpeed\":";
  json += String((appliedDuty * 100 + 511) / PWM_MAX);
  json += "}";

  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", json);
}

// ---------------- Webpage ----------------

const char webpage[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>In-plane Rotation Control</title>
<style>
  body {
    font-family: sans-serif;
    text-align: center;
    max-width: 550px;
    margin: auto;
    padding: 30px 12px;
  }

  button {
    font-size: 22px;
    padding: 16px 26px;
    margin: 8px;
    border: 1px solid #555;
    border-radius: 8px;
    cursor: pointer;
  }

  button:disabled { opacity: 0.4; }
  button.active { background: #34874a; color: white; }
  #speedWarning { color: #9b3d00; min-height: 1.3em; font-size: 0.9rem; }
  input[type=range] { width: 85%; }
  #error { color: #b22222; }
  fieldset { border: none; }

  .switch {
    position: relative;
    display: inline-block;
    width: 56px;
    height: 30px;
    vertical-align: middle;
    margin: 10px;
  }

  .switch input {
    opacity: 0;
    width: 0;
    height: 0;
  }

  .track {
    position: absolute;
    inset: 0;
    background: #aaa;
    border-radius: 30px;
    cursor: pointer;
  }

  .track::before {
    content: "";
    position: absolute;
    width: 24px;
    height: 24px;
    left: 3px;
    top: 3px;
    background: white;
    border-radius: 50%;
    transition: transform 0.2s;
  }

  input:checked + .track { background: #34874a; }
  input:checked + .track::before { transform: translateX(26px); }
  input:focus-visible + .track { outline: 3px solid #2456b5; }
</style>
</head>
<body>
<h2>Specimen Holder Rotation</h2>

<label class="switch">
  <input id="mode" type="checkbox"
         aria-label="Enable web control" disabled>
  <span class="track"></span>
</label>
<strong id="modeLabel">Connecting...</strong>

<p id="description"></p>

<fieldset id="controls" disabled>
  <button id="cw" aria-pressed="false" onclick="setDirection('cw')">CW</button>
  <button id="ccw" aria-pressed="false" onclick="setDirection('ccw')">CCW</button>

  <h3>Speed: <span id="speedValue">100</span>%</h3>
  <!-- The lower part of the track detects attempts below 15%; the value
       is immediately clamped and the server also enforces the limit. -->
  <input id="speed" aria-label="Speed" type="range" min="0" max="100" value="100">
  <p id="speedWarning" role="status" aria-live="polite"></p>
</fieldset>

<p id="status"></p>
<p id="error"></p>

<script>
const mode = document.getElementById('mode');
const controls = document.getElementById('controls');
const slider = document.getElementById('speed');
const speedValue = document.getElementById('speedValue');
const errorText = document.getElementById('error');

let pending = 0;
let polling = false;
let editingSpeed = false;
let revision = 0;
let commandQueue = Promise.resolve();

function displayState(state) {
  mode.disabled = false;
  for (const name of ['cw', 'ccw']) {
    const selected = name === 'cw' ? state.webCW : state.webCCW;
    const button = document.getElementById(name);
    button.classList.toggle('active', selected);
    button.setAttribute('aria-pressed', String(selected));
  }
  mode.checked = state.webEnabled;
  controls.disabled = !state.webEnabled;

  document.getElementById('modeLabel').textContent =
    state.webEnabled ? 'Web control ON' : 'Web control OFF';

  document.getElementById('description').textContent =
    state.webEnabled
      ? 'Use the webpage to control direction and speed.'
      : 'Use the physical buttons and potentiometer.';

  document.getElementById('status').textContent =
    (state.direction === 1 ? 'Running CW' :
     state.direction === -1 ? 'Running CCW' : 'Stopped') +
    ' | Applied PWM: ' + state.appliedSpeed + '%';

  if (!editingSpeed) {
    slider.value = state.webSpeed;
    speedValue.textContent = state.webSpeed;
  }
}

async function refresh() {
  if (polling || pending) return;

  polling = true;
  const currentRevision = revision;

  try {
    const response = await fetch('/status', {cache: 'no-store'});
    if (!response.ok) throw new Error('Status unavailable');

    const state = await response.json();

    // Ignore a status response made stale by a new command.
    if (currentRevision === revision && !pending) {
      displayState(state);
    }
  } catch (error) {
    if (currentRevision === revision && !pending) {
      mode.disabled = true;
      controls.disabled = true;
      document.getElementById('status').textContent =
        'Connection lost — motor state unknown.';
    }
  } finally {
    polling = false;
  }
}

// Serialize commands so rapid clicks arrive in their original order.
function sendCommand(path, data) {
  pending++;
  revision++;
  const task = commandQueue.then(async () => {
    try {
      const response = await fetch(path, {
        method: 'POST',
        headers: {'Content-Type': 'application/x-www-form-urlencoded'},
        body: new URLSearchParams(data)
      });
      if (!response.ok) throw new Error(await response.text());
      errorText.textContent = '';
    } catch (error) {
      errorText.textContent = 'Command failed: ' + error.message;
    } finally {
      pending--;
      refresh();
    }
  });
  commandQueue = task.catch(() => {});
  return task;
}

mode.onchange = async () => {
  const enabled = mode.checked ? '1' : '0';
  mode.disabled = true;
  controls.disabled = true;
  await sendCommand('/mode', {enabled});
};

function setDirection(value) {
  sendCommand('/direction', {value});
}

function clampSpeed() {
  const belowMinimum = Number(slider.value) < 15;
  document.getElementById('speedWarning').textContent = belowMinimum
    ? 'Speeds below 15% are disabled to reduce the risk of motor stalling.'
    : '';
  slider.value = Math.max(15, Number(slider.value));
  speedValue.textContent = slider.value;
}

slider.oninput = () => {
  editingSpeed = true;
  clampSpeed();
};

slider.onchange = async () => {
  const value = String(Math.max(15, Number(slider.value)));
  await sendCommand('/speed', {value});
  editingSpeed = false;
  refresh();
};

setInterval(refresh, 300);
refresh();
</script>
</body>
</html>
)HTML";

// ---------------- Setup ----------------

void setup() {
  pinMode(pinIA, OUTPUT);
  pinMode(pinIB, OUTPUT);
  digitalWrite(pinIA, LOW);
  digitalWrite(pinIB, LOW);

  analogWriteRange(PWM_MAX);
  analogWriteFreq(1000);

  pinMode(btnCW, INPUT_PULLUP);
  pinMode(btnCCW, INPUT_PULLUP);

  rawCW = stableCW = digitalRead(btnCW) == LOW;
  rawCCW = stableCCW = digitalRead(btnCCW) == LOW;

  filteredPot = analogRead(potPin);

  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.print("Open http://");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", webpage);
  });

  server.on("/mode", HTTP_POST, handleMode);
  server.on("/direction", HTTP_POST, handleDirection);
  server.on("/speed", HTTP_POST, handleSpeed);
  server.on("/status", HTTP_GET, handleStatus);

  server.begin();
}

void loop() {
  readPhysicalInputs();
  server.handleClient();
  updateMotor();
  yield();
}