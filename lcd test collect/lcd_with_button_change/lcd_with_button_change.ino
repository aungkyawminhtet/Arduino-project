#include <LiquidCrystal_I2C.h>

#define relay_pin 25 //relay two
// #define relay_pin 26 //relay one
#define buzzer_pin 4
#define limit_sw_pin 32
#define sw_menu 19 // switch pin gp 19
#define up_switch 18
#define down_switch 5

volatile long pulseCount; // pulse count var
const int flowSnsor_pin = 33;
const int start_led_pin = 14;
const int stop_led_pin = 27;

int lcdColums = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27 , lcdColums, lcdRows);

int menu_count = 1; //count var gp *****
long minute_count = 10;
long liter_count = 250;
long record_count_minute;

unsigned long interval = 3000;
unsigned long prev_time = 0;
unsigned long wait_time;
unsigned long wait_time_two;
unsigned long current_time;

float calibration_factor = 7.5;

float flow_rate;
float flow_liter, total_liter;
float flow_milliLiter, total_milliLiter;

int limit_switch_value;
long total_print_liter = 0;
long total_minute_liter = 0;

String first_run = "ON";
String filled = "ON";
String stop = "ON";
// String w_fill = "ON";

void setup(){
  Serial.begin(9600);
  lcd_start();
  update_menu();

  pinMode(sw_menu, INPUT_PULLUP);
  pinMode(up_switch, INPUT_PULLUP);
  pinMode(down_switch, INPUT_PULLUP);
  pinMode(limit_sw_pin, INPUT_PULLUP);

  pinMode(relay_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  // pinMode(flowSnsor_pin, INPUT_PULLUP);

  pinMode(start_led_pin, OUTPUT);
  pinMode(stop_led_pin, OUTPUT);

  // digitalWrite(flowSnsor_pin, HIGH);
  digitalWrite(relay_pin, LOW);
  digitalWrite(start_led_pin, HIGH);
  attachInterrupt(digitalPinToInterrupt(flowSnsor_pin), pulse, FALLING);
}

void pulse(){
  pulseCount++;
}

void loop(){

  main_fun(); // mian function for menu 
}

void main_fun(){
  main_menu(); // main menu control function

  if((menu_count == 1 && !digitalRead(up_switch)) || (menu_count == 1 && !digitalRead(down_switch)))
  {
    // Serial.println("this is minute count fucntion");
    liter_up_count();
    delay(10);
    liter_down_count();
    delay(10);
  }

  if((menu_count == 2 && !digitalRead(up_switch)) || (menu_count == 2 && !digitalRead(down_switch)))
  {
    // Serial.println("this is minute count fucntion");
    minute_up_count();
    delay(10);
    minute_down_count();
    delay(10);
  }

  if((menu_count == 3 && !digitalRead(up_switch)) || (menu_count == 3 && !digitalRead(down_switch)))
  {
    // Serial.println("this is minute count fucntion");
    calibration_up_count();
    delay(10);
    calibration_down_count();
    delay(10);
  }


  running_main_fun(); ////////////////////
}

void running_main_fun(){ //This is control of action running function#####################
  limit_switch_value = digitalRead(limit_sw_pin);

  if(limit_switch_value == LOW && menu_count == 1 && liter_count > 250){
    // Serial.println("Liter run function");
    main_run_liter();
  }

  if(limit_switch_value == LOW && menu_count == 1 && liter_count == 250){
    // Serial.println("Liter for 250 function");
    main_run_liter_aa();
  }

  if(limit_switch_value == HIGH && menu_count == 1)
  {  
    // Serial.println("Not press Liter Switch!");
    print_data();
    stop_all();
  }

 //##############################################################################//

  if(limit_switch_value == LOW && menu_count == 2)
  {
    // Serial.println("Time running function");
    main_run_time();
  }

  if(limit_switch_value == HIGH && menu_count == 2)
  {
    Serial.println("Not press Time Switch!");
    stop_all();
  }

  if(limit_switch_value == HIGH && stop == "OFF"){
    // Serial.println("lcd stop funtion");
    lcd_stop();
  }

  //################################################################//
}

void main_run_liter(){ //$$$$$$$$$$$$$$$$$ ===> main function for running liter

  if(first_run == "ON"){
      wait_time_two = millis();
      pulseCount = 1;
      first_run = "OFF";
    }

  if(millis() - wait_time_two >= 2000 && total_milliLiter <= liter_count){
    // Serial.print("calibration count => ");
    // Serial.println(calibration_factor);
    // Serial.println("liter count start");
    filling_lcd();
    stop = "OFF";
    digitalWrite(relay_pin, HIGH);
    
    if(millis() - prev_time >= 100 && pulseCount > 0 ){
      // Serial.print("pulse Count is => ");
      // Serial.println(pulseCount);
      flow_rate = ((100.0 / (millis() - prev_time)) * pulseCount) / calibration_factor;

      total_liter += (pulseCount / calibration_factor) / 60.0;
      total_milliLiter += (pulseCount / calibration_factor) * 1000.0;
      print_data();

      if(total_milliLiter >= liter_count && filled == "ON"){
        digitalWrite(relay_pin, LOW);
        digitalWrite(start_led_pin, LOW);
        digitalWrite(stop_led_pin, HIGH);
        // tone(buzzer_pin, 4000);

        total_print_liter++;
        filled_litetr_lcd();
        filled = "OFF";
        stop = "ON";
      }
      pulseCount = 0;
      prev_time = millis();
    }
  }
}

void main_run_time(){//$$$$$$$$$$$$ =====> main run time function
  if(first_run == "ON"){
    wait_time = millis();
    first_run = "OFF";
  }
  record_count_minute = ( minute_count * 1000 ) + 3000;

  if(millis() - wait_time >= 2000 && millis() - wait_time <= record_count_minute){
    digitalWrite(relay_pin, HIGH); 
    filling_lcd();
    stop = "OFF";
  }

  if(millis() - wait_time >= record_count_minute && filled == "ON"){
    Serial.println("time stop");
    total_minute_liter++;

    digitalWrite(relay_pin, LOW);
    digitalWrite(start_led_pin, LOW);
    digitalWrite(stop_led_pin, HIGH);
    // tone(buzzer_pin, 4000);
    
    filled_minute_lcd();// for show filled liter lcd 
    filled = "OFF";
    stop = "ON";
  }
}

void stop_all(){ // if not press switch stop all
  // Serial.println("All Stop!")
  digitalWrite(relay_pin, LOW);
  digitalWrite(start_led_pin, HIGH);
  digitalWrite(stop_led_pin, LOW);
  // noTone(buzzer_pin);
   
  pulseCount = 0;
  total_liter = 0;
  flow_rate = 0;
  total_milliLiter = 0;
  first_run = "ON";
  filled = "ON";
  stop = "ON";
}

void main_menu(){
  if(!digitalRead(sw_menu)) // && menu_count > 0
  {
    menu_count++;
    delay(200);

    if(menu_count > 3)
    {
      menu_count = 1;
      // update_menu();
      while(!digitalRead(sw_menu));
    }
    update_menu();

    stop = "ON";
    while(!digitalRead(sw_menu));
  }
}

void update_menu(){ //lcd menu change
  switch(menu_count){
    case 0:
      menu_count = 1;
      break;
    
    case 1:
      lcd.clear();
      lcd.print("-> FlowSenor");
      lcd.setCursor(0, 1);
      lcd.print("   Time Delay");
      break;

    case 2:
      lcd.clear();
      lcd.print("   FlowSenor");
      lcd.setCursor(0, 1);
      lcd.print("-> Time Delay");
      break;

    case 3:
      lcd.clear();
      lcd.print(" Time Dealy");
      lcd.setCursor(0,1);
      lcd.print("-> C Factor");
      break;
  }
}

void calibration_up_count(){ // for calibration up count
  if(!digitalRead(up_switch)){
    calibration_factor += 0.1;
    delay(200);
    if(calibration_factor > 8.0){
      calibration_factor = 8.0;
    }
    calibration_lcd();
    while(!digitalRead(up_switch));
  }
  
}

void calibration_down_count(){ // for calibration dowun count
  if(!digitalRead(down_switch)){
    calibration_factor -= 0.1;
    delay(200);

    if(calibration_factor <= 5.5){
        calibration_factor = 5.5;
      }
    calibration_lcd();
    while(!digitalRead(down_switch));
  }
}

void liter_up_count(){ // up count for liter
  if(!digitalRead(up_switch)){
      liter_count = liter_count + 250;
      delay(200);
      lcd_print_liter();  // lcd print function
      // Serial.println(liter_count);

      while(!digitalRead(up_switch));
    }
}

void liter_down_count(){ // down count for liter
  // Serial.println("liter down function");
  if(!digitalRead(down_switch)){
      liter_count = liter_count - 250;
      delay(200);

      if(liter_count <= 250){
        liter_count = 250;
      }
      lcd_print_liter(); // lcd print function
      // Serial.println(liter_count);
      
      while(!digitalRead(down_switch));
    }
}

void minute_up_count(){ // up count for minute
  // Serial.println("up count minute function");
  if(!digitalRead(up_switch)){
      minute_count = minute_count + 5;
      delay(50);
      lcd_print_minute(); // lcd print function
      // Serial.println(minute_count);
      while(!digitalRead(up_switch));
    }
}

void minute_down_count(){ // down count for minute
  // Serial.println("down count minute function");
  if(!digitalRead(down_switch)){
      minute_count = minute_count - 5;
      delay(50);

      if(minute_count <= 10){
        minute_count = 10;
      }
      lcd_print_minute(); // lcd print function
      // Serial.println(minute_count);
      while(!digitalRead(down_switch));
    }
}

void calibration_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibration Num");
  lcd.setCursor(0, 1);
  lcd.print("calibrate ");
  lcd.print(calibration_factor);
}

