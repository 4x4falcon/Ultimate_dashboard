// Calibrate.h

/*
*
* These are the calibration functions
*
*
*/

void storeCalibrateSpeed() {

  EEPROM.writeFloat(eepromTachoPPRAddress, float(calibrateCounter));

}


void updateCalibrateDisplay() {

}

void doCalibrate() {
}


