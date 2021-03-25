#include "DisplayDriver.h"

int digitPinMappings[NUM_DIGITS] = {DIGIT1_PIN, DIGIT2_PIN, DIGIT3_PIN, DIGIT4_PIN};

void DisplayDriver::enableTimer(){
  // Save old sreg value
  uint8_t oldSREG = SREG;

  // Disable interrupts while configuring IRQ
  cli();
  
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
  TCCR1A =  (1<<WGM11);
  TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
  TCCR1C = 0;
  
  // Set TOP Register Value = 0x1FF, change to change update rate
  ICR1 = 0x300;
  
  // Enable interrupts for overflow
  TIMSK1 = (1<<TOIE1);

  // Re-enable interrupts
  SREG = oldSREG;
}

byte digitMap[] = {
  0b00111111, // Digit 0
  0b00000110, // Digit 1
  0b01011011, // Digit 2
  0b01001111, // Digit 3
  0b01100110, // Digit 4
  0b01101101, // Digit 5
  0b01111101, // Digit 6
  0b00100111, // Digit 7
  0b01111111, // Digit 8
  0b01101111  // Digit 9
};

DisplayDriver::DisplayDriver() {
  pinMode(SHIFT_DATA_PIN, OUTPUT);
  pinMode(SHIFT_CLOCK_PIN, OUTPUT);
  pinMode(SHIFT_LATCH_PIN, OUTPUT);
  
  digitalWrite(SHIFT_DATA_PIN, LOW);
  digitalWrite(SHIFT_CLOCK_PIN, LOW);
  digitalWrite(SHIFT_LATCH_PIN, LOW);

  for (int i = 0; i < NUM_DIGITS; i++){
    pinMode(digitPinMappings[i], OUTPUT);
    digitalWrite(digitPinMappings[i], HIGH);
    displayContents[i] = 0;
  }

  displayIndex = 0;

  powered = true;
  
}

void DisplayDriver::displayByte(int pos){
  byte dataByte = displayContents[pos];
  for (int i = 0; i < 8; i++){
    digitalWrite(SHIFT_DATA_PIN, dataByte & 0x80);
    dataByte <<= 1;
    delayMicroseconds(10);
    digitalWrite(SHIFT_CLOCK_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SHIFT_CLOCK_PIN, LOW);
    delayMicroseconds(10);
  }
  digitalWrite(SHIFT_LATCH_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SHIFT_LATCH_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(digitPinMappings[pos], LOW);
}

void DisplayDriver::refreshDisplay(){
  digitalWrite(digitPinMappings[displayIndex], HIGH);
  displayIndex = (displayIndex + 1) % NUM_DIGITS;

  if (powered) {
    displayByte(displayIndex);
  }
}

void DisplayDriver::clear(){ 
  for (int i = 0; i < NUM_DIGITS; i++){
    displayContents[i] = 0;
  }
}

void DisplayDriver::setRaw(int pos, byte value){
  displayContents[pos] = value;
}

byte DisplayDriver::getRaw(int pos) {
  return displayContents[pos];
}

void DisplayDriver::setDigit(int pos, int value){
  displayContents[pos] = digitMap[value];
}

void DisplayDriver::displayDigits(int digits, boolean showLeadingZeros){
  for (int i = 0; i < NUM_DIGITS; i++){
    if (!showLeadingZeros && digits == 0 && i != 0){
      displayContents[NUM_DIGITS-1-i] = 0;
    } else {
      displayContents[NUM_DIGITS-1-i] = digitMap[digits%10];
    }
    digits /= 10;
  }
}

void DisplayDriver::displayRaw(byte* rawContents){
  for (int i = 0; i < NUM_DIGITS; i++){
    displayContents[i] = rawContents[i];
  }
}
