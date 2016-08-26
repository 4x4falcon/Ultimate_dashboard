// Calibrate.h

/*
*
* These are the calibration functions
*
*
*/

void storeCalibrateSpeed() {

  EEPROM.writeFloat(eepromTachoPPR, float(calibrateCounter));

}


void updateCalibrateDisplay() {

}

void doCalibrate() {
}


