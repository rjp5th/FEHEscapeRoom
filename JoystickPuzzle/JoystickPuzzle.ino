#include "JoystickPasscode.h"

JoystickPasscode *passcodeControl;

void setup() {
  passcodeControl = new JoystickPasscode();
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  // Wait for input
  passcodeControl->waitAndProcessAction();
  Serial.println("Item Entered");

  // Check if the passcode sequence is complete
  if (passcodeControl->sequenceCompleted()) {
    if (passcodeControl->sequenceCorrect()) {
      Serial.println("Passcode Correct!");
    } else {
      Serial.println("Invalid Password");
    }
    passcodeControl->resetSequence();
  }
}
