#ifndef _SUDOKU_PASSWORD_H
#define _SUDOKU_PASSWORD_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class NumericPassword {
  private:
    LiquidCrystal* lcd;
    int digits;
    int* correctPasscode;
  public:
    NumericPassword(LiquidCrystal* lcd, int digits, int* correctPasscode);
    void startPasscodeDisplayLoop();
    bool passcodeDisplayLoop();
};

#endif
