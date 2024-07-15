#include <EEPROM.h>
 
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  eep_rom(200, "hello aung kyaw");
  data_read(200); 

}

void loop() {

}

void eep_rom(int length, String data){
  // String data = "aung kyaw";
  // int length = 10;
  int size = data.length();
  // Serial.println(size);

  for(int i = 0 ; i < size ; i++){
    EEPROM.write(length + i, data[i]);
    EEPROM.commit();
  }
  EEPROM.write(length + size, '\0'); // Null terminator to mark the end of the string
  EEPROM.commit();
  Serial.println("write success");
}

void data_read(int length){
  String readdata = "";
  char chardata;
  int i = 0;

  while (true) {
   chardata = EEPROM.read(length + i);
  //  Serial.println(readdata);
   if(chardata == '\0') break;
   readdata += chardata;
   i++;
  }

  Serial.print("Read string data ");
  Serial.println(readdata);
} 
