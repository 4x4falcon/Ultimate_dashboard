// Calibrate.h

/*
*
* These are the calibration functions
*
*
*/

void storeCalibrateSpeed() {

  EEPROM.writeFloat(eepromCalibrateAddress, float(calibrateCounter/2));

}


void updateCalibrateDisplay() {

}

void doCalibrate() {
}


