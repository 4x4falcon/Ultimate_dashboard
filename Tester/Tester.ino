// Tester.ino

#include <Arduino.h>

#include <Button.h>
#include <Timer.h>

// the speedo tone value
volatile int toneSpeedoValue = 30;
volatile int toneSpeedoStep = 1;
const int toneSpeedoMax = 600;
const int toneSpeedoMin = 31;

// the tacho tone value
volatile int toneTachoValue = 40;
volatile int toneTachoStep = 10;
const int toneTachoMax = 1000;
const int toneTachoMin = 40;


// the speedo output pin
static const byte pinVss = 5;

// the tacho output pin
static const byte pinTacho = 6;

// the button pin
static const byte pinModeButton = 7;

// the mode led pin
static const byte pinModeLed = 8;

// function modes
static const byte modeSpeedo = 0;
static const byte modeTacho = 0;

// the function modes
static byte MODE_SPEEDO = 0;
static byte MODE_TACHO = 1;

// function mode
volatile byte modeFunction = MODE_SPEEDO;


// update timer

Timer timer = Timer();
static long updateTime = 5000;

// Helper class for handling MODE button presses
Button buttonMode = Button(pinModeButton, BUTTON_PULLUP_INTERNAL, true, 50);

bool buttonModeLongPress = false;


void buttonModePressed() {

  buttonModeLongPress = false;
  Serial.println("button pressed");
}

void buttonModeReleased()
 {
  if (!buttonModeLongPress)
   {
    modeFunction = !modeFunction;
    digitalWrite(pinModeLed, modeFunction);
    toneSpeedoValue = toneSpeedoMin;
    toneTachoValue = toneTachoMin;
    Serial.println("button released");
   }
  buttonModeLongPress = false;
 }

void buttonModeLongPressed()
 {
  digitalWrite(pinModeLed, modeFunction);
  toneSpeedoValue = toneSpeedoMax;
  toneTachoValue = toneTachoMax;
  buttonModeLongPress = true;
  Serial.println("button long press");
  buttonModeLongPress = true;
}


void doSpeedo() {
  Serial.print("Speedo output     ");
  Serial.println(toneSpeedoValue);
  noTone(pinVss);
  tone(pinVss, toneSpeedoValue);
}

void doTacho() {
  Serial.print("Tacho output    ");
  Serial.println(toneTachoValue);

  noTone(pinTacho);
  tone(pinTacho, toneTachoValue);
}

void updateOutput() {
 
  
  Serial.print("modeFunction = ");
  Serial.println(modeFunction);

  toneSpeedoValue += toneSpeedoStep;
  if ((toneSpeedoValue > toneSpeedoMax) || (toneSpeedoValue < toneSpeedoMin))
   {
    toneSpeedoStep = toneSpeedoStep * -1;
   }
  toneTachoValue += toneTachoStep;
  if ((toneTachoValue > toneTachoMax) || (toneTachoValue < toneTachoMin))
   {
    toneTachoStep = toneTachoStep * -1;
   }


  if (modeFunction == MODE_SPEEDO)
   {
    noTone(pinTacho);
    doSpeedo();
   }
  else
   {
    noTone(pinVss);
    doTacho();
   }
}


/*
 * setup
 */

void setup () {
  Serial.begin(9600);

  pinMode(pinVss, OUTPUT);
  pinMode(pinTacho, OUTPUT);
  pinMode(pinModeLed, OUTPUT);
  pinMode(pinModeButton, INPUT_PULLUP);

  // Set up mode button handlers
  buttonMode.pressHandler(buttonModePressed);
  buttonMode.releaseHandler(buttonModeReleased);
  buttonMode.holdHandler(buttonModeLongPressed, 1000);

  timer.every(updateTime, updateOutput);

  Serial.print("Connect pin D");
  Serial.print(pinVss);
  Serial.println(" to input vss interrupt pin");
  
  Serial.println("");
  Serial.print("Connect pin D");
  Serial.print(pinTacho);
  Serial.println(" to input tacho interrupt pin");

  Serial.println("");
  Serial.println("GND to GND");
}

/*
 * main loop
 */

void loop () {

  buttonMode.process();
  timer.update();
}