void filling_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Filling...");
  delay(50);
}

void filled_litetr_lcd(){
  stop = "ON";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Filled ");
  lcd.setCursor(0, 1);
  lcd.print("Total liter ");
  lcd.print(total_print_liter);
  lcd.print("L");
}

void filled_minute_lcd(){
  stop = "ON";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Filled ");
  lcd.setCursor(0, 1);
  lcd.print("Total Count ");
  lcd.print(total_minute_liter);
  lcd.print("L");
}

void lcd_stop(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Program Stop!");
  delay(50);
}

void lcd_print_liter(){
  lcd.clear();
  lcd.print("Flow Function");
  lcd.setCursor(0, 1);
  lcd.print("M/liter ");
  lcd.print(liter_count);
  lcd.print("m/l");
}

void lcd_print_minute(){
  lcd.clear();
  lcd.print("Time Function");
  lcd.setCursor(0, 1);
  lcd.print("Seconds ");
  lcd.print(minute_count);
  lcd.print("s");
}

void lcd_start(){ //setup of lcd

  const char* text = "Pump Project";
  int textLength = strlen(text);
  int text_center = (lcdColums - textLength) / 2; //to lcd center

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Welcome To Water");
  lcd.setCursor(text_center,1);
  lcd.print(text);
  delay(1500);
  lcd.clear();
}

