/*
this circuit board is missing SDA pin and SCL pin. So declare sda_pin and scl_pin
this code is testing smart home circuit board
*/
#include "Wire.h"

// #define SDA_pin 22
// #define SCL_pin 21
#define SDA_pin 21
#define SCL_pin 22 

#define EEPROM_I2C_ADDRESS 0x50

void setup() {
  Wire.begin(SDA_pin, SCL_pin);
  // Wire.begin();
  Serial.begin(115200);

  int address = 40; //10
  int valueToWrite = 1;

  writeIntToEEPROM(10, 100);
  writeIntToEEPROM(20, 50000);
  writeIntToEEPROM(40, 888888);

  int l_readValue = readIntFromEEPROM(10);
  int r_ret = readIntFromEEPROM(20);
  int aa = readIntFromEEPROM(40);

  Serial.print("The returned 10  value is ");
  Serial.println(l_readValue);
  Serial.print("The returned 20 value is ");
  Serial.println(r_ret);
  Serial.print("The returned 40 value is ");
  Serial.println(aa);
}

void loop() {
}

void writeIntToEEPROM(int address, int value) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);

  // Write the address bytes
  Wire.write((uint8_t)(address >> 8));   // MSB
  Wire.write((uint8_t)(address & 0xFF)); // LSB

  // Write the value bytes
  Wire.write((uint8_t)(value >> 24));  // Byte 3
  Wire.write((uint8_t)(value >> 16));  // Byte 2
  Wire.write((uint8_t)(value >> 8));   // Byte 1
  Wire.write((uint8_t)(value & 0xFF)); // Byte 0

  Wire.endTransmission();

  delay(5); // Delay for EEPROM write cycle
}

int readIntFromEEPROM(int address) {
  int value = 0;

  Wire.beginTransmission(EEPROM_I2C_ADDRESS);

  // Write the address bytes
  Wire.write((uint8_t)(address >> 8));   // MSB
  Wire.write((uint8_t)(address & 0xFF)); // LSB
  Wire.endTransmission(false); // Send repeated start condition

  // Request 4 bytes from EEPROM
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 4);

  // Read the value bytes and reconstruct the integer
  if (Wire.available() >= 4) {
    value = Wire.read() << 24; // Byte 3
    value |= Wire.read() << 16; // Byte 2
    value |= Wire.read() << 8; // Byte 1
    value |= Wire.read(); // Byte 0
  }

  return value;
}

//this is to store 16 bits integer

// #include "Wire.h"

// #define SDA_pin 22
// #define SCL_pin 21

// #define EEPROM_I2C_ADDRESS 0x50

// void setup() {
//   Wire.begin(SDA_pin, SCL_pin);
//   Serial.begin(115200);

//   int address = 10;
//   int valueToWrite = 1000;

//   writeIntToEEPROM(address, valueToWrite);

//   int readValue = readIntFromEEPROM(address);

//   Serial.print("The returned value is ");
//   Serial.println(readValue);
// }

// void loop() {
// }

// void writeIntToEEPROM(int address, int value) {
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);

//   // Write the address bytes
//   Wire.write((uint8_t)(address >> 8));   // MSB
//   Wire.write((uint8_t)(address & 0xFF)); // LSB

//   // Write the value bytes
//   Wire.write((uint8_t)(value >> 8));   // MSB
//   Wire.write((uint8_t)(value & 0xFF)); // LSB

//   Wire.endTransmission();

//   delay(5); // Delay for EEPROM write cycle
// }

// int readIntFromEEPROM(int address) {
//   int value = 0;

//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);

//   // Write the address bytes
//   Wire.write((uint8_t)(address >> 8));   // MSB
//   Wire.write((uint8_t)(address & 0xFF)); // LSB
//   Wire.endTransmission(false); // Send repeated start condition

//   // Request 2 bytes from EEPROM
//   Wire.requestFrom(EEPROM_I2C_ADDRESS, 2);

//   // Read the value bytes and reconstruct the integer
//   if (Wire.available() >= 2) {
//     value = Wire.read() << 8; // MSB
//     value |= Wire.read();     // LSB
//   }

//   return value;
// }


// this is only 8bit integer data
// #include "Wire.h"

// #define EEPROM_I2C_ADDRESS 0x50

// void setup() 
// {
//   Wire.begin();
//   Serial.begin(9600);

//   int address = 0;
//   byte val = 110;
  
//   writeAddress(address, val); 
//   byte readVal = readAddress(address);
  
//   Serial.print("The returned value is ");
//   Serial.println(readVal);

// }

// void loop() 
// {

// }

// void writeAddress(int address, byte val)
// {
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);
//   Wire.write((int)(address >> 8));   // MSB
//   Wire.write((int)(address & 0xFF)); // LSB
  
   
//   Wire.write(val);
//   Wire.endTransmission();

//   delay(5);
// }

// byte readAddress(int address)
// {
//   byte rData = 0xFF;
  
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  
//   Wire.write((int)(address >> 8));   // MSB
//   Wire.write((int)(address & 0xFF)); // LSB
//   Wire.endTransmission();  


//   Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  

//   rData =  Wire.read();

//   return rData;
// }

