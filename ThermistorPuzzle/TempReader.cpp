#include "TempReader.h"


TempReader::TempReader(double temperatureIncreaseAmount, double overshoot){
  increaseAboveAmbient = temperatureIncreaseAmount;
  startingTemp = 150;
  tempOvershoot = overshoot;
}

void TempReader::calibrate(){
  startingTemp = readTemperature();
}

double TempReader::readTemperature(){
  double voltage = analogRead(THERMISTOR_PIN) / RESOLUTION * VIN;
  double resistance = (voltage * R_REF) / (VIN - voltage);

  double temperature = 1 / ((1/CALIBRATION_TEMP) + ((1/CALIBRATION_BETA)*log(resistance/CALIBRATION_RESISTANCE)));

  return temperature;
}

int TempReader::tempStatus(){
  double temperature = readTemperature();
  if (temperature < (startingTemp - BELOW_THRESHOLD)){
    valueShown = false;
    return STATUS_CAL_ERROR;
  } else if (temperature > (startingTemp + increaseAboveAmbient)){
    if (!valueShown && (temperature < (startingTemp + increaseAboveAmbient + tempOvershoot))) {
      valueShown = false;
      return STATUS_100_DONE;
    } else {
      valueShown = true;
      return STATUS_REACHED;
    }
  } else if (temperature > (startingTemp + (increaseAboveAmbient*0.75))){
    valueShown = false;
    return STATUS_75_DONE;
  } else if (temperature > (startingTemp + (increaseAboveAmbient*0.50))){
    valueShown = false;
    return STATUS_50_DONE;
  } else if (temperature > (startingTemp + (increaseAboveAmbient*0.25))){
    valueShown = false;
    return STATUS_25_DONE;
  } else {
    valueShown = false;
    return STATUS_0_DONE;
  }
}
