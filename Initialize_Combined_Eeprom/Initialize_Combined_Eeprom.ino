/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#include <SoftwareSerial.h>
#include <EEPROMex.h>
#include <Adafruit_NeoPixel.h>

#include "Button.h"
#include "Timer.h"
#include "Constants.h";
#include "Version.h";
#include "Variables.h";

void setup () {

  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order
  eepromTitleAddress = EEPROM.getAddress(sizeof(char)*sizeof(title));
  eepromVersionHigh = EEPROM.getAddress(sizeof(byte));
  eepromVersionLow = EEPROM.getAddress(sizeof(byte));

  int eepromOdoAddress = EEPROM.getAddress(sizeof(long));
  int eepromTrip1Address = EEPROM.getAddress(sizeof(long));
  int eepromTrip2Address = EEPROM.getAddress(sizeof(long));

  int eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));

  int eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(byte));
  eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));

// VOLTMETER
   eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
   eepromVoltUpperAddress =  EEPROM.getAddress(sizeof(int));
   eepromVoltMaxAddress =  EEPROM.getAddress(sizeof(int));
   eepromVoltWarnAddress =  EEPROM.getAddress(sizeof(int));

// OIL PRESSURE METER
  eepromOilLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromOilWarnAddress =  EEPROM.getAddress(sizeof(int));

// WATER TEMPERATURE METER
  eepromTempLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromTempWarnAddress =  EEPROM.getAddress(sizeof(int));

// FUEL LEVEL METER  
  eepromFuelLowerAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelUpperAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelMaxAddress =  EEPROM.getAddress(sizeof(int));
  eepromFuelWarnAddress =  EEPROM.getAddress(sizeof(int));




  EEPROM.writeBlock(eepromTitleAddress, title);
  EEPROM.writeByte(eepromVersionHigh, versionHigh);
  EEPROM.writeByte(eepromVersionLow, versionLow);

  EEPROM.writeLong(eepromOdoAddress, 0UL);
  EEPROM.writeLong(eepromTrip1Address, 0UL);
  EEPROM.writeLong(eepromTrip2Address, 0UL);




  // This is the distance per pulse in km
  // the value here is calculated from the following
  // wheel/tyre combination is 33x12.5R15 or (318/72R5)
  //
  // pulses per revolution of vehicle speed sensor = ppr =	10
  // this needs to have hardware /10 circuit
  // circumference of wheel/tyre in meters = cir =		2.63144
  // final drive ratio of diff = ratio =			3.5
  // formula is
  // (1000m/cir) * ratio * ppr
  // for each kilometer there are (1000/cir) turns of the wheel
  // for each turn of the wheel the drive shaft turns ratio times
  // for each turn of the driveshaft there are ppr pulses
  // therefore for this tyre/wheel diff combo the result is:
  // (1000/2.63144) * 3.5 * 10
  // equals
  // 13300.7 pulses per kilometer
  // 13293.0549211603
  //
  // this is
  // 0.075227m per pulse
  //
  // to get odometer or trip reading multiply this by the number in eeprom
  //
  // 
  //
  // when calibrated in the speedo program it is for 1 kilometer or mile

  // NOTE if you are using a sensor that is on the wheel/tyre the final drive ratio is 1

  EEPROM.writeFloat(eepromSpeedoCalibrateAddress, 0.075227);  

  EEPROM.writeByte(eepromModeFuncAddress, 0);


  EEPROM.writeByte(eepromTachoCalibrateAddress, 4);
  EEPROM.writeByte(eepromTachoTypeAddress, TACHO_PETROL);


  // Setup voltmeter

  EEPROM.writeInt(eepromVoltLowerAddress, voltLower);
  EEPROM.writeInt(eepromVoltUpperAddress, voltUpper);
  EEPROM.writeInt(eepromVoltMaxAddress, voltMax);
  EEPROM.writeInt(eepromVoltWarnAddress, voltWarn);

  // Setup oil pressure meter
  EEPROM.writeInt(eepromOilLowerAddress, oilLower);
  EEPROM.writeInt(eepromOilUpperAddress, oilUpper);
  EEPROM.writeInt(eepromOilMaxAddress, oilMax);
  EEPROM.writeInt(eepromOilWarnAddress, oilWarn);

  // Setup water temperature meter
  EEPROM.writeInt(eepromTempLowerAddress, tempLower);
  EEPROM.writeInt(eepromTempUpperAddress, tempUpper);
  EEPROM.writeInt(eepromTempMaxAddress, tempMax);
  EEPROM.writeInt(eepromTempWarnAddress, tempWarn);

  // Setup fuel level meter
  EEPROM.writeInt(eepromFuelLowerAddress, fuelLower);
  EEPROM.writeInt(eepromFuelUpperAddress, fuelUpper);
  EEPROM.writeInt(eepromFuelMaxAddress, fuelMax);
  EEPROM.writeInt(eepromFuelWarnAddress, fuelWarn);


  // confirm eeprom has been written to

  Serial.print("Speedo title address = ");
  Serial.print(eepromTitleAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  EEPROM.readBlock(eepromTitleAddress, title);
  Serial.println(title);

  Serial.print("Speedo Version High address = ");
  Serial.print(eepromVersionHigh);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionHigh));    

  Serial.print("Speedo Version Low address = ");
  Serial.print(eepromVersionLow);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromVersionLow));

  Serial.println();
  Serial.print("Odometer address = ");
  Serial.print(eepromOdoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromOdoAddress));    
  Serial.print("Tripmeter 1 address = ");
  Serial.print(eepromTrip1Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromTrip1Address));    
  Serial.print("Tripmeter 2 address = ");
  Serial.print(eepromTrip2Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readLong(eepromTrip2Address));    
  Serial.print("Calibration address = ");
  Serial.print(eepromSpeedoCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromSpeedoCalibrateAddress));    




}

void loop () {

}


