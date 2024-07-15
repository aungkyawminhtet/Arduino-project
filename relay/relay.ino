int relayPin_one = 18;
int relayPin_two = 19;
int r122=15;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin_one, OUTPUT);
  pinMode(relayPin_two, OUTPUT);

}

void loop() {
  Serial.print("hello world");
  Serial.available()

  digitalWrite(relayPin_one, HIGH);
  delay(1000);
  digitalWrite(relayPin_one, LOW);
  delay(1000);
  digitalWrite(relayPin_two, HIGH);
  delay(1000);
  digitalWrite(relayPin_two, LOW);
  delay(1000);
  digitalWrite(r122, HIGH);
  delay(1000);
  digitalWrite(r122, LOW);
  delay(1000);

  
}




