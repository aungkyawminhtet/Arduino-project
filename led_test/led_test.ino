
int led_pin = 14;
// int led_pin_o = 35;
int led_pin_tw = 27;
int buzzer_pin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  // pinMode(led_pin_o, OUTPUT);
  pinMode(led_pin_tw, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

}

void loop() {
  digitalWrite(led_pin, HIGH);
  // digitalWrite(led_pin_o, HIGH);
  digitalWrite(led_pin_tw, HIGH);
  // tone(buzzer_pin, 3000),
  delay(1000);
  digitalWrite(led_pin, LOW); 
  // digitalWrite(led_pin_o, LOW);
  digitalWrite(led_pin_tw, LOW);
  // noTone(buzzer_pin);
  delay(1000);

  // tone(buzzer_pin, 8000);
  // delay(1000);
  // noTone(buzzer_pin);
  // delay(1000);

}
