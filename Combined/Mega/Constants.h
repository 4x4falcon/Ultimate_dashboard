/*
 * Constants.h
 *
 *
 * Constant values
 */

// EEPROM has a limited life span; be careful how often we write to it
static const unsigned long odometerWriteFrequency = 60000000;
// odometer write to eeprom timeout
static const unsigned long odoTimeout = odometerWriteFrequency * 10;


// INPUTS

// values of resistors in divider network on voltAnalogPin

static const float r1 = 14880.0;
static const float r2 = 9830.0;


// SPEEDO constants


// ODOMETER constants
// active tripmeter indicator
// this is a small square in the centre of the lcd character
// from datasheet
static const char tripActive = B10100101;

static const char * gaugesFormat = "%3d ";
static const char * tachoFormat = "%4d";
static const char * speedoFormat = "%4d";



