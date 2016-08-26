//Meters.ino

/*
*	A generic meter reading and display
*
*
*/
#include <SoftwareSerial.h>

#include "gauge.h"

// create a gauge
Gauge generic_gauge(0, 4, 3, 0);

// temporary storage for the value
int val;

// storage to format the value in
char tempstring[10];

void setup() {
  
  Serial.begin(9600);

}


void loop() {

  val = generic_gauge.read();
  
  sprintf(tempstring, "%4d", val);

  generic_gauge.display(tempstring);

}

