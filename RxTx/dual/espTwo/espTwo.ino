
#define max_arr_size 100

char data;
int i = 0;
int length = 0;

char db_arr[max_arr_size];

// int arr_length = sizeof(db_arr)/sizeof(db_arr[0]);

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  
  while(Serial2.available() > 0){

    data = char(Serial2.read());
    // Serial.print("From sender => ");
    // Serial.println(data);
    // delay(20);

    db_arr[i] = data;

    if(db_arr[i] == 'd'){
      i = -1;
      bob();

    }
    i++;
  
  }

}

void bob(){
  // Serial.println("I Found d");
  // Serial.println(db_arr);

  if(db_arr[0] == 'H' && db_arr[9] == 'd'){
    // Serial.println("I Found H and d");
    // delay(20);
    ak();
  }
}

void ak(){
   for(int x = 0 ; x <= 9 ; x++){
    // Serial.println("This is ak function");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(db_arr[x]);
    Serial.print("  ");
    delay(20);
  
  }
  Serial2.write("Naypyitaw");
  delay(20);
  Serial.println();
}

