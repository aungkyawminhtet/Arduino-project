// #include <HardwareSerial.h>
// HardwareSerial Sender(1);

// #define sender_Txd_pin 10
// #define sender_Rxd_pin 9
// char data;

unsigned arr[50];

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  main_fun();
}


void main_fun(){
    if(Serial2.availableForWrite()) {
    Serial2.write("HELLO");
    delay(20);
  }

  if(Serial2.available()) {
    char receivedChar = Serial2.read();
    delay(20);
    Serial.print("From Recv => ");
    Serial.println(receivedChar);
  }
}

