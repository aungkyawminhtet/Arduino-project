
const int ir_pin = 32;
const int led_pin = 4;
void setup() {
  Serial.begin(9600);
  pinMode(ir_pin, INPUT);
  pinMode(led_pin, OUTPUT);

}

void loop() {
   int val = digitalRead(ir_pin);
   if(val == LOW){
    delay(1000);
    Serial.println("this is Low");
    digitalWrite(led_pin,HIGH);
   }

   if(val == HIGH){
    Serial.println("this is HIGH");
    digitalWrite(led_pin,LOW);
   }

}
