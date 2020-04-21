#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

#define RST_PIN         D2           // Configurable, see typical pin layout above
#define SS_PIN          D1          // Configurable, see typical pin layout above
#define led_r 5
#define led_b 6
#define led_g 7
#define buzzer 8

String perangkat = "9010";
String vardock, varabs, varkon;
String url;
String oldurl;
String mystring, mystring1, oldmystring1;
String subb, oldsubb;
String Respon = "";
String kirim, oldkirim;
String mystring2;
String stat;

const char* ssid     = "ISEMSCHILLER"; //nama wifi
const char* password = "1nterlog4kupadamu"; //password
const char* host = "10.3.141.1"; //IP PC
const char* php = " /chiller.php";

char stat1 = '0'; //absen
char stat2 = '0';//kontener
char stat3 = '0'; //docking
char cperangkat[5];
char ckirim[30];
char cmood[6];
char cvarkon[7];
char cvardock[7];
char cvarabs[7];

int status = WL_IDLE_STATUS;
int statrfid = 0;
int oneortwo = 0;
int count=0;
int a=0;

WiFiClient client;  
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance



void bacarfid()
{
  MFRC522::MIFARE_Key key;

  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  byte block;
  byte len;
  MFRC522::StatusCode status;
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

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
  for (uint8_t i = 0; i < 7; i++) {
  mystring += (char)buffer2[i];
  mystring1 = mystring;
  }
  Serial.println();
  //mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}



void init_awal() 
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
  delay(100);
  Serial.println("Connected");

}

 

void setup() {

  Serial.begin(9600);                                           // Initialize serial communications with the P
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();
   
  //pinMode(buzzer, OUTPUT);
//  digitalWrite(led_r, HIGH);
//  digitalWrite(led_g, LOW);
//  digitalWrite(led_b, LOW);// Init MFRC522 card
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
  init_awal();
}

void loop() {
  
if(WiFi.status() != WL_CONNECTED)
{
  Serial.println("ga konek gan");
  WiFi.begin(ssid, password);
}
bacarfid();
delay(50);
  if(count++ % 2 == 0) //menyatakan bahwa klo dia genap
  {
    mystring2 = mystring1;
  }  

else //selain itu ganjil
  {
    mystring = mystring1;
  }
  Serial.println(mystring1);
    if(mystring.startsWith ("0"))
    {
     varabs = mystring;
    }
    if(mystring2.startsWith ("0"))
    {
     varabs = mystring2;
    }
    if(mystring.startsWith ("1"))
    {
     varkon = mystring;
    }
    if(mystring2.startsWith ("1"))
    {
     varkon = mystring2;
    }
    if(mystring.startsWith ("2"))
    {
     vardock = mystring;
    }
    if(mystring2.startsWith ("2"))
    {
     vardock = mystring2;
    }

    if (mystring1.startsWith("0") && oldmystring1 == "" || mystring1 == "" && oldmystring1.startsWith("0"))
    {
      stat1 = '1';
    }
    if (mystring1.startsWith("1") && oldmystring1 == "" || mystring1 == "" && oldmystring1.startsWith("1"))
    {
      stat2 = '1';
    }
    if (mystring1.startsWith("2") && oldmystring1 == "" || mystring1 == "" && oldmystring1.startsWith("2"))
    {
      stat3 = '1';
    }
    if (mystring1.startsWith("1") && oldmystring1.startsWith("2") || mystring1.startsWith("2") && oldmystring1.startsWith("1"))
    {
      stat2 = '1';
      stat3 = '1';
    }
    if (mystring1.startsWith("0") && oldmystring1.startsWith("2") || mystring1.startsWith("2") && oldmystring1.startsWith("0"))
    {
      stat1 = '1';
      stat3 = '1';
    }
    if (mystring1.startsWith("0") && oldmystring1.startsWith("1") || mystring1.startsWith("1") && oldmystring1.startsWith("0"))
    {
      stat1 = '1';
      stat2 = '1';
    }
  String url="";
  String mood = "?mood";
  
  perangkat.toCharArray(cperangkat, 5);
  varkon.toCharArray(cvarkon,7);
  vardock.toCharArray(cvardock,7);
  varabs.toCharArray(cvarabs,7);
  
  kirim += perangkat;    kirim += "~";
  kirim += cvarabs;      kirim += "~";
  kirim += cvarkon;      kirim += "~";
  kirim += cvardock;     kirim += "~";
  kirim += stat1;        kirim += "~";
  kirim += stat2;        kirim += "~";
  kirim += stat3;          
  
  kirim.toCharArray(ckirim,35);      
  mood.toCharArray(cmood,6);
  url += php;
  url += "?mood=";
  url += ckirim;

  if(oldurl != url)
  {
    delay(500);
if (client.connect(host, 8080)) 
{ 
    client.print("GET");
    client.print(url);
       client.println(" HTTP/1.1");
       client.println("Host: 10.3.141.1");
       client.println("Connection: close");
       client.println();
       Serial.println(url);
  }
 }

  oldurl = url;
  oldmystring1 = mystring1;
  mystring="";
  mystring1="";
  mystring2=""; 
  kirim="";
  url="";
  stat1 = '0';
  stat2 = '0';
  stat3 = '0';

}
