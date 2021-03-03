#include "JoystickPasscode.h"
#include "NextClueMusic.h"

JoystickPasscode *passcodeControl;
NextClueMusic *toneControl;

void setup() {
  passcodeControl = new JoystickPasscode();
  toneControl = new NextClueMusic();
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  // Wait for input
  passcodeControl->waitAndProcessAction();
  toneControl->playEntryChirp();
  Serial.println("Item Entered");

  // Check if the passcode sequence is complete
  if (passcodeControl->sequenceCompleted()) {
    if (passcodeControl->sequenceCorrect()) {
      Serial.println("Passcode Correct!");
      toneControl->playSuccess();
    } else {
      Serial.println("Invalid Password");
      toneControl->playFailure();
    }
    passcodeControl->resetSequence();
  }
}
