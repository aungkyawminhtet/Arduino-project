#include <LiquidCrystal_I2C.h>

#define switch_pin 19

int lcdColums = 16;
int lcdRows = 2;

int count = 0;
int press;

LiquidCrystal_I2C lcd(0x27 , lcdColums, lcdRows);

String a = "Aung Kyaw Min Htet";

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(switch_pin, INPUT_PULLUP);
}

void loop(){
   int switch_data = digitalRead(switch_pin);
   
   if(switch_data == HIGH){
    // press = count++;
    // delay(500);

    for(int i = 0 ; i <= 5 ; i++){
      switch(i){
        case 1:
          lcd.setCursor(0, 0);
          lcd.print("Hello World");
          delay(1000);
        
        case 2:
          lcd.setCursor(0, 1);
          lcd.print("How are you.");
          delay(1000);

        case 3:
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("I am fine");
          delay(1000);

        case 4:
          // lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("And You.");
          delay(1000);
        
        case 5:
        lcd.clear();
        lcd.print("Bye Bye...");
        delay(1000);
        i = 0;
        break;
      }
    }



   }else{

    lcd.setCursor(0, 1);
    lcd.print("How are you.");
    delay(500);
    lcd.clear();
    // for(int j = 0 ; j < press ; j++){
    //   lcd.setCursor(0,1);
    //   lcd.print(j);
    //   delay(500);

    //   if(j == press){
    //     ak();
    //     // j = 0;
    //   }
    // }
   }
    // lcd.setCursor(0,0);
    // lcd.print("Counting ");
    // lcd.print(press);
  }

  void ak(){
    // lcd.setCursor(0,1);
    lcd.print("Data Limit!");
    delay(1000);
    lcd.clear();
  }

  // lcd.setCursor(0, 0);
  // lcd.print(data);
  // delay(1000);
  // lcd.clear();
// }

// #include <LiquidCrystal_I2C.h>

// // set the LCD number of columns and rows
// int lcdColumns = 16;
// int lcdRows = 2;

 
// LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

// String messageStatic = "Static message";
// String messageToScroll = "This is a scrolling message with more than 16 characters";

// void scrollText(int row, String message, int delayTime, int lcdColumns) {
//   for (int i=0; i < lcdColumns; i++) {
//     message = " " + message;  
//     Serial.println(message);
//   } 
//   message = message + " "; 
//   Serial.println(message);
//   for (int pos = 0; pos < message.length(); pos++) {
//     lcd.setCursor(0, row);
//     lcd.print(message.substring(pos, pos + lcdColumns));
//     delay(delayTime);
//   }
// }

// void setup(){
//   // initialize LCD
//   Serial.begin(9600);
//   lcd.init();
//   // turn on LCD backlight                      
//   lcd.backlight();
// }

// void loop(){
//   // set cursor to first column, first row
//   lcd.setCursor(0, 0);
//   // print static message
//   lcd.print(messageStatic);
//   // print scrolling message
//   scrollText(1, messageToScroll, 250, lcdColumns);
// }