
void setup() {
  Serial.begin(9600);

}

void loop() {
  aa();

}

void aa(){
  int a;
  int b= 10;

  if(Serial.available() > 0){
    a = Serial.parseInt();
    Serial.println(a);
    // Serial.println(b);
    if(a == 10){
      Serial.println("This is 10");
    }
    else if(a == 20){
      Serial.println("This is 20");
    }
    else if(a == 30){
      ak();
    }
    else{
      Serial.println("This is only integer");
    }
  }
}

void ak(){
  Serial.println("This is ak");
}