void print_data(){ //data printing fun
  Serial.print("Flow rate is => ");
  Serial.print(flow_rate);
  Serial.print(" l/m");   
  Serial.print("  ");

  Serial.print("Total Liters is => ");
  Serial.print(total_liter);
  Serial.print(" l");
  Serial.print("  ");

  Serial.print("Total flow millier => ");
  Serial.print(total_milliLiter);
  Serial.println(" ml");
}

void main_run_liter_aa(){

  if(first_run == "ON"){
      wait_time_two = millis();
      pulseCount = 1;
      first_run = "OFF";
    }
  if(millis() - wait_time_two >= 2000 && total_milliLiter <= liter_count){
    // Serial.println("liter count start");
    filling_lcd();
    stop = "OFF";
    
    if(millis() - prev_time >= 100 && pulseCount > 0 ){
      // Serial.println("250L for function");
      digitalWrite(relay_pin, HIGH);
      // Serial.print("pulse Count is => ");
      // Serial.println(pulseCount);
      flow_rate = ((100.0 / (millis() - prev_time)) * pulseCount) / 8;

      total_liter += (pulseCount / 8.0) / 60.0;
      total_milliLiter += ((pulseCount / 8.0) / 60.0) * 1000.0;
      print_data();

      if(total_milliLiter >= liter_count && filled == "ON"){
        digitalWrite(relay_pin, LOW);
        digitalWrite(start_led_pin, LOW);
        digitalWrite(stop_led_pin, HIGH);
        // tone(buzzer_pin, 4000);

        total_print_liter++;
        filled_litetr_lcd();
        filled = "OFF";
        stop = "ON";
      }
      pulseCount = 0;
      prev_time = millis();
    }
  }
}
