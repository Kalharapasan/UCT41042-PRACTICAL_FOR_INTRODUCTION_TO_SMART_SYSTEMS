#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    5
#define RST_PIN   21

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(115200);   // Initialize serial communications
  SPI.begin();            // Init SPI bus
  mfrc522.PCD_Init();     // Init MFRC522 
  
  Serial.println("Scan an RFID tag or card...");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("Tag UID:");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  // Example: Check for a specific authorized UID
  if (content.substring(1) == "XX XX XX XX") { // Change this to your tag's UID
    Serial.println("Access Authorized");
  } else {
    Serial.println("Access Denied");
  }

  delay(1000);
}