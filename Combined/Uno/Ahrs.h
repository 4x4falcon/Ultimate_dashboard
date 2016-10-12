/*
 * Ahrs.h
 * 
 * Attitude and heading reference system
 * 
 * Using GY-81 10 DOF module on i2c
 * 
 * Using Adafruit libraries as they give units in SI rather than having to convert from obscure data
 * please support them by buying hardware from them for further development of libraries
 * 
 */

#define I2C_ADDRESS_MAGNETOMETER 0x68

void getAHRS()
 {
  
 }

int getHeading()
 {
  return 181;
 }

