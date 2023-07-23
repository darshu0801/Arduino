#define BLYNK_TEMPLATE_ID "TMPLYYUV3Bl9"
#define BLYNK_TEMPLATE_NAME "QCBIoT pH"
#define BLYNK_AUTH_TOKEN "Nx2HBUL0z5Ae0VGSiN7fD3NL7tn44qS4"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "Nx2HBUL0z5Ae0VGSiN7fD3NL7tn44qS4";      
char ssid[] = "Darshan's X7 PRO 5G";                    
char pass[] = "Babu@08012003";
const int potPin=A0;
float ph;
float Value=0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(potPin,INPUT);
  delay(1000);
}
 void loop(){
    Blynk.run(); //this initializes the platform
    Value= analogRead(potPin); //this reads from the pin which we defined where sensor is connected to that pin
    Serial.print(Value);
    Serial.print(" | ");
    float voltage=Value*(3.3/4095.0); //baro value multiplied with voltage from micro/max value produced by that sensor
    ph=(3.3*voltage)+4.3;
    Blynk.virtualWrite(V1,ph); //widget alli print madodakke
    Serial.println(ph);
    delay(1000);
 }
