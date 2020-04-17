#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define RST_PIN         D2           // Configurable, see typical pin layout above
#define SS_PIN          D1          // Configurable, see typical pin layout above

String mystring, mystring1;
const char* ssid     = "ISEMSCHILLER"; //nama wifi
const char* password = "1nterlog4kupadamu"; //password
const char* host = "10.3.141.1"; //IP PC

WiFiClient client;  

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void bacarfid(){
   // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  byte buffer2[18];
  block = 1;
  len = 18;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 7; i++) {
//  Serial.write(buffer2[i]);
  mystring += (char)buffer2[i];
  mystring1 = mystring;
  }
  
  Serial.println();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void init_awal() {
  
Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(100);
  Serial.println("Connected");
 }
 

void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                           // Init MFRC522 card
  init_awal();

}
void loop() {
    Serial.print(mystring);  
bacarfid();
Serial.print(mystring);

if (client.connect(host, 8080)) { 
    Serial.print("Masuk ke database");
    bacarfid();
    delay(100);
    client.print("GET /chiller.php?");
    client.print("mood=");
    client.print(mystring);
    Serial.print(mystring);
    client.stop();
    Serial.println("Disconnected");
  }
  else {
// if you didn't get a connection to the server:
//Serial.println("connection failed");
}
delay(500);
  mystring = "";
  mystring1 = "" ;
}
