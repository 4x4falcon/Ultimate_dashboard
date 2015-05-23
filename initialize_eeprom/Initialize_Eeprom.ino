/*
 * Initalize eeprom for speedometer
 *
 * This only needs to be run on initial construction of speedometer
 *
 *
 */

#include <EEPROMex.h>
#include <EEPROMVar.h>

void setup () {

  Serial.begin(9600);

  // Get eeprom storage addresses MUST be before anything else and in the same order

  int eepromOdoAddress = EEPROM.getAddress(sizeof(float));
  int eepromTrip1Address = EEPROM.getAddress(sizeof(float));
  int eepromTrip2Address = EEPROM.getAddress(sizeof(float));
  int eepromCalibrateAddress = EEPROM.getAddress(sizeof(float));

  EEPROM.writeFloat(eepromOdoAddress, 0.0);  
  EEPROM.writeFloat(eepromTrip1Address, 0.0);  
  EEPROM.writeFloat(eepromTrip2Address, 0.0);  

  // This is the pulses per kilometer or mile
  // the value here is calculated from the following
  // wheel/tyre combination is 33x12.5R15 or (318/72R5)
  //
  // pulses per revolution of vehicle speed sensor = ppr =	10
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
  //
  // when calibrated in the speedo program it is for 1 kilometer or mile

  // NOTE if you are using a sensor that is on the wheel/tyre the final drive ratio is 1


  EEPROM.writeFloat(eepromCalibrateAddress, 13300.7);  

  // confirm eeprom has been written to

  Serial.println();
  Serial.print("Odometer address = ");
  Serial.print(eepromOdoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ")
  Serial.println(EEPROM.readFloat(eepromOdoAddress));    
  Serial.print("Tripmeter 1 address = ");
  Serial.print(eepromTrip1Address);
  Serial.print(" \t\t ");
  Serial.print("value = ")
  Serial.println(EEPROM.readFloat(eepromTrip1Address));    
  Serial.print("Tripmeter 2 address = ");
  Serial.print(eepromTrip2Address);
  Serial.print(" \t\t ");
  Serial.print("value = ")
  Serial.println(EEPROM.readFloat(eepromTrip2Address));    
  Serial.print("Calibration address = ");
  Serial.print(eepromCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ")
  Serial.println(EEPROM.readFloat(eepromCalibrateAddress));    
}

void loop () {

}


