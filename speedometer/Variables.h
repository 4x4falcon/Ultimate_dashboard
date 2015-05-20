// Current millis updated on each loop
unsigned long loopTime = 0;

// The last time the hall effect sensor was triggered
volatile unsigned long lastTrigger = 0;

// Rotations per second, set by the ISR
volatile float rps = 0.0;

// Odometer value, set by the ISR
volatile float totalMiles = 0.0;

// Current mode
int mode = MODE_SPEEDOMETER;

// The last time the odometer value was written to memory
unsigned long lastOdometerWrite = 0;

// Used to control the LED display
Adafruit_AlphaNum4 alpha = Adafruit_AlphaNum4();

// Helper class for handling button presses
Button button = Button(pinButton, LOW, 3000);

// Helper class for processing at intervals
Timer timer = Timer();
