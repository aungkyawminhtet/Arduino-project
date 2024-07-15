#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 27  //for rfid 
#define SDA_PIN 4
MFRC522 mfrc522(SDA_PIN, RST_PIN);

#define RST_PIN_two 27  //for rfid two
#define SDA_PIN_two 5
MFRC522 Hmi_mfrc522(SDA_PIN_two, RST_PIN_two);


void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  // pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  
  // digitalWrite(15, HIGH);

  SPI.begin();
  mfrc522.PCD_Init();
  Hmi_mfrc522.PCD_Init();
}


void loop() {  
  rfid_setup(); 
  rfid_setup_two();
}

void rfid_setup() {  // rfid auth
  // Serial.println(" rfid setup ");

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("UID tag :");
    String rfid_content = "";

    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      rfid_content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      rfid_content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    Serial.println();
    rfid_content.toUpperCase();

    Serial.print("RFID card one is => ");
    Serial.println(rfid_content);

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);

  }
}


void rfid_setup_two() {  // rfid auth
  // Serial.println(" rfid setup in Hmi two");
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

    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
  }
}


