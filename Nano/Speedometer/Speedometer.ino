//Speedometer.ino

/*
*	Speedometer
*
*	Reads from vss and displays
*
*	speed (kph or mph)
*
*	odometer (can not be reset by user)
*
*	tripmeters (individually resetable)
*
*
*/

// echo to serial for debugging
//#define ECHO_SERIAL 1
//#define ECHO_SERIAL_2 1
//#define ECHO_SERIAL_3 1

//library includes
#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>


//local includes for helpers
#include <Button.h>
#include <Timer.h>

//local includes for global constants and variables
#include "Constants.h"
#include "Variables.h"

//local includes for functions
#include "Version.h"
#include "Display_Functions.h"
#include "Speedo_Functions.h"
#include "Functions.h"


void setup() {
  Serial.begin(115200);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  
  eepromTitle = EEPROM.getAddress(sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  eepromOdo = EEPROM.getAddress(sizeof(long));
  eepromTrip1 = EEPROM.getAddress(sizeof(long));
  eepromTrip2 = EEPROM.getAddress(sizeof(long));

  eepromSpeedoCalibrate = EEPROM.getAddress(sizeof(float));

  eepromModeFunc = EEPROM.getAddress(sizeof(byte));

  // Read odometer value from flash memory
  totalOdometer = EEPROM.readLong(eepromOdo);

  // Read tripmeter 1 value from flash memory
  totalTrip_1 = EEPROM.readLong(eepromTrip1);

  // Read tripmeter 2 value from flash memory
  totalTrip_2 = EEPROM.readLong(eepromTrip2);

  // pulse distance
  // calibration is over 2 kilometers or miles but is stored as for 1 kilometer or mile
  // this gives distance travelled in one pulse

  pulseDistance = EEPROM.readFloat(eepromSpeedoCalibrate);

#ifdef ECHO_SERIAL
  Serial.print("setup pulseDistance =   ");
  char setupBuffer[25];
  dtostrf(pulseDistance, 20, 12, setupBuffer);
  Serial.println(setupBuffer);
#endif


  // get mode function set this should only be FUNC_KPH or FUNC_MPH
  // if set to FUNC_CAL then reset to FUNC_KPH
  modeFunc = EEPROM.readByte(eepromModeFunc);
  if (modeFunc == FUNC_CAL)
   {
    modeFunc = FUNC_KPH;
   }

  // timer to update the speedo and odometer display every 100ms
  timer.every(updateTime, updateDisplay);

  // Set up trip button handlers
  buttonTrip.setPressHandler(buttonTripPressed);
  buttonTrip.setLongPressHandler(buttonTripLongPressed);

  // Set up mode button handlers
  buttonMode.setPressHandler(buttonModePressed);
  buttonMode.setLongPressHandler(buttonModeLongPressed);

  // Set up brightness button handlers
  buttonBrightness.setPressHandler(buttonBrightnessPressed);
  buttonBrightness.setLongPressHandler(buttonBrightnessLongPressed);

  pinMode(pinOdoSerialTX, OUTPUT);
  pinMode(pinSpeedoSerialTX, OUTPUT);
  pinMode(pinSpeedoNeopixel, OUTPUT);

  //setup speedo and odo software serial baud

  speedoSerial.begin(9600);
  odoSerial.begin(9600);
  speedoPixels.begin(); // This initializes the NeoPixel library.
  delay(500);

  // 
  speedoSerial.write(0x76);
  
  // Initialize ODOMETER and TRIPMETER(s) display
  setupOdometerDisplay();
  displayOdometer();
  displaySpeed(0);
  
  // set the led on pin 13 to off
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, arduinoLed);

  // set the button and vss pins to be INPUT_PULLUP
  
  pinMode(pinTripButton, INPUT_PULLUP);
  pinMode(pinModeButton, INPUT_PULLUP);
  pinMode(pinBrightnessSw, INPUT_PULLUP);

  pinMode(pinVss, INPUT_PULLUP);
  pinMode(pinLightsOn, INPUT_PULLUP);    // need to confirm this when completing circuit

  setBrightness();

  // Attach interrupt for the vehicle speed sensor
  attachInterrupt(speedoInterrupt, sensorTriggered_2, FALLING);

}


void loop() {

  // see if there are serial commands

  while ((Serial.available()) && (speed == 0)) {
    char c = Serial.read();     //gets one byte from serial buffer
    readString += c;            //makes the string readString
    delay(2);                   //slow looping to allow buffer to fill with next character
  }

  // act on serial commands

  if (readString.length() >0) {
    doSerialCommand(readString);
    readString="";              //empty for next input
  } 


  
  loopTime = millis();

  if (modeFunc != FUNC_CAL)
   {
    timer.update();

    buttonTrip.check();
    buttonMode.check();
    buttonBrightness.check();

    writeOdometer();

    checkForTimeout();
    checkForEepromWrite();
   }
}

