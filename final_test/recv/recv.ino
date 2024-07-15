
char data;
#define max_size 100
int length = 0;
char db_arr[50];
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

}

void loop() {
  main_fun();

}

void main_fun(){

  while(Serial2.available() > 0){
    data = Serial2.read();
    Serial.println(data);
    delay(500);
    db_arr[i] = data;

    if(db_arr[i] == 'o'){
      i = 0;
      Serial.println(db_arr);
      ak();
    }
    i++;
  }
}

void ak(){
  for( int z ; z < 10 ; z++){
    Serial.print("From array => ");
    Serial.print(z);
    Serial.println(db_arr[z]);
    delay(500);
  }
}
