#include<WiFi.h>
#include<PubSubClient.h>

// const char* ssid = "Digital Engineering Tech";
// const char* password = "13133732092";

const char* ssid = "POS_Server";
const char* password = "asdffdsa";

const char* mqtt_ip = "192.168.0.100";
const int mqtt_port = 1883;
const char* mqtt_user = "detpos";
const char* mqtt_pass = "asdffdsa";

const char* outTopic = "/ak/out";  // just like route 
const char* inTopic = "/ak/in";

WiFiClient espClient;
PubSubClient client(espClient);

long currentTime, lastTime;
int count = 0;
char message[50];


void setup() {
  Serial.begin(9600);
  wifi_start();
  client.setServer(mqtt_ip, mqtt_port);
  client.setCallback(callback); //to receive message from mqtt

}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Received messages; ");
  Serial.println(topic);
  Serial.print("message paylod ");
  for(int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();

}

void wifi_start(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  if(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi is connected.");
}

void reconnect(){
  while(!client.connected()){
    Serial.println("Connecting to Mqtt ");
    if(client.connect("ak", mqtt_user, mqtt_pass)){
      Serial.print("Connected to mqtt.");
      client.subscribe("ak/#");
      client.subscribe("aa/#")
    }else{
      Serial.print("Fail mqtt connection");
      Serial.print(client.state()); //to know connection lost and sth error connection
      Serial.println("Retrying in 5 seconds");
      delay(5000);
    }
  }
}

// void reconnect(){
//   while(!client.connected()){
//     Serial.print("Connectind to ");
//     Serial.println(mqtt_ip);
//     if(client.connected()){
//       Serial.print("Connected to ");
//       Serial.println(mqtt_ip);
//     }else{
//       Serial.println("Try again connect");
//       delay(1000);
//     }
//   }
// }
