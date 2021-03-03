#include "JoystickPasscode.h"

#include "Arduino.h"

#define MIN_JOYSTICK_DIRECTION 0.7
#define MAX_JOYSTICK_DEVIATION 0.2

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1

JoystickPasscode::JoystickPasscode() {
  this->sequenceIndex = 0;
}

/*
 * Reads the current state of the joystick as an action type
 */
int JoystickPasscode::readJoystickAction() {
  // Normalize joystick values from analog reading to value from -1 to 1
  double joyXNorm = (analogRead(JOYSTICK_X_PIN) / 1024.0) * 2 - 1;
  double joyYNorm = (analogRead(JOYSTICK_Y_PIN) / 1024.0) * 2 - 1;

  if (joyXNorm > MIN_JOYSTICK_DIRECTION && abs(joyYNorm) < MAX_JOYSTICK_DEVIATION) {
    return LEFT_PRESS;
  } else if (joyXNorm < -MIN_JOYSTICK_DIRECTION && abs(joyYNorm) < MAX_JOYSTICK_DEVIATION) {
    return RIGHT_PRESS;
  } else if (joyYNorm > MIN_JOYSTICK_DIRECTION && abs(joyXNorm) < MAX_JOYSTICK_DEVIATION) {
    return UP_PRESS;
  } else if (joyYNorm < -MIN_JOYSTICK_DIRECTION && abs(joyXNorm) < MAX_JOYSTICK_DEVIATION) {
    return DOWN_PRESS;
  } else {
    return NO_PRESS;
  }
}

/*
 * Wait until joystick action is completed, then store action into passcode
 */
void JoystickPasscode::waitAndProcessAction() {
  
  // Wait for action on joystick
  int action = NO_PRESS;
  while (action == NO_PRESS){
    action = this->readJoystickAction();
  }

  // Debug log the current action done
  Serial.print("Sequence ");
  switch(action){
    case RIGHT_PRESS:
      Serial.print("RIGHT_PRESS");
      break;
    case LEFT_PRESS:
      Serial.print("LEFT_PRESS");
      break;
    case UP_PRESS:
      Serial.print("UP_PRESS");
      break;
    case DOWN_PRESS:
      Serial.print("DOWN_PRESS");
      break;
    default:
      Serial.print(action);
  }
  Serial.print(": ");

  // If there is enough space in the buffer, store the action
  if (this->sequenceIndex < SEQUENCE_SIZE) {
    this->inputSequence[this->sequenceIndex] = action;
    this->sequenceIndex++;
  }

  // Wait until the joystick is back to normal before returning
  while (this->readJoystickAction() != NO_PRESS) {}
}

/*
 * Returns if there are enough actions is buffer to satisfy sequence passcode
 */
bool JoystickPasscode::sequenceCompleted() {
  return this->sequenceIndex == SEQUENCE_SIZE;
}

/*
 * Clear the sequence data in the class
 */
void JoystickPasscode::resetSequence() {
  this->sequenceIndex = 0;
}

/*
 * Check if the entered sequence is valid
 */
bool JoystickPasscode::sequenceCorrect() {
  if (this->sequenceIndex != SEQUENCE_SIZE) {
    return false;
  }

  for (int i = 0; i < SEQUENCE_SIZE; i++) {
    if (this->inputSequence[i] != validSequence[i]) {
      return false;
    }
  }

  return true;
}
