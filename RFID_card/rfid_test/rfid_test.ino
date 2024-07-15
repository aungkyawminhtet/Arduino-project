#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22
#define SS_PIN 5
// Slave Select pin
#define RST_PIN_2 22
#define SDA_PIN_2 21  // Slave Select pin

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance
MFRC522 akrfc(SDA_PIN_2, RST_PIN_2);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  akrfc.PCD_Init();  // Init MFRC522
}

void loop() {
  rfid_one();
  rfid_two();
}

void rfid_one() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Show UID on serial monitor
    Serial.print("UID tag one :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message :");
    content.toUpperCase();
    Serial.println(content);
    if (content == "1360BC1D") {
      Serial.println("Authorized access");
      // Perform actions for authorized access here
    } else if (content == "E336CA11") {
      Serial.println("Authorized access");
    } else {
      Serial.println("Access denied");
    }
    delay(1000);
  }
}

void rfid_two() {
  if (akrfc.PICC_IsNewCardPresent() && akrfc.PICC_ReadCardSerial()) {
    // Show UID on serial monitor
    Serial.print("UID tag two:");
    String content = "";
    byte letter;
    for (byte i = 0; i < akrfc.uid.size; i++) {
      Serial.print(akrfc.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(akrfc.uid.uidByte[i], HEX);
      content.concat(String(akrfc.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(akrfc.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message :");
    content.toUpperCase();
    Serial.println(content);
    if (content == "1360BC1D") {
      Serial.println("Authorized access");
      // Perform actions for authorized access here
    } else if (content == "E336CA11") {
      Serial.println("Authorized access");
    } else {
      Serial.println("Access denied");
    }
    delay(1000);
  }
}


// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN  21  // ESP32 pin GPIO5
// #define RST_PIN 22 // ESP32 pin GPIO27

// MFRC522 rfid(SS_PIN, RST_PIN);

// void setup() {
//   Serial.begin(9600);
//   SPI.begin(); // init SPI bus
//   rfid.PCD_Init(); // init MFRC522

//   Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
// }

// void loop() {
//   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
//     if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
//       MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
//       Serial.print("RFID/NFC Tag Type: ");
//       Serial.println(rfid.PICC_GetTypeName(piccType));

//       // print UID in Serial Monitor in the hex format
//       Serial.print("UID:");
//       for (int i = 0; i < rfid.uid.size; i++) {
//         Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(rfid.uid.uidByte[i], HEX);
//       }
//       Serial.println();

//       rfid.PICC_HaltA(); // halt PICC
//       rfid.PCD_StopCrypto1(); // stop encryption on PCD
//     }
//   }
// }
