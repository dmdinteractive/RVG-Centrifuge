// =====================================================================
// RVG CENTRIFUGE LOCK TEST
// Purpose: exercise the cabinet lock relay without the motor or lid switch.
// Press the start button (I/O-1) to energize the lock relay and unlock.
// Release the start button to re-lock.
// =====================================================================

#include "ClearCore.h"

#define lockRelay   ConnectorIO0
#define startButton ConnectorIO1

const uint16_t INPUT_FILTER_MS = 20;

void lockLid() {
  lockRelay.State(false);
  Serial.println("LOCK: ENGAGED");
}

void unlockLid() {
  lockRelay.State(true);
  Serial.println("LOCK: UNLOCKED");
}

void setup() {
  Serial.begin(9600);
  unsigned long serialWaitStart = millis();
  while (!Serial && millis() - serialWaitStart < 3000) {
    // wait briefly for USB serial if connected
  }

  lockRelay.Mode(Connector::OUTPUT_DIGITAL);
  startButton.Mode(Connector::INPUT_DIGITAL);
  startButton.FilterLength(INPUT_FILTER_MS, DigitalIn::FILTER_UNIT_MS);

  lockLid();

  Serial.println("=================================");
  Serial.println("Lock test sketch loaded");
  Serial.println("Press and hold START to unlock the lock");
  Serial.println("Release START to re-lock");
  Serial.println("=================================");
}

void loop() {
  bool buttonPressed = startButton.State();

  if (buttonPressed) {
    unlockLid();
  } else {
    lockLid();
  }

  delay(50);
}
