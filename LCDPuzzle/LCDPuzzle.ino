#include <LiquidCrystal.h>
#include <IRremote.h>
#include "MinigameControl.h"
#include "NumericPassword.h"

/*
 * IRRemote.h function wrappers
 */
bool ir_data_available(){
  if (IrReceiver.decode()) {
    return true;
  }
  return false;
}

unsigned long ir_get_data(){
  return IrReceiver.decodedIRData.decodedRawData;
}

void ir_resume() {
  IrReceiver.resume();
}

/*
 * Global Defines
 */

#define IR_PIN 5
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS, E, D4, D5, D6, D7

#define NUM_PASSWORDS 2

MinigameControl* minigame;
NumericPassword* passwordSequences[NUM_PASSWORDS];

/*
 * Password Definitions
 */
#define SUDOKU_PASSWORD_LENGTH 8
#define TEMPERATURE_PASSWORD_LENGTH 4
int sudokuPassword[SUDOKU_PASSWORD_LENGTH] = {1, 4, 5, 7, 2, 6, 9, 4};
int temperaturePassword[TEMPERATURE_PASSWORD_LENGTH] = {1, 2, 3, 4};

/*
 * Global State Variables
 */
int passwordIndex = 0;
bool needsSetup = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Running!");

  // Start up LCD and IR
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  lcd.begin(16,2);

  // Create all the classes
  minigame = new MinigameControl(&lcd);

  // Sudoku Password
  passwordSequences[0] = new NumericPassword(&lcd, SUDOKU_PASSWORD_LENGTH, sudokuPassword);

  // Temperature Password
  passwordSequences[1] = new NumericPassword(&lcd, TEMPERATURE_PASSWORD_LENGTH, temperaturePassword);
}

void loop() {
  // Run password code if current state is passcode
  if (passwordIndex < NUM_PASSWORDS) {
    if (needsSetup) {
      passwordSequences[passwordIndex]->startPasscodeDisplayLoop();
      needsSetup = false;
    }
    if (passwordSequences[passwordIndex]->passcodeDisplayLoop()) {
      needsSetup = true;
      passwordIndex++;
    }

  // If not then execute main game display logic
  } else {
    if (needsSetup) {
      minigame->startGameDisplayLoop();
      needsSetup = false;
    }
    minigame->displayLoop();
  }
}
