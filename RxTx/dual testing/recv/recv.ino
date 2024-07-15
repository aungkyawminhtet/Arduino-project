// #include <HardwareSerial.h>
// HardwareSerial Receiver(2);

// #define receiver_Txd_pin 17
// #define receiver_Rxd_pin 16
// char data;
// char arr_one;
unsigned arr[50];
int i = 0;
int data;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  main_fun();

}

void main_fun(){

  if(Serial2.availableForWrite()) {
    Serial2.write("Hi");
    delay(20);
  }

  if(Serial2.available()) {
    char receivedChar = Serial2.read(); 
    delay(20);
    Serial.print("From Sender => ");
    Serial.println(receivedChar); 
    arr[i] = receivedChar;
  }
}