#include <WiFi.h>

const char* ssid = "akmh";
const char* password = "12345678";
// const char* ssid = "Digital Engineering Tech";
// const char* password = "1313373290";

// WiFiServer server(80);

IPAddress local_IP(192,168,1,188);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,0,0);
IPAddress primaryDNS(8,8,8,8);
IPAddress SecondaryDNS(8,8,1,1);

unsigned long previousMillis = 0;
unsigned long intervel =10000;

void setup() {
  Serial.begin(9600);
  wifi_start();

  Serial.print("RSSI :");
  Serial.println(WiFi.RSSI());

}

void loop() {
  unsigned long currentMillis = millis();
  // Serial.print("From currentsec => ");
  // Serial.println(currentMillis);
  delay(1000);

  // if((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= intervel)){
  //   Serial.print(millis());
  //   Serial.println("Reconnecting to wifi ...");
  //   WiFi.disconnect();
  //   WiFi.reconnect();
  //   previousMillis = currentMillis;
  // }
  // Serial.println("Connecting");

  if(WiFi.status() != WL_CONNECTED){
    Serial.println();
    Serial.println("Reconnecting to wifi ...");
    wifi_start();
  }else{
    connected();
    ak();
  }

}

void wifi_start(){

  if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, SecondaryDNS)){
    Serial.println("STA is Failed to Configure");
  }

  WiFi.mode(WIFI_STA);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for(int j = 0 ; j < 10 ; j++){
    if(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }else{
    break;
  }
  }

  // Serial.println();
  // Serial.println("Wifi connected.");
  // Serial.println("IP address :");
  // Serial.println(WiFi.localIP());

  // server.begin();
}

void connected(){
  Serial.println();
  Serial.println("Wifi connected.");
  Serial.println("IP address :");
  Serial.println(WiFi.localIP());
}

void ak(){
  Serial.println("This is from function");
  delay(1000);
}
