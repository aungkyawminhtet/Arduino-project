void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  data_send();
}

void data_send(){
  Serial2.write("Hello");
  delay(500);
}
