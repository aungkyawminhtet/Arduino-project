#include<WiFi.h>
#include<PubSubClient.h>
#include <WiFiClientSecure.h>

// const char* ssid = "Digital Engineering Tech";
// const char* password = "1313373290";

const char* ssid = "Myo";
const char* password = "12345678";

// const char* ssid = "POS_Server";
// const char* password = "asdffdsa";

const char* mqtt_ip = "4b26b408563f43c1b0e441b02798aa06.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "admin";
const char* mqtt_pass = "Admin1234";

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

const char* outTopic = "/ak/out";  // just like route 
const char* inTopic = "/ak/#";

String data;

unsigned long prev_time;

WiFiClientSecure espClient;///////
PubSubClient client(espClient);

long currentTime, lastTime;
int count = 0;
char message[50];
bool ser_check = false;


void setup() {
  Serial.begin(115200);
  wifi_start();
  espClient.setCACert(root_ca);
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
  // client.publish(outTopic, "receive message");
  Serial.println();

}

void loop() {
  if(!client.connected()){
    reconnect();
  } 
  client.loop();
  ser_check = false;
  data = "";
  if(Serial.available() > 0){
    data = Serial.readString();
    ser_check = true;
  }

  if(ser_check){
    client.publish(outTopic, data.c_str());
    ser_check = false;
  }


  // if(millis() - prev_time >= 3000){
  //   String msg = "Hello mqtt";
  //   client.publish(outTopic, msg.c_str());
  //   prev_time = millis();
  // }

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
    if(client.connect("sbo", mqtt_user, mqtt_pass)){
      Serial.print("Connected to mqtt.");
      // client.subscribe("ak/#");
      client.subscribe("aa/#");
    }else{
      Serial.print("Fail mqtt connection");
      Serial.print(client.state()); //to know connection lost and sth error connection
      Serial.println("Retrying in 3 seconds");
      delay(3000);
    }
  }
}


 

