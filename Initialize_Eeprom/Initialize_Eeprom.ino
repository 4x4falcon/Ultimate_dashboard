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
  int eepromSpeedoCalibrateAddress = EEPROM.getAddress(sizeof(float));
  int eepromTachoCalibrateAddress = EEPROM.getAddress(sizeof(byte));
  int eepromTachoTypeAddress = EEPROM.getAddress(sizeof(byte));
  int eepromModeFuncAddress = EEPROM.getAddress(sizeof(byte));

  int eepromVoltLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromVoltUpperAddress = EEPROM.getAddress(sizeof(int));
  
  int eepromOilLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromOilUpperAddress = EEPROM.getAddress(sizeof(int));
  
  int eepromTempLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromTempUpperAddress = EEPROM.getAddress(sizeof(int));
  
  int eepromFuelLowerAddress = EEPROM.getAddress(sizeof(int));
  int eepromFuelUpperAddress = EEPROM.getAddress(sizeof(int));


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


  // This sets up the tacho
  // default is petrol 8 cylinders
  // for petrol engines set to number of cylinders
  // for diesel engines
  // -  if using a Dakota Digital converter then set to 8
  // -  set to number of pulses per revoulution from W terminal of alternator
  // can be calculated from
  // number of altenator pole pairs multiplied by the crank to altenator pulley ratio
  // eg 2 pole pairs
  //    crank pulley 200mm dia
  //    altenator pulley 50mm dia
  //    calibration = pole pairs * (crank pulley/altenator pulley)
  //    calibration = 2 * (200/50)
  //    calibration = 8

  EEPROM.writeByte(eepromTachoCalibrateAddress, 8);
  EEPROM.writeByte(eepromTachoTypeAddress, 0);


  // set lower and upper voltmeter range

  EEPROM.writeInt(eepromVoltLowerAddress, 0);
  EEPROM.writeInt(eepromVoltUpperAddress, 1023);
  
  // set lower and upper oil pressure range
  
  EEPROM.writeInt(eepromOilLowerAddress, 0);
  EEPROM.writeInt(eepromOilUpperAddress, 1023);

  // set lower and upper water temperature range

  EEPROM.writeInt(eepromTempLowerAddress, 0);
  EEPROM.writeInt(eepromTempUpperAddress, 1023);

  // set lower and upper fuel level range

  EEPROM.writeInt(eepromFuelLowerAddress, 0);
  EEPROM.writeInt(eepromFuelUpperAddress, 1023);




  // confirm eeprom has been written to

  Serial.println();
  Serial.print("Odometer address = ");
  Serial.print(eepromOdoAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromOdoAddress));    
  Serial.print("Tripmeter 1 address = ");
  Serial.print(eepromTrip1Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromTrip1Address));    
  Serial.print("Tripmeter 2 address = ");
  Serial.print(eepromTrip2Address);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromTrip2Address));    
  Serial.print("Calibration address = ");
  Serial.print(eepromCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readFloat(eepromCalibrateAddress));    
  Serial.print("Tacho Calibration address = ");
  Serial.print(eepromTachoCalibrateAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoCalibrateAddress));    
  Serial.print("TachoType address = ");
  Serial.print(eepromTachoTypeAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.readByte(eepromTachoTypeAddress));    
  Serial.print("Volt lower address = ");
  Serial.print(eepromVoltLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromVoltLowerAddress));    
  Serial.print("Volt upper address = ");
  Serial.print(eepromVoltUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromVoltUpperAddress));    
  Serial.print("Oil lower address = ");
  Serial.print(eepromOilLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromOilLowerAddress));    
  Serial.print("Oil upper address = ");
  Serial.print(eepromOilUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromOilUpperAddress));    
  Serial.print("Water temp lower address = ");
  Serial.print(eepromTempLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromTempLowerAddress));    
  Serial.print("Water temp upper address = ");
  Serial.print(eepromTempUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromTempUpperAddress));    
  Serial.print("Fuel level lower address = ");
  Serial.print(eepromFuelLowerAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromFuelLowerAddress));    
  Serial.print("Fuel Upper address = ");
  Serial.print(eepromFuelUpperAddress);
  Serial.print(" \t\t ");
  Serial.print("value = ");
  Serial.println(EEPROM.read(eepromFuelUpperAddress));    


}

void loop () {

}


