unsigned long interval = 5000;
unsigned long interval_one = 8000;
unsigned long pre_time = 0;
unsigned long current_time = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
  current_time = millis();

  if(current_time - pre_time >= interval){
    Serial.println("hello millis");
    unsigned long sec_time = millis();

    // if(sec_time - pre_time >= interval_one){
    //   Serial.println("Second function");
    // }
    pre_time = current_time;
  }

}
