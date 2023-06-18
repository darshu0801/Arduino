#define BLYNK_TEMPLATE_ID "TMPLcY5Ft9b2"
#define BLYNK_DEVICE_NAME "FIRST PROJECT"
#define BLYNK_AUTH_TOKEN "mVQQMRVKlyZhj_GpdSQSdK-yCkTAWutx"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DBKS";//Enter your WIFI name
char pass[] = "Babu@08012003";//Enter your WIFI password

DHT dht2(D4,DHT11); //D4
WidgetLCD lcd(V1);

int dbks;
float a;

BLYNK_WRITE(V0) {
  dbks = param.asInt();
}

void setup() {
  //Set the LED pin as an output pin
  pinMode(D1, OUTPUT);
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
  if (dbks == 1)
  {
    digitalWrite(D1, LOW);
  }
  else
  {
    digitalWrite(D1, HIGH);
  }
  tempalert();//TEMP READ
}

void tempalert()
{
  a = dht2.readTemperature( );
  //c = a;//copy contents of 'a' into string 'c' to be used in TG 
  if(a>35 && a<37)
  {
    //digitalWrite(14,HIGH);//connected
    lcd.clear();
    lcd.print(0,0,"Temp in C:");
    lcd.print(10,0,a);
    lcd.print(5,1,"DANGER");
    //buzzeralert();
    //lightalert();
    delay(2000);
  }
  else if(a>=37)
  {
    //digitalWrite(14,LOW);//disconnected
    //Blynk.notify("BATTERY TEMPARATURE EXCEEDED THRESHOLD LIMIT, BATTERY WILL BE DISCONNECTED IN 3 SECONDS");
    //delay(1500);
    lcd.clear();
    lcd.print(0,0,"BATTERY IS");
    lcd.print(2,1,"DISCONNECTED");
  }
  else if(a<35)
  {
    //digitalWrite(14,HIGH);//connected
    lcd.clear();
    lcd.print(0,0,"Temp in C:");
    lcd.print(10,0,a);
    lcd.print(3,1,"YOU R SAFE");
    //delay(2000);
  }
  else
  {
    lcd.clear();
    //digitalWrite(14,HIGH);//connected
  }
}
