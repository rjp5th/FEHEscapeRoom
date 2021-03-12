#include "PhotoresistorPasscode.h"

PhotoresistorPasscode::PhotoresistorPasscode() {
  // Initialize Pin states
  pinMode(RESET_PIN, INPUT_PULLUP);
  SEVEN_SEGMENT_DIR |= SEVEN_SEGMENT_MASK;  // Set all pins for 7 segment display to output, preserve others

  this->resetSequence();
}

void PhotoresistorPasscode::resetSequence() {
  this->enteredNotes.pin_value = 0;
  this->sequenceIndex = 0;
}

void PhotoresistorPasscode::updateState() {
  if (digitalRead(RESET_PIN) == LOW) {
    this->resetSequence();
  } else {
    // Iterate through all pins to check if there are any pins that have been changed
    for (int i = 0; i < PIN_COUNT; i++) {
      
      // If the note hasn't been entered yet
      if (!((this->enteredNotes.pin_value >> (2+i)) & 1)) {
  
        // Check if the photoresistor is blocked
        int pinReading = analogRead(analogPinMappings[i]);
        if (pinReading < threshold_values[i]) {
          // Set the pin to be pressed
          this->enteredNotes.pin_value |= (1<<(2+i));
  
          // Record the pressed item
          this->inputSequence[this->sequenceIndex] = i;
          this->sequenceIndex++;
  
          // Play the sound
          tone(BUZZER_PIN, toneMapping[i], TONE_DURATION);
        }
      }
    }
  }

  // Output the state of the seven segment display
  SEVEN_SEGMENT_PORT = (SEVEN_SEGMENT_PORT & 0b11) | (this->enteredNotes.pin_value & SEVEN_SEGMENT_MASK);
}

bool PhotoresistorPasscode::sequenceCompleted() {
  return this->sequenceIndex == PIN_COUNT;
}

bool PhotoresistorPasscode::sequenceCorrect() {
  if (this->sequenceIndex != PIN_COUNT) {
    return false;
  }

  for (int i = 0; i < PIN_COUNT; i++) {
    if (this->inputSequence[i] != validSequence[i]) {
      return false;
    }
  }

  return true;
}
