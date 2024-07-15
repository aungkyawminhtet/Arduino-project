#include<WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

int led_pin = 4;
const char* ssid = "POS_Server";
const char* password = "asdffdsa";

#define RST_PIN_two 25  //for rfid two
#define SDA_PIN_two 5
MFRC522 Hmi_mfrc522(SDA_PIN_two, RST_PIN_two);
int try_ = 0;

void setup() {
  Serial.begin(115200); 
  pinMode(13, OUTPUT);
  SPI.begin();
  // mfrc522.PCD_Init();
  Hmi_mfrc522.PCD_Init();

  // WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED && try_++ < 10){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected Wifi to ");
  Serial.println(ssid); 
}

void loop() { 
  rfid_setup_two();
}

void rfid_setup_two() {  // rfid auth
  Serial.println(" rfid setup in Hmi two");
  if (Hmi_mfrc522.PICC_IsNewCardPresent() && Hmi_mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID tag :");
    String rfid_content_two = "";

    for (byte i = 0; i < Hmi_mfrc522.uid.size; i++) {
      Serial.print(Hmi_mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(Hmi_mfrc522.uid.uidByte[i], HEX);
      rfid_content_two.concat(String(Hmi_mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfid_content_two.concat(String(Hmi_mfrc522.uid.uidByte[i], HEX));
    }
    
    Serial.println();
    rfid_content_two.toUpperCase();
    Serial.print("RFID card two is => ");
    Serial.println(rfid_content_two);
 
    Hmi_mfrc522.PICC_HaltA();
    Hmi_mfrc522.PCD_StopCrypto1();

    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
  }
}
