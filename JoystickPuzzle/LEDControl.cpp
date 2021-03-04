#include <Arduino.h>
#include "LEDControl.h"

// Utility Functions

static void enableBlinking(bool enablePin9, bool enablePin10) {
  // 150ms on
  // 100ms off

  // Using Fast PWM Mode with ICR1 set to timer TOP
  // 16MHz base clock, 64 prescaler, 16-bit timer -> 262. 14 ms timer period
  // Targeting 157.284 ms on, 104.856 ms off actual values

  // Register Configuration

  // Stop the Timer
  TCCR1B = 0;

  // Interupt Mask Register (Mask all interrupts)
  TIMSK1 = 0;

  // Reset Timer
  TCNT1 = 0;

  // Control Register Configuration
  // WGM13-10 = 14 (b1110) [Set Fast PWM with ICR1 TOP]
  // CS12-10 = b011 [/64 prescaler]
  // COM1A1-0 = 0b11  Set OC1A on compare match, clear OC1A at BOTTOM (Pin 9)
  // COM1B1=0 = 0b11  Set OC1B on compare match (Pin 10)
  unsigned short pinFlags = 0;
  if (enablePin9) {
    pinFlags |= (1<<COM1A1) | (0<<COM1A0);
  }
  if (enablePin10) {
    pinFlags |= (1<<COM1B1) | (0<<COM1B0);
  }
  
  TCCR1A =  pinFlags | (1<<WGM11);
  TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
  TCCR1C = 0;
  
  // Set TOP Register Value = 65535 (I paid for the whole timer, I'm gonna use the whole timer)
  ICR1 = 0xFFFF;
  
  // OCR1A/OC1B = 39322  - Value to make the LED blink with the ~60/40 duty cycle
  OCR1A = 39322;
  OCR1B = 39322;
}

static void disableBlinking() { 
  // Stop Timer
  TCCR1B = 0;

  // Reset timer to what Arduino-Core expects (See arduino/wiring.c init function)
  TCNT1 = 0;
  TCCR1A = (1<<WGM10);
  TCCR1B = (1<<CS11) | (1<<CS10);

  // Turn off pins if they were still active when timer was disabled
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}


// Private LED Class Code

void LEDControl::setLEDState(int state) {
  // If the LED was previously blinking, disable the timer
  if (this->ledState & LED_BLINKING_FLAG != 0) {
    disableBlinking();
  }

  // See LEDControl.h for the encoding of the LED state bits

  // Handle off state
  if (state == LED_STATE_OFF) {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
  }
  // Handle blinking states
  else if ((state & LED_BLINKING_FLAG) != 0) {
    bool enableRed = ((state & LED_STATE_RED) != 0);
    bool enableGreen = ((state & LED_STATE_GREEN) != 0);

    enableBlinking(enableRed, enableGreen);
  }
  // Handle non-blinking states
  else {
    bool enableRed = ((state & LED_STATE_RED) != 0);
    bool enableGreen = ((state & LED_STATE_GREEN) != 0);
    bool enableBlue = ((state & LED_STATE_BLUE) != 0);
    digitalWrite(RED_LED_PIN, enableRed);
    digitalWrite(GREEN_LED_PIN, enableGreen);
    digitalWrite(BLUE_LED_PIN, enableBlue);
  }
  
  this->ledState = state;
}


// Public LED Class Code

LEDControl::LEDControl() {
  // Enable OC1A/B for output from timer
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  this->setLEDState(LED_STATE_OFF);
}

void LEDControl::displayIncorrect(bool enable) {
  if (enable) {
    this->setLEDState(LED_STATE_RED_BLINKING);
  } else {
    this->setLEDState(LED_STATE_OFF);
  }
}

void LEDControl::displayCorrect(bool enable) {
  if (enable) {
    this->setLEDState(LED_STATE_GREEN_BLINKING);
  } else {
    this->setLEDState(LED_STATE_OFF);
  }
}

void LEDControl::displayEntry(bool enable){
  if (enable) {
    this->setLEDState(LED_STATE_BLUE);
  } else {
    this->setLEDState(LED_STATE_OFF);
  }
}

void LEDControl::displayTimeout(bool enable) {
  if (enable) {
    this->setLEDState(LED_STATE_YELLOW_BLINKING);
  } else {
    this->setLEDState(LED_STATE_OFF);
  }
}
