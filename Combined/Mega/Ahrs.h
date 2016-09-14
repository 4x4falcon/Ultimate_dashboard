/*
 * Ahrs.h
 * 
 * Attitude and heading reference system
 * 
 * Using GY-80 10 DOF module on i2c
 * 
 * Using Adafruit libraries as they give units in SI rather than having to convert from obscure data
 * please support them by buying hardware from them for further development of libraries
 * 
 */



// adafruit adxl345 library for 3-axis accelerometer
#include <Adafruit_ADXL345_U.h>

// adafruit hmc5883 library for 3-axis magnetometer
#include <Adafruit_HMC5883_U.h>

// adafruit l3gd20 library for 3-axis gyroscope
#include <Adafruit_L3GD20_U.h>

// adafruit bmp085 library for barometer and temperature
#include <Adafruit_BMP085.h>



