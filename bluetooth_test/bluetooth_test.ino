
#include "BluetoothSerial.h"

const char *pin = "1234";  
String device_name = "akmh";
String aa = "on";

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  SerialBT.begin(device_name); 
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    // Serial.write(SerialBT.read());

    String data = SerialBT.readString();
    Serial.println(data);

    if(data == aa){
      Serial.println("led on");
      digitalWrite(2, HIGH);
    }
    if(data == "off"){
      Serial.println("led off");
      digitalWrite(2, LOW);
    }
  }
  
}
