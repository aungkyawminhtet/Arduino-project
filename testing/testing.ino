int a = 20;
int b = 30;

String ak = "my name is akmh";

void setup(){
  Serial.begin(9600);
}

void loop(){

  if(Serial.available() > 0){
    int data = Serial.read();

    Serial.println(data);

    if((data > 30) && (data < 60)){
      Serial.println("This is True");
      Serial.println(ak.length());
    }else{
      Serial.println("This is false");
    }

  }

  // if((b > a) && (a == 10)){
  //   Serial.println("True");
  // }else{
  //   Serial.println("False");
  // }
}