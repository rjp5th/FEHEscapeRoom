#include "NumericPassword.h"

/*
 * External defines
 */
// IRremote.h references in LCDPuzzle.ino since it can't be included in multiple cpp files
extern bool ir_data_available();     // Equivalent: IrReceiver.decode()
extern unsigned long ir_get_data();  // Equivalent: IrReceiver.decodedIRData.decodedRawData
extern void ir_resume();             // Equivalent: IrReceiver.resume()


NumericPassword::NumericPassword(LiquidCrystal* lcd, int digits, int* correctPasscode){
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
  return true;  // Bypass to enable full testing
}
