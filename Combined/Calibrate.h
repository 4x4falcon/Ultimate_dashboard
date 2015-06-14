// Calibrate.h

/*
*
* These are the calibration functions
*
*
*/

void storeCalibrateSpeedo() {

  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, float(calibrateCounter/2));

}


void updateCalibrateDisplay() {

}

void doCalibrate() {
}


