#ifndef _TEMP_READER_H
#define _TEMP_READER_H

#include <Arduino.h>

#define THERMISTOR_PIN A0

#define RESOLUTION 1024.0
#define VIN 5.0
#define R_REF 10000.0

#define CALIBRATION_BETA -75.0
#define CALIBRATION_TEMP 25.0
#define CALIBRATION_RESISTANCE 10000.0

#define BELOW_THRESHOLD 0.5

#define STATUS_CAL_ERROR -1
#define STATUS_0_DONE 0
#define STATUS_25_DONE 1
#define STATUS_50_DONE 2
#define STATUS_75_DONE 3
#define STATUS_100_DONE 4
#define STATUS_REACHED 5

class TempReader{
  private:
    double startingTemp;
    double increaseAboveAmbient;
    double tempOvershoot;
    bool valueShown;
  public:
    TempReader(double temperatureIncreaseAmount, double overshoot);
    void calibrate();
    double readTemperature();
    int tempStatus();
};

#endif
