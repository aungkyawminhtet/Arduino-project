#include "Wire.h"

#define SDA_pin 22
#define SCL_pin 21

#define EEPROM_I2C_ADDRESS 0x50

void setup() {
  Wire.begin(SDA_pin, SCL_pin);
  Serial.begin(115200);

  int address = 200;
  String dataToWrite = "005-Octane Ron(95)";

  writeStringToEEPROM(address, dataToWrite);

  String dataRead = readStringFromEEPROM(address);

  Serial.print("The returned value is: ");
  Serial.println(dataRead);
}

void loop() {
}

void writeStringToEEPROM(int address, String data) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);

  Wire.write((uint8_t)(address >> 8));  
  Wire.write((uint8_t)(address & 0xFF));  
 
  uint16_t length = data.length();
  Wire.write((uint8_t)(length >> 8));    
  Wire.write((uint8_t)(length & 0xFF)); 
 
  for (size_t i = 0; i < length; i++) {
    Wire.write(data[i]);
  }
  Wire.endTransmission();

  delay(5); // Delay for EEPROM write cycle
}

String readStringFromEEPROM(int address) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
 
  Wire.write((uint8_t)(address >> 8));   
  Wire.write((uint8_t)(address & 0xFF));  
  Wire.endTransmission(false);  

  
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 2);
  uint16_t length = (Wire.read() << 8) | Wire.read();
 
  Wire.requestFrom(EEPROM_I2C_ADDRESS, length);
 
  String dataRead;
  while (Wire.available()) {
    char c = Wire.read();
    dataRead += c;
  }

  return dataRead;
}

 