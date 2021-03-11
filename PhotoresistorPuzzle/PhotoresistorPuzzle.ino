#include "PhotoresistorPasscode.h"

#define SERVO_CLOSE_ANGLE 20
#define SERVO_OPEN_ANGLE 90

PhotoresistorPasscode* photoresPasscode;

void setup() {
  photoresPasscode = new PhotoresistorPasscode();
  Serial.begin(9600);
  Serial.println("Ready!");
}

void loop() {
  
}
