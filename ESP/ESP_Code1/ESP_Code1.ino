

#define SS_PIN D4
#define RST_PIN D3

#define LISTEN_PORT 80

#include "ESP8266WiFi.h"
#include <SPI.h>
#include <MFRC522.h>
#include <aREST.h>

aREST rest = aREST();

WiFiServer server(LISTEN_PORT);

MFRC522 mfrc522(SS_PIN, RST_PIN);
int statuss = 0;
int out = 0;

String id;

const char* ssid = "brot";
const char* password = "9632240604";

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  rest.variable("id", &id);

  rest.set_id("1");
  rest.set_name("Station1");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("This is the local IP - ");
  Serial.println(WiFi.localIP());

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
Serial.println(" ");
  id = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    id.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  id.toUpperCase();

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);

}
