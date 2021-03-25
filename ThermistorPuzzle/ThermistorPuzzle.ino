#include "DisplayDriver.h"
#include "TempReader.h"

DisplayDriver* disp = NULL;
TempReader* tempReader;

ISR(TIMER1_OVF_vect) {
  if (disp != NULL) {
    disp->refreshDisplay();
  }
}

// Calibration error for display
byte calError[] = {0x40, 0x39, 0x77, 0x38};

// Allows shifting offsets depending on percent complete when displaying
byte statusDots[] = {0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80};

// Secret code to be displayed
int secretCode = 7365;

void setup() {
  disp = new DisplayDriver();
  disp->enableTimer();

  tempReader = new TempReader(1.5, 0.4);
  tempReader->calibrate();
}

void loop() {
  int statusCode = tempReader->tempStatus();
  
  if (statusCode == STATUS_CAL_ERROR){
    disp->displayRaw(calError);
  } else if (statusCode == STATUS_REACHED){
    disp->displayDigits(secretCode, true);
  } else {
    disp->displayRaw(statusDots + statusCode);
  }
  
  delay(200);
}
