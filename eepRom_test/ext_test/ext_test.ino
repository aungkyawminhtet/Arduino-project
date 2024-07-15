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

  // writeIntToEEPROM(10, 5);
  // writeIntToEEPROM(20, 50000);
  // writeIntToEEPROM(40, 900000);

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