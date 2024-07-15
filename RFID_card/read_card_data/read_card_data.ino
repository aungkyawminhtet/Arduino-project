 
#include <SPI.h>
#include <MFRC522.h>

// #define RST_PIN 14
// #define SS_PIN 13      
// // MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
// MFRC522 ak522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#define RST_PIN 25  //for rfid
#define SDA_PIN 5
MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
	Serial.begin(115200);		 
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			 
	mfrc522.PCD_Init();		 
	delay(4);				 
	mfrc522.PCD_DumpVersionToSerial();	 
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	 
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	// Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
