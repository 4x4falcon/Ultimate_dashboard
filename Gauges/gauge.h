//gauge.h

#ifndef GAUGE_H
#define GAUGE_H

#include <Arduino.h>

class Gauge {

  public:

//    Gauge (byte readPin, byte displayPinOut, byte displayPinIn, byte displayType, char* name);
    Gauge (byte readPin, SoftwareSerial serial, byte displayType, char* name);
    int read();
    void display(char* str);		// the formatted string to display

  private:


    byte m_readPin;
//    byte m_displayPinIn;
//    byte m_displayPinOut;
    byte m_displayType;					// 0 = Serial output to computer
							// TODO 
							// 1 = SoftwareSerial
							// 2 = I2C
							// 3 = SPI
    char* m_name;
    SoftwareSerial m_serial;
};


//Gauge::Gauge (byte readPin, byte displayPinOut, byte displayPinIn, byte displayType, char* name) :
Gauge::Gauge (byte readPin, SoftwareSerial serial, byte displayType, char* name) :

  m_readPin(readPin),
//  m_displayPinOut(displayPinOut),
//  m_displayPinIn(displayPinIn),
  m_displayType(displayType),
//  m_serial(displayPinIn, displayPinOut),

  m_serial(serial),
  m_name(name)

 {
  m_serial.begin(9600);
  delay(1);
  m_serial.write(0x76);    // clear the display
  delay(1);
//  m_serial.write(0x79);    // set cursor to the first digit
//  m_serial.write(byte(0));
//  delay(1);
//  m_serial.print("    ");
//  delay(1);
  m_serial.print(m_name);  // name on gauge
  delay(1);
//  m_serial.write(0x77);
//  m_serial.write(0b00000100);  // sets digit 3 decimal on

   
 }

int Gauge::read()
 {
  return analogRead(m_readPin);
 }

void Gauge::display(char* str)
 {
  switch (m_displayType) {
   case 0:
    Serial.println(str);
    break;
   case 1:
    Serial.println(str);
    m_serial.print(str);
    break;
   default:
    Serial.println(str);
   }
 }

    

#endif

