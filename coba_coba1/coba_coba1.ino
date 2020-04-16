#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial esp (3, 2);

#define led_r 5
#define led_b 6
#define led_g 7
#define buzzer 8
#define RST_PIN 9
#define SS_PIN 10

char ssid[] = "ISEMSCHILLER";
char pass[] = "1nterlog4kupadamu";
//const char* php = " /globalindo/kirim.php";
char php[] = " /chiller.php";
//const char* host = "192.168.2.9";
char host[] = "10.3.141.1";
const uint16_t port = 8080;

int status = WL_IDLE_STATUS;
int statrfid = 0;
int oneortwo = 0;
int count=0;
int a=0;

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

char stat1 = '0'; //absen
char stat2 = '0';//kontener
char stat3 = '0'; //docking
char cperangkat[5];
char ckirim[30];
char cmood[6];
char cvarkon[7];
char cvardock[7];
char cvarabs[7];

bool statusKomunikasiWifi = false;
bool responDariServer = false;

MFRC522 mfrc522 (SS_PIN, RST_PIN);
WiFiEspClient client;

void setup() 
{  
  Serial.begin(9600);
  perangkat.toCharArray(cperangkat, 5);
  pinMode(buzzer, OUTPUT);
  SetSockStatus();
  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  delay(200);
  SPI.begin();
  mfrc522.PCD_Init();
  init_awal();
}

void loop()
{
  detectcard();
  delay(50);
//   Serial.print(oldmystring1);
//  Serial.print(" ");
//  Serial.println(mystring1);
  if(count++ % 2 == 0) //menyatakan bahwa klo dia genap
  {
    mystring2 = mystring1;
  }  
  else //selain itu ganjil
  {
    mystring = mystring1;
  }
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
//      buzzer_tone(1);
      digitalWrite(led_r, HIGH);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
      delay(100);
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
//      buzzer_tone(0);
    }
    if (mystring1.startsWith("1") && oldmystring1 == "" || mystring1 == "" && oldmystring1.startsWith("1"))
    {
      stat2 = '1';
//      buzzer_tone(1);
      digitalWrite(led_r, HIGH);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
      delay(100);
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
//      buzzer_tone(0);
    }
    if (mystring1.startsWith("2") && oldmystring1 == "" || mystring1 == "" && oldmystring1.startsWith("2"))
    {
      stat3 = '1';
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, HIGH);
      digitalWrite(led_b, LOW);
    }
    if (mystring1.startsWith("1") && oldmystring1.startsWith("2") || mystring1.startsWith("2") && oldmystring1.startsWith("1"))
    {
      stat2 = '1';
      stat3 = '1';
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, HIGH);
      digitalWrite(led_b, LOW);
    }
    if (mystring1.startsWith("0") && oldmystring1.startsWith("2") || mystring1.startsWith("2") && oldmystring1.startsWith("0"))
    {
      stat1 = '1';
      stat3 = '1';
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, HIGH);
      digitalWrite(led_b, LOW);
      
    }
    if (mystring1.startsWith("0") && oldmystring1.startsWith("1") || mystring1.startsWith("1") && oldmystring1.startsWith("0"))
    {
      stat1 = '1';
      stat2 = '1';
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, HIGH);
      digitalWrite(led_b, LOW);
    }
    if (stat1 == '0' && stat2 == '0' && stat3 == '0') //kondisi ketika ga ada kartu
    {
//      buzzer_tone(1);
      digitalWrite(led_r, HIGH);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
      delay(100);
      digitalWrite(led_r, LOW);
      digitalWrite(led_g, LOW);
      digitalWrite(led_b, LOW);
//      buzzer_tone(0);
    }
  String url="";
  String mood = "?mood";
  
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
    if (client.connect(host, port)) 
      {         
       client.print("GET");
       client.print(url);
       client.println(" HTTP/1.1");
       client.println("Host: 10.3.141.1");
       client.println("Connection: close");
       client.println();
       Serial.println(url);
       digitalWrite(led_r, LOW);
       digitalWrite(led_g, LOW);
       digitalWrite(led_b, HIGH);
       buzzer_tone(1);
       delay(1000);
       buzzer_tone(0);
       delay(50);
      }
  SetSockStatus();
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
