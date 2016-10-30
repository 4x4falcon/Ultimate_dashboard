/*
 * Bluetooth.h
 * 
 * Bluetooth communications
 * 
 * 
 */

void printBluetooth()
 {
  Serial.print("Speed = ");
  Serial.println(speed);
  Serial.print("RPM = ");
  Serial.println(rpm);
  Serial.print("Voltage = ");
  Serial.println(voltVal);
  Serial.print("Oil Pressure = ");
  Serial.println(oilVal);
  Serial.print("Coolant Temperature = ");
  Serial.println(tempVal);
  Serial.print("Fuel Level = ");
  Serial.println(fuelVal);
 }


