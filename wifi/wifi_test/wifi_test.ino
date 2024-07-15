#include <WiFi.h>

const char* ssid = "Digital Engineering Tech";
const char* password = "1313373290";

void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  // wifi_start();
}

void loop(){
  Serial.println("Wifi scan start");
  
  int n = WiFi.scanNetworks();
  Serial.println(n);

  if ( n == 0 ){
    Serial.println("Wifi network not Found in near.");
  }else{
    for(int i = 0 ; i < n ; i++){
      Serial.println(WiFi.SSID(i));
      Serial.println(WiFi.RSSI(i));
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)? "Open" : "close");
    }
  }
}

void wifi_start(){
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for(int i = 0 ; i < 10 ; i++){
    if(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.println(WiFi.localIP());
}