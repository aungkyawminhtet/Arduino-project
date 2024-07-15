#include "Wire.h"

#define SDA_pin 21
#define SCL_pin 22

#define EEPROM_I2C_ADDRESS 0x50

char dataRead[50];

void setup() {
  Wire.begin(SDA_pin, SCL_pin);
  Serial.begin(115200);

  int address = 20;
  // char dataToWrite[20] = "Hello, minhtet how";
  String dataToWrite = "005-Premium Diesel";

  // writeStringToEEPROM(address, dataToWrite);

  char* Fuel_type;
  // readStringFromEEPROM(int address, char* Fuel_type, size_t Fuel_type);
  Fuel_type = Rom_Fuel_type(20, 40);
  Serial.print("The returned value is: ");
  Serial.println(Fuel_type);

  // readStringFromEEPROM(address);
}

void loop() {
}

void writeStringToEEPROM(int address, String data) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);

  Wire.write((uint8_t)(address >> 8));    
  Wire.write((uint8_t)(address & 0xFF));  

  // Write the string
  int i = 0;
  while (data[i]) {
    Wire.write(data[i]);
    i++;
  }
  Wire.write('\0'); // Null-terminate the string
  Wire.endTransmission();

  delay(5); // Delay for EEPROM write cycle
}


void readStringFromEEPROM(int address, char* buffer, size_t bufferSize) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
 
  Wire.write((uint8_t)(address >> 8));    
  Wire.write((uint8_t)(address & 0xFF));  
  Wire.endTransmission(false);  

   
  Wire.requestFrom(EEPROM_I2C_ADDRESS, bufferSize);

   
  size_t i = 0;
  while (Wire.available() && i < bufferSize - 1) {
    buffer[i++] = Wire.read();
  }
  buffer[i] = '\0';  
}

char* Rom_Fuel_type(int fuel_start_address, int fuel_end_address) {  // to save fuel type in eeprom

  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
 
  Wire.write((uint8_t)(fuel_start_address >> 8));    
  Wire.write((uint8_t)(fuel_start_address & 0xFF));  
  Wire.endTransmission(false);  

   
  Wire.requestFrom(EEPROM_I2C_ADDRE, );

  char tem_data;
  char* common_data = (char*)malloc(20);  // Dynamically allocate memory

  if (common_data == NULL) {
    return NULL;
  }

  for (int i = 0; i < 20; i++) common_data[i] = 0;

  for (int j = fuel_start_address; j < fuel_end_address; j++) {
    tem_data = Wire.read(j);
    if (tem_data == '\0') break;
    common_data[j - fuel_start_address] = tem_data;
  }

  // Serial.print("common data is => ");
  // Serial.println(common_data);

  return common_data;
}


// void readStringFromEEPROM(int address) {
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);
//   Wire.write((uint8_t)(address >> 8));    
//   Wire.write((uint8_t)(address & 0xFF));  
//   Wire.endTransmission(false);  
   
//   Wire.requestFrom(EEPROM_I2C_ADDRESS, 20);

//   int i = 0;
//   while (Wire.available() && i < 20 - 1) {
//     dataRead[i++] = Wire.read();
//   }
//   dataRead[i] = '\0'; // Null-terminate the string

//   Serial.print("The returned value is: ");
//   Serial.println(dataRead);
// }
