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
const uint16_t port = 80;

int status = WL_IDLE_STATUS;
int statrfid = 0;
int oneortwo = 0;
int count=0;
int a=0;

String perangkat = "9010";
String vardock, varabs, varkon;
String url;
String oldurl;
String mystring, mystring1;
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

MFRC522 mfrc522 (SS_PIN, RST_PIN);
WiFiEspClient client;

void setup() 
{  
  Serial.begin(9600);
  perangkat.toCharArray(cperangkat, 5);
  pinMode(buzzer, OUTPUT);
  //SetSockStatus();
  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, LOW);
  digitalWrite(led_b, LOW);
  delay(200);
  SPI.begin();
  mfrc522.PCD_Init();
  //init_awal();
}

void loop()
{
 
  detectcard();
  delay(50);
   
  if(count++ % 2 == 0) //menyatakan bahwa klo dia genap
  {
    mystring2 = mystring1;
  }  
  else //selain itu ganjil
  {
    mystring = mystring1;
  }
//  if(mystring.startsWith ("0") || mystring2.startsWith("0"))
//  {
    if(mystring.startsWith ("0"))
    {
     varabs = mystring;
     
    }
    
    else if(mystring2.startsWith ("0"))
    {
     varabs = mystring2;
    }
//  }

//   else if(mystring.startsWith("1") || mystring2.startsWith("1"))
//  {
     if(mystring.startsWith ("1"))
    {
     varkon = mystring;
    }
    
     if(mystring2.startsWith ("1"))
    {
     varkon = mystring2;
    }
//  }

//   else if(mystring.startsWith("2")|| mystring2.startsWith("2"))
//  {
    if(mystring.startsWith ("2"))
    {
     vardock = mystring;
    }
    if(mystring2.startsWith ("2"))
    {
     vardock = mystring2;
    }

  
    
  String url="";
  String mood = "?mood";
  
  varkon.toCharArray(cvarkon,7);
  vardock.toCharArray(cvardock,7);
  varabs.toCharArray(cvarabs,7);
  
  kirim += perangkat;    kirim += "~";
  kirim += cvarkon;      kirim += "~";
  kirim += cvardock;     kirim += "~";
  kirim += cvarabs;      kirim += "~";
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
    Serial.println(url); 
  }
  oldurl = url;
  mystring="";
  mystring1="";
  mystring2=""; 
  kirim="";
  url="";
  

}
