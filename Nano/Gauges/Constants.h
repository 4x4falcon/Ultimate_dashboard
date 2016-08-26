// Constants.h

// function modes

static const byte FUNC_NORMAL = 0;
static const byte FUNC_CAL = 1;

// this is the serial pin for all displays

static const byte serialRX = 12;

// Voltmeter

static const byte voltAnalogPin = 0;
static const byte voltSerialTX = 22;
static const byte voltDisplayType = 1;
// values of resistors in divider network on voltAnalogPin
static const float r1 = 100000.0;
static const float r2 = 10000.0;


// Oil pressure meter

static const byte oilAnalogPin = 1;
static const byte oilSerialTX = 24;
static const byte oilDisplayType = 0;


// Water Temperature meter

static const byte tempAnalogPin = 2;
static const byte tempSerialTX = 30;
static const byte tempDisplayType = 0;


// Fuel Level meter

static const byte fuelAnalogPin = 3;
static const byte fuelSerialTX = 28;
static const byte fuelDisplayType = 0;

static const byte pinModeButton = 5;

// digital inputs from 12V
static const byte pinLightsOn = 8;		//	Lights on input
static const byte pinBrightnessSw = 9;		//	Brightness switch
static const byte pinIgnOn = 10;		//	Ignition on

// arduino onboard led pin
static const byte pinLed = 13;


// times in ms
static const unsigned long timeUpdate = 1000;


// messages
//const char message[] PROGMEM = ;

const char message000[] PROGMEM = " = ";                  // =
const char message001[] PROGMEM = "Setting ";             // Setting

const static char message100[] PROGMEM = "Title";         // Title
const static char message101[] PROGMEM = "Ver high";      // Version High digit
const static char message102[] PROGMEM = "Ver low";       // Version Low digit


// Voltmeter messages
const char message300[] PROGMEM = "($300)Volt lower calibration";
const char message301[] PROGMEM = "($301)Volt upper calibration";
const char message302[] PROGMEM = "($302)Volt minimum reading";
const char message303[] PROGMEM = "($303)Volt maximum reading";
const char message304[] PROGMEM = "($304)Volt warning reading";
const char message305[] PROGMEM = "($305)Volt warning low";


// Oil pressure meter messages
const char message400[] PROGMEM = "($400)Oil Pressure lower calibration";
const char message401[] PROGMEM = "($401)Oil Pressure upper calibration";
const char message402[] PROGMEM = "($402)Oil Pressure minimum reading";
const char message403[] PROGMEM = "($403)Oil Pressure maximum reading";
const char message404[] PROGMEM = "($404)Oil Pressure warning reading";
const char message405[] PROGMEM = "($405)Oil Pressure warning low";


// Water temperature meter messages
const char message500[] PROGMEM = "($500)Water Temperature lower calibration";
const char message501[] PROGMEM = "($501)Water Temperature upper calibration";
const char message502[] PROGMEM = "($502)Water Temperature minimum reading";
const char message503[] PROGMEM = "($503)Water Temperature maximum reading";
const char message504[] PROGMEM = "($504)Water Temperature warning reading";
const char message505[] PROGMEM = "($505)Water Temperature warning low";

// Fuel level meter messages
const char message600[] PROGMEM = "($400)Fuel Level lower calibration";
const char message601[] PROGMEM = "($401)Fuel Level upper calibration";
const char message602[] PROGMEM = "($402)Fuel Level minimum reading";
const char message603[] PROGMEM = "($403)Fuel Level maximum reading";
const char message604[] PROGMEM = "($404)Fuel Level warning reading";
const char message605[] PROGMEM = "($405)Fuel Level warning low";



const char* const string_table[] PROGMEM = {message000,           // =                0
                                            message001,           // Setting          1
                                            message100,           // title            2
                                            message101,           // Version high     3
                                            message102,           // Version low      4

                                            message300,           //                  5
                                            message301,           //                  6
                                            message302,           //                  7
                                            message303,           //                  8
                                            message304,           //                  9
                                            message305,           //                  10

                                            message400,           //                  11
                                            message401,           //                  12
                                            message402,           //                  13
                                            message403,           //                  14
                                            message404,           //                  15
                                            message405,           //                  16

                                            message500,           //                  17
                                            message501,           //                  18
                                            message502,           //                  19
                                            message503,           //                  20
                                            message504,           //                  21
                                            message505,           //                  22

                                            message600,           //                  23
                                            message601,           //                  24
                                            message602,           //                  25
                                            message603,           //                  26
                                            message604,           //                  27
                                            message605,           //                  28

                                          };


