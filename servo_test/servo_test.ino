#include<ESP32Servo.h>
Servo myservo;
int servo_pin = 18;
int i;

void setup() {
  Serial.begin(9600);
  myservo.attach(servo_pin);
  myservo.write(0);

}

void loop() {
   for(i = 0 ; i < 180 ; i++){
    myservo.write(i);
    delay(100);
   }
   if(i == 180){
    for( i ; i > 0 ; i--){
      myservo.write(i);
      delay(100);
    }
   }

}
