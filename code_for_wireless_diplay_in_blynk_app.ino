#define BLYNK_PRINT Serial
#include <TinyGPS++.h> 
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <BlynkSimpleEsp8266.h>
#define BLYNK_MAX_SENDBYTES 512
//#include "CTBot.h"


//WiFiClientSecure secured_client;
//CTBot myBot;
//TBMessage msg;

static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

float a,latitude,longitude;
int b;
String lat_str,lng_str,notify,c;

TinyGPSPlus gps; // The TinyGPS++ object
DHT dht2(2,DHT11); //D4
WidgetLCD lcd(V2);//TEMP DISPLAY
WidgetLCD lcd1(V1);//LOC DISPLAY

SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

BlynkTimer timer;


char auth[] = "kKczOS0qW_8snQrExL34cqrHhe6YuXUv";
//String token = "5334993886:AAH1IDtytTqA0SgEcPNYmsE0puu6-acDHKc"; 

char ssid[] = "realme X7 Pro 5G";
char pass[] = "Babu@2003";

void setup()
{
  // Debug console
  Serial.begin(9600);
  //temparature sensor D4
  
  pinMode(16, INPUT); //flame sensor D0
  pinMode(12, OUTPUT); //buzzer D6
  pinMode(13, OUTPUT); //LED for alert D7
  pinMode(14, OUTPUT); //LED for connection between motor and battery ie MCB D5
  ss.begin(GPSBaud);//START GPS
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once //NOT REQUIRED
  /*myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection()){
   
    Serial.println("\ntestConnection OK");
  }
  else
  {
    Serial.println("\ntestConnection NOK");
  }*/
}

void checkGPS(){                                        //NOT REQUIRED
  if (gps.charsProcessed() < 10)                        //NOT REQUIRED
  {                                                     //NOT REQUIRED
    Serial.println(F("No GPS detected: check wiring."));//NOT REQUIRED
    Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected//NOT REQUIRED
  }                                                     //NOT REQUIRED
}                                                       //NOT REQUIRED

void loop()
{
  Blynk.run();
  tempalert();//TEMP READ
  b = digitalRead(16);//CHECKS FIRE
  while (ss.available() > 0) //IF GPS MODULE IS AVAILABLE 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))//READS THE DATA AND ENCODES IT INTO NORMAL FORMAT
        displayInfo();
  }
  
  firealert();//ALERTS IF FIRE
  //telegram();
  timer.run();//NA
}

void displayInfo()
{ 
    latitude = (gps.location.lat());
    lat_str=String(latitude, 7);
    longitude = (gps.location.lng());
    lng_str=String(longitude, 7); 
    lcd1.clear();
    lcd1.print(0,0,"LAT:");
    lcd1.print(0,1,"LNG:");
    lcd1.print(4,0,lat_str);
    lcd1.print(4,1,lng_str);  
    notify ="EMERGENCY!!! ,AN ELECTRIC VEHICLE CAUGHT FIRE AT " + lat_str + "," + lng_str + " RESCUE TEAM WANTED AT THIS LOCATION AS SOON AS POSSIBLE, " + "CLICK ON THE LINK TO OPEN THE LOCATION IN GOOGLE MAPS " + "https://www.google.com/maps/search/?api=1&query=" + lat_str + "," + lng_str;//STRING MERGING   
}

//String chat_id="123485102";

/*void telegram()
{
  if (myBot.getNewMessage(msg))
  {
    if (msg.text.equalsIgnoreCase("location"))
    {    
      myBot.sendMessage(msg.sender.id, notify);
    }
    else if (msg.text.equalsIgnoreCase("fire check"))
    {
      if(b==0)
      {    
      myBot.sendMessage(msg.sender.id, "EV ON FIRE!!!");
      }
      else
      {
        myBot.sendMessage(msg.sender.id, "EV IS SAFE");
      }
    }
    else if (msg.text.equalsIgnoreCase("Temp"))
    {    
      myBot.sendMessage(msg.sender.id, c); 
    }
    else
    {
      myBot.sendMessage(msg.sender.id, "ENTER THE CORRECT COMMAND");
    }
  }
}*/
void firealert()
{
  if(b==0) //fire is detected
  {
    lcd.clear();
    lcd.print(0,0,"FIRE IN THE BOX");
    lcd.print(3,1,"EMERGENCY AT");
    buzzeralert();
    lightalert();
    digitalWrite(14,LOW);//disconnected
    delay(2000); 
    Blynk.notify("EMERGENCY!!!, EV CAUGHT FIRE, LOCATION DETAILS SENT, RESCUE TEAM ON THE WAY");
    Blynk.email("EMERGENCY!!!",notify);
  }
}
void tempalert()
{
  a = dht2.readTemperature( );
  //c = a;//copy contents of 'a' into string 'c' to be used in TG 
  if(a>35 && a<37)
  {
    digitalWrite(14,HIGH);//connected
    lcd.clear();
    lcd.print(0,0,"Temp in C:");
    lcd.print(10,0,a);
    lcd.print(5,1,"DANGER");
    buzzeralert();
    lightalert();
    delay(2000);
  }
  else if(a>=37)
  {
    digitalWrite(14,LOW);//disconnected
    Blynk.notify("BATTERY TEMPARATURE EXCEEDED THRESHOLD LIMIT, BATTERY WILL BE DISCONNECTED IN 3 SECONDS");
    delay(1500);
    lcd.clear();
    lcd.print(0,0,"BATTERY IS");
    lcd.print(2,1,"DISCONNECTED");
  }
  else if(a<35)
  {
    digitalWrite(14,HIGH);//connected
    lcd.clear();
    lcd.print(0,0,"Temp in C:");
    lcd.print(10,0,a);
    lcd.print(3,1,"YOU R SAFE");
    delay(2000);
  }
  else
  {
    lcd.clear();
    digitalWrite(14,HIGH);//connected
  }
}

void buzzeralert()
{
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(12,LOW);
  delay(500);
  digitalWrite(12,HIGH);
  delay(500);
  digitalWrite(12,LOW);
  delay(500);
}

void lightalert()
{
  
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(500);
}
