// #define RXD2 16
// #define TXD2 17
int arr[] = {1,2,3,4,6,7,8,10};
int i = 0;
int j = 0;
unsigned char ak[50];

void setup() {
  Serial.begin(9600);
  // Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600);
}

void aa(){
  // Serial.println("this is ak function");
  for( j ; j <= 5 ; j++){
      Serial.println("data is form rs422");
      Serial.println(arr[j]);
      delay(1000);
    }
}

void loop() {

  if(Serial2.available()){
    // Serial.println(Serial2.read(), HEX);
    ak[i] = Serial2.read();
    int a = ak[1];

    Serial.println(a, HEX);
    Serial.println(a);
    if(a == 66){
      Serial.println("this is 42");
    }else{
      Serial.println("this is not found");
    }
    i++;


    // aa();

  }
  // delay(1000);

  // Serial.print(arr[4]);

  // for( i; i < 10; i++){
  //   Serial.println(arr[i]);
  // }

  // ak[1] = 10;
  // ak[2] = 20;

  // Serial.println(ak[0]);
  // delay(1000);
  // // int b = sizeof(arr);
  // Serial.println(sizeof(arr));
  // delay(1000);
  // Serial.println(sizeof(ak));
  // delay(1000);
}



// void aa(){
//   // Serial.println("this is ak function");
//   for( j ; j <= 5 ; j++){
//       Serial.println("data is form rs422");
//       Serial.println(arr[j]);
//       delay(1000);
//     }
// }
