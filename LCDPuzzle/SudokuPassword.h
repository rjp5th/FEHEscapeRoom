#ifndef _SUDOKU_PASSWORD_H
#define _SUDOKU_PASSWORD_H

class SudokuPassword {
  private:
    LiquidCrystal* lcd;
  public:
    SudokuPassword(LiquidCrystal* lcd, int digits);
    void startPasscodeDisplayLoop();
    bool passcodeDisplayLoop();
};

#endif
