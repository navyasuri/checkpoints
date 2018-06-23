

#define SS_PIN D4  
#define RST_PIN D3 

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN); 
int statuss = 0;
int out = 0;

void setup() {
  Serial.begin(115200);  
  SPI.begin();      
  mfrc522.PCD_Init();  

}

void loop() {
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
   if ( ! mfrc522.PICC_ReadCardSerial()) 
  { 
    return;
  }
  
  String id = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     id.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  id.toUpperCase();  

  

}
