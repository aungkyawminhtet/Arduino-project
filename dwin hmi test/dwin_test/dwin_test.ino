const int led_pin = 18;
unsigned char buffer[20];
unsigned char retbuffer[20];
int calibration_buff[20];
// int flow_ML_buff[15];
char flow_ML_buff[5];
int second_buff[20];

unsigned char showFilling[14] = {0x5A, 0xA5, 0x0a, 0x82, 0x40, 0x00, 0x46, 0x69, 0x6C, 0x6C, 0x69, 0x6E, 0x67};
unsigned char showStop[14] = {0x5A, 0xA5, 0x0B, 0x82, 0x40, 0x00, 0x53, 0x74, 0x6F, 0x70, 0x21, 0xff, 0xff, 0xff};

int secondCount = 0;
int MilliliterCount = 0;
char data;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  char hexString[] = "13E8";
  long intValue = strtol(hexString, NULL, 16);

// Use the converted integer
Serial.println(intValue); // Print the integer value


}

void loop() {
  
  if(Serial2.available() > 0){
    for(int i = 0 ; i <= 20 ; i++){
      buffer[i] = Serial2.read();
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    // Serial.print(buffer[9]);

    if(buffer[4] == 0X21){
      Serial.println("this is time mode");
      for(int j = 0 ; j < 20 ; j++){
        // if(buffer[ j + 7 ] == 0xff) break;
        second_buff[ j ] = buffer[j + 7];
      }
      // Serial.println(second_buff[1], DEC);
      secondCount = second_buff[1];
      Serial.println(secondCount);
      Serial2.write(showFilling, 14);
      // if(Serial2.available() > 0 ){
      //   for(int j = 0 ; j < 20 ; j++){
      //     ret
      //   }
      // }

    }else if(buffer[4] == 0x11){
      Serial.println("this is flow sensor mode");
      for(int j = 0; j < 2 ; j++){
        // flow_ML_buff += buffer[j+j]
        if(buffer[ j + 7 ] == 0xff) break;
        flow_ML_buff[j] = buffer[ j + 7 ];
        // Serial.print(flow_ML_buff[ j ]);
        // Serial.print(" ");
       }
       ak();

 
      //  Serial.println(atoi(flow_ML_buff));
      //  data = (flow_ML_buff[1], HEX);
      //  data += (flow_ML_buff[1], HEX);
      // int intValue = strtol(flow_ML_buff[1], NULL, 16);
      //  Serial.print("data is ");
      //  Serial.println(intValue);

    }else if(buffer[4] == 0x31){
      Serial.println("this is calibration");
      for(int j = 0 ; j < 15 ; j++){
        // if(buffer[ j + 7 ] == 0xff) break;
        calibration_buff[j] = buffer[ j + 7 ];
        // Serial.print(calibration_buff[j], HEX);
        // Serial.print(" "); 
      }
      int cal = calibration_buff[1];
      float cal_li = cal * 0.1;
      Serial.println(cal_li);
      
    }
  }
}

void ak(){
  Serial.println("stop function");
  // Serial2.write(showStop, 14);
}