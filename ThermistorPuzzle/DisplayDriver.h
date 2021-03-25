#ifndef _DISPLAY_DRIVER_H
#define _DISPLAY_DRIVER_H

#include <Arduino.h>

#define SHIFT_DATA_PIN 2
#define SHIFT_CLOCK_PIN 3
#define SHIFT_LATCH_PIN 4

#define NUM_DIGITS 4
#define DIGIT1_PIN 5
#define DIGIT2_PIN 6
#define DIGIT3_PIN 7
#define DIGIT4_PIN 8

class DisplayDriver{
  private:
    byte displayContents[NUM_DIGITS];
    int displayIndex;
    void displayByte(int pos);
    boolean powered;
  public:
    DisplayDriver();
    void enableTimer();
    void displayDigits(int digits, boolean showLeadingZeros);
    void displayRaw(byte* rawContents);
    void setDigit(int pos, int value);
    void setRaw(int pos, byte value);
    byte getRaw(int pos);
    void clear();
    void refreshDisplay();
};

#endif
