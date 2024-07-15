int sw_pin = 18;
int led_pin = 5;

int oldvalue = 1;
bool ledState = true;

void setup() {
  Serial.begin(9600);
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  int sw_val = digitalRead(sw_pin);
  Serial.println(oldvalue);
  // Serial.println();

  if(sw_val == 1 && oldvalue == 0){
    Serial.println(sw_val);
    if(ledState){
      digitalWrite(led_pin, HIGH);
      ledState = false;
    }else{
      digitalWrite(led_pin, LOW);
      ledState = true;
    }
  }
  // delay(100);
  oldvalue = sw_val;

}

// if(!digitalRead(sw_pin)){  this is control swith value
//   count++;
//   delay(100);
//   while(!digitalRead(sw_pin))
// }
