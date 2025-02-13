#include <SoftwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <WiFiClientSecure.h>///////

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   22     
#define SS_PIN  21 

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

const byte rxPin = 15;
const byte txPin = 4;
SoftwareSerial akSerial(rxPin, txPin);

// WiFiClient espClient;
// PubSubClient client(espClient);

WiFiClientSecure espClient;///////
PubSubClient client(espClient);

const char* wifi_ssid = "Digital Engineering Tech";
const char* wifi_pass = "1313373290";

const char* mqtt_server = "4b26b408563f43c1b0e441b02798aa06.s1.eu.hivemq.cloud";
const char* mqtt_username = "admin";
const char* mqtt_password = "Admin1234";
const int mqtt_port = 8883;

// const char* mqtt_server = "192.168.0.100";
// const char* mqtt_username = "detpos";
// const char* mqtt_password = "asdffdsa";
// const int mqtt_port = 1883;

const char* outTopic ="detpos/device/card";
const char* inTopic = "detpos/device/#";

MFRC522 mfrc522(SS_PIN, RST_PIN);  //for rfid card

String message;
char Buffer[20];
bool rf_check = false;

void setup() {
  Serial.begin(115200);
  akSerial.begin(115200);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  espClient.setCACert(root_ca);

  SPI.begin();       
  mfrc522.PCD_Init();
  wifi_init();  

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Serial.println("Scan RFID tag...");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    if(!client.connected()){
      Serial.println("cloud is reconnect");
      reconnect();
    }else{
      // Serial.println("cloud is connected");
      hmi_init();
    }

  }else {
    Serial.print("wifi not connected");
    wifi_init();
  }
  // if(!client.connect()) reconnect();
  if(rf_check){
    rfid_setup();
  }
  client.loop();
}

void rfid_setup(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    String rpmsg = "";
    // byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
      
      rpmsg.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rpmsg.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message :");
    content.toUpperCase();
    Serial.println(content);
    client.publish(outTopic, rpmsg.c_str());
    // if(content == "1360BC1D") {
    //   Serial.println("Authorized access card one");
    //   client.publish(outTopic, rpmsg.c_str());

    // } else if (content == "E336CA11"){
    //   Serial.println("Authorized access card two");
    //   client.publish(outTopic, rpmsg.c_str());

    // } else {
    //   Serial.println("Access denied");
    //   client.publish(outTopic, "Access denies");
    // }
    delay(1000);
  }
}

void hmi_init(){
  // Serial.println("hmi mode");
  if(akSerial.available()){
    for(int i = 0 ; i < 10 ; i++){
      Buffer[i] = akSerial.read(); 
      delay(10);
      Serial.print(Buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    if(Buffer[4] == 0x20){
      Serial.println("this is RFid mode on");
      rf_check = true;
    }

    if(Buffer[4] == 0x10){
      Serial.println("Rfid mode is off");
      rf_check = false;
    }
  }

}

void reconnect(){
  while (!client.connected()) {
    Serial.println("MQtt is connecting ");
    String clientId = "Rfid_client-";
    clientId += String(random(0xffff), HEX);
    Serial.println(clientId);
    if(client.connect(clientId.c_str(), mqtt_username, mqtt_password)){
      Serial.println("Mqtt connected");

      client.subscribe(inTopic);
    }else{
      Serial.print("mqtt connection failed, rc=");
      Serial.print(client.state());
      Serial.print(" try again in 3 seconds");
      delay(3000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Receives messages: ");
  Serial.println(topic);
  Serial.print("Msg From payload ");
  message = "";
  for(int i = 0 ; i < length ; i++){
    message += (char)payload[i];
  }

  Serial.println(message);
  if (strcmp(topic, "detpos/device/card/ak") == 0) {
    client.publish(outTopic, "Received your message");
  }
}

void wifi_init(){
  Serial.println();
  Serial.print("connecting wifi to ");
  Serial.println(wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi is connected.");
  Serial.println(WiFi.localIP());
}
