// char data_arr[20];
int i = 20;
int pin = 22;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  // Serial.print("page 1");
  // Serial.write(0xff);
  // Serial.write(0xff);
  // Serial.write(0xff);

}

void loop() {
  delay(5000);
  int val = digitalRead(pin);
  // Serial.println(val);
  if(val == 0){
    Serial.println("page one");
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }else{
    Serial.println("page 0");
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }
  // if(Serial2.available()){
  //   String data_arr = "";
     
  //   while(Serial2.available() > 0){
  //     data_arr += Serial2.readString();
  //   }
  //   Serial.println(data_arr);
  //   send_data(data_arr);
  // }
  // delay(2000);
  // Serial.println("j0.val="+String(i));
  // Serial2.write("0xff");
  // Serial2.write("0xff");
  // Serial2.write("0xff");
  // i++;

}

void send_data(String data){
  if(data == "ON"){
    Serial.println("this is on state");
  }

  if(data == "OFF"){
    Serial.println("This is Off state");
  }
}
