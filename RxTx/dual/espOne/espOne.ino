
#define max_arr_size 100

char data;
int b;
int i = 0;

char db_arr[max_arr_size];

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  Serial2.write("Helloworld");
  delay(20);

  // Serial.println("sending");
  // Serial2.write("S z");
  // main_fun();

  if(Serial2.available() > 0){

    data = char(Serial2.read());
    // Serial.print("From recv => ");
    // Serial.println(data);
    // delay(20);

    db_arr[i] = data;

    if(db_arr[i] == 'w'){
      i = -1;
      alice();
    }
    i++;
  }
}

void alice(){
  // Serial.println("I found u");
  // Serial.println(db_arr);

  if(db_arr[0] == 'N' && db_arr[8] == 'w'){
    // Serial.println("I Found H and u");
    // delay(20);
    ak();
  }
}

void ak(){
  for(int x = 0 ; x <= 8 ; x++){
    // Serial.println("This is ak function");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(db_arr[x]);
    Serial.print("  ");
  
  }
  Serial.println();
}



