#include "JoystickPasscode.h"
#include "NextClueMusic.h"
#include "LEDControl.h"

JoystickPasscode *passcodeControl;
NextClueMusic *toneControl;
LEDControl *ledControl;

void setup() {
  passcodeControl = new JoystickPasscode();
  toneControl = new NextClueMusic();
  ledControl = new LEDControl();

  Serial.begin(9600);  
  Serial.println("Ready!");
}

void loop() {
  // Wait for input
  if (passcodeControl->waitAndProcessAction()) {
    ledControl->displayEntry(true);
    toneControl->playEntryChirp();
    ledControl->displayEntry(false);
  } else {
    ledControl->displayTimeout(true);
    toneControl->playTimeoutChirp();
    ledControl->displayTimeout(false);
  }
  Serial.println("Item Entered");

  // Check if the passcode sequence is complete
  if (passcodeControl->sequenceCompleted()) {
    if (passcodeControl->sequenceCorrect()) {
      Serial.println("Passcode Correct!");
      ledControl->displayCorrect(true);
      toneControl->playSuccess();
      ledControl->displayCorrect(false);
    } else {
      Serial.println("Invalid Password");
      ledControl->displayIncorrect(true);
      toneControl->playFailure();
      ledControl->displayIncorrect(false);
    }
    passcodeControl->resetSequence();
  }
}
