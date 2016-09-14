/*
 * 
 * i2c write functions
 * 
 */


//Given a string, i2cSendString chops up the string and sends out the first four characters over i2c

void  i2c_SendString_4(byte address, char *toSend)
 {
  Wire.beginTransmission(address);
  for(byte x = 0 ; x < 4 ; x++)
    Wire.write(toSend[x]);                     //Send a character from the array out over I2C
  Wire.endTransmission();                      //Stop I2C transmission
 }

void  i2c_SendString_16(byte address, char *toSend)
 {
  Wire.beginTransmission(address);
  for(byte x = 0 ; x < 16 ; x++)
    Wire.write(toSend[x]);                     //Send a character from the array out over I2C
  Wire.endTransmission();                      //Stop I2C transmission
 }

void  i2c_s7s_ClearDisplay(byte address)
 {
  Wire.beginTransmission(address);
  Wire.write(0x76);                            // Clear display
  Wire.endTransmission();
 }

void  i2c_s7s_SetDisplayBrightness(byte address, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(0x7A);                            // Brightness control command
  Wire.write(b);
  Wire.endTransmission();
 }

void  i2c_s7s_SendDecimalControl(byte address, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(0x77);                            // Brightness control command
  Wire.write(b);
  Wire.endTransmission();
 }

void  i2c_s7s_SendDigitControl(byte address, byte d, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(d);                              // Digit control command
  Wire.write(b);
  Wire.endTransmission();
 }

void  i2c_s7s_SendCursorControl(byte address, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(0x79);                            // Cursor control command
  Wire.write(b);
  Wire.endTransmission();
 }


// TODO may need separate funcitions for serial lcd (1602, 2004, etc) display


void  i2c_serlcd_SetDisplayBrightness(byte address, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(0x7C);                            // Brightness control command
  Wire.write(b);
  Wire.endTransmission();
 }

void i2c_serlcd_ClearDisplay(byte address)
 {
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(128);

  Wire.write("                ");
  Wire.write("                ");
  Wire.endTransmission();
 }

void  i2c_serlcd_SendCursorControl(byte address, byte b)
 {
  Wire.beginTransmission(address);
  Wire.write(0xFE);                            // Cursor control command
  Wire.write(b);
  Wire.endTransmission();
 }

