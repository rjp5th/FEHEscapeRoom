#include "NumericPassword.h"
#include <Math.h>
/*
 * External defines
 */
// IRremote.h references in LCDPuzzle.ino since it can't be included in multiple cpp files
extern bool ir_data_available();     // Equivalent: IrReceiver.decode()
extern unsigned long ir_get_data();  // Equivalent: IrReceiver.decodedIRData.decodedRawData
extern void ir_resume();             // Equivalent: IrReceiver.resume()

#define IR_PIN 5
#define ZERO 0xE916FF00
#define ONE 0xF30CFF00
#define TWO 0xE718FF00
#define THREE 0xA15EFF00
#define FOUR 0xF708FF00
#define FIVE 0xE31CFF00
#define SIX 0xA55AFF00
#define SEVEN 0xBD42FF00
#define EIGHT 0xAD52FF00
#define NINE 0xB54AFF00

NumericPassword::NumericPassword(LiquidCrystal* lcd, int digits, int *correctPasscode){
  this->lcd = lcd;
  this->digits = digits;
  this->correctPasscode = correctPasscode;
}

void NumericPassword::startPasscodeDisplayLoop(){
  // Test code to make sure that each passcode length runs
  lcd->clear();
  lcd->print("Passcode: ");
  lcd->write('0'+digits);
  delay(2000);
}

bool NumericPassword::passcodeDisplayLoop(){
  lcd->clear();
  int i = 0;
  while(i<digits){
    lcd->setCursor(i,0);
    lcd->print("_");
    i++;
  }
  i=0;
  int code[digits] = {0,0,0,0,0,0,0,0};
  bool isTrue = true;
  while(i<digits){
    if (ir_data_available()){
      if (ir_get_data()!=0){
        int num = 0;
        switch (ir_get_data())
        {
        case ZERO:
        num = 0;
        break;
        case ONE:
        num = 1;
        break;
        case TWO:
        num = 2;
        break;
        case THREE:
        num = 3;
        break;
        case FOUR:
        num = 4;
        break;
        case FIVE:
        num = 5;
        break;
        case SIX:
        num = 6;
        break;
        case SEVEN:
        num = 7;
        break;
        case EIGHT:
        num = 8;
        break;
        case NINE:
        num = 9;
        break;    
        }
        lcd->setCursor(i,0);
        lcd->print(num);
        code[i] = num;
        i++;
      }
      ir_resume();
    }
  }
  bool arraysEqual = true;
  i = 0;
  while(i<digits)
  {
    if(code[i] != *correctPasscode)
    {
      arraysEqual = false;
      
      }
    correctPasscode++;
    i++;
    }
  if (arraysEqual){
    lcd->setCursor(0,1);
    lcd->print("CORRECT");
    isTrue = true;
  }
  else
  {
  lcd->setCursor(0,1);
  lcd->print("INCORRECT");
  isTrue = false;
  ir_resume();
  }
  return isTrue; 
}
