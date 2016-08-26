# Ultimate Dashboard
Arduino powered vehicle dashboard

This is the first draft version.


There are three separate possibilities now.

Mega = Arduino Mega 2650 - utilizing a single Mega for Speedometer, Tachometer and Gauges

Uno = Arduino Uno - utilizing a separate Uno for Speedometer, Tachometer and Gauges

Nano = Arduino Nano - utilizing a separate Nano for Speedometer, Tachometer and Gauges

They are arranged as:

Speedometer
 - Displays speed in KPH or MPH
 - Has three digit led display (serial)
 - Has serial 16x2 display for odometer, trip meter(s) and other data
 - Intended to have 15 neopixel 1/4 array as well (this will depend on space in the dashboard but will be included in software)

Tachometer
 - Displays RPM
 - Has 4 digit led display (serial)
 - Has programmable Redline and Shift
 - Intended to have neopixel ring as well (this will depend on space in the dashboard but will be included in software)

Gauges
 - Has Voltmeter, Oil Pressure Meter, Water Temperature Meter and Fuel Level Meter
 - Can be expanded to include other meters
 - Initially will be on 4 digit led displays (serial)
 - Possibility to use oled graphic displays instead.
