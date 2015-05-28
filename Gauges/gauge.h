//gauge.h

#ifndef GAUGE_H
#define GAUGE_H

#include <Arduino.h>

class Gauge {
  
  

  public:

    Gauge (byte readPin, byte displayPinOut, byte displayPinIn, byte displayType);
    int read();
    void display(char* str);		// the formatted string to display

  private:


    byte m_readPin;
    byte m_displayPinIn;
    byte m_displayPinOut;
    byte m_displayType;					// 0 = Serial output to computer
							// TODO 
							// 1 = SoftwareSerial
							// 2 = I2C
							// 3 = SPI
    SoftwareSerial m_Serial;
};


Gauge::Gauge (byte readPin, byte displayPinOut, byte displayPinIn, byte displayType) :

  m_readPin(readPin),
  m_displayPinOut(displayPinOut),
  m_displayPinIn(displayPinIn),
  m_displayType(displayType),
  m_Serial(displayPinIn, displayPinOut)
 {
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
//  SoftwareSerial m_Serial(m_displayPinIn,m_displayPinOut,0);
    m_Serial.write(str);
    break;
   default:
    Serial.println(str);
   }
 }


#endif

