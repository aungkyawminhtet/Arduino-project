float calibartionFactor = 5.0;
float flowRate;
float pulseCount;

float flowRate_ml;
float total_ml;
unsigned long prev_time;

int flowMeter_pin = 14;
// byte interrupt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(flowMeter_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowMeter_pin), pulse, FALLING);

}

void pulse(){
  pulseCount++;
}

void loop() {
  if((millis() - prev_time) > 1000){

    flowRate = ((1000.0/ (millis() - prev_time)) * pulseCount) / calibartionFactor;
    prev_time = millis();
    flowRate_ml = (flowRate / 60) * 1000;
    
    total_ml += flowRate_ml;

    Serial.print("Current Flow Rate is => ");
    Serial.print(flowRate);
    Serial.print("  ");
    Serial.print("Total millimetr => ");
    Serial.print(total_ml);
    Serial.println("ml");

    pulseCount = 0;

  }

}
