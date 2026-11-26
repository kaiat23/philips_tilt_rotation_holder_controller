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

// Require released buttons after startup or a two-button stop.
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
  if (stableCW && stableCCW) {
    waitForRelease = true;
  }

  int direction = 0;
  if (!waitForRelease) {
    if (stableCW) direction = 1;
    if (stableCCW) direction = -1;
  }
  driveMotor(direction, physicalSpeed());
}

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
}

void loop() {
  readPhysicalInputs();
  updateMotor();
  yield();
}