int a;
int c;

String b;
String b_1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    String data = Serial.readString();
    b = data[0];
    b_1 = data[1];

    char a_3 = data[2];
    char a_4 = data[3];
    a = b.toInt();
    c = b_1.toInt();

    // Serial.println(a);

    if(a == 1){
      Serial.println("This is equal 1");
    }

    if(c == 2){
      Serial.println("This is equal 2");
    }
  }

}
