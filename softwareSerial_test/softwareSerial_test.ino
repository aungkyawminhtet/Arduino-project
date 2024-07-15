#include <SoftwareSerial.h>
const byte rxPin = 26;
const byte txPin = 27;
char buffer[20];

SoftwareSerial akSerial(rxPin, txPin);

void setup() {
  Serial.begin(115200);
  akSerial.begin(115200);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

}

void loop() {
  if(akSerial.available()){
    for(int i = 0 ; i < 20 ; i++){
      buffer[i] = akSerial.read();
      delay(10);
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

}
