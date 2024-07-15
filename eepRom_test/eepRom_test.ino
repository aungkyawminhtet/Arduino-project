#include <EEPROM.h>
 
bool pressd = true;
char dataBuffer[10];
int a;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  EEPROM.write(88, 256);
  EEPROM.commit();

  int a = EEPROM.read(88);
  // int b = EEPROM.read(89);
  Serial.print("a int is ");
  Serial.println(a);
  // Serial.print("b int is ");
  // Serial.println(b);

  // String data = EEPROM.readString(11);
  // Serial.print("EEp read string ");
  // Serial.println(data);

  // String da = "hello world";
  // for(int j = 0 ; j < da.length() ; j++){
  //   Serial.println(da[j]);
  // }


  eep_rom();
  data_read();
  // a = EEPROM.read(16);
  // Serial.println(a);

}

void loop() {

}

void eep_rom(){
  String data = "akmh";
  int _size = 10;
  int size = data.length();
  // Serial.println(size);

  for(int i = 0 ; i < size ; i++){
    EEPROM.write(_size + i, data[i]);
    EEPROM.commit();
  }
  EEPROM.write(_size + size, '\0'); // Null terminator to mark the end of the string
  EEPROM.commit();
  Serial.println("write success");
}

void data_read(){
  String readdata = "";
  char chardata;
  int i = 0;

  while (true) {
   chardata = EEPROM.read(10 + i);
   Serial.println(readdata);
   if(chardata == '\0'){
    break;
   }
   readdata += chardata;
   i++;
  }
  Serial.print("Read string data ");
  Serial.println(readdata);
}

// void writeString(char add, String data) {
//   int _size = data.length();
//   int j;
//   for (j = 0; j < _size; j++) {
//     EEPROM.write(add + j, data[j]);
//     EEPROM.commit();
//   }
//   EEPROM.write(add + _size, '\0');  
//   EEPROM.commit();
//   Serial.println("Wrtiting ssid and pass to eeprom");
// }


 

 
 