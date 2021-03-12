#include "PhotoresistorPasscode.h"
#include <Servo.h>

Servo servo;

#define SERVO_CLOSE_ANGLE 120
#define SERVO_OPEN_ANGLE 10

PhotoresistorPasscode* photoresPasscode;

void setup() {
  servo.attach(9);
  photoresPasscode = new PhotoresistorPasscode();
  Serial.begin(9600);
  Serial.println("Ready!");
  servo.write(120);
}

void loop() {
  photoresPasscode->updateState();
  if(photoresPasscode->sequenceCompleted())
  {
    if(photoresPasscode->sequenceCorrect())
    {
      servo.write(SERVO_OPEN_ANGLE);
      }
    else
    {
      servo.write(SERVO_CLOSE_ANGLE);
      }
    }
  
}
