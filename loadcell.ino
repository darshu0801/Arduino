#define BLYNK_TEMPLATE_ID "TMPLR0OTM_ro"
#define BLYNK_TEMPLATE_NAME "QCBIoT"
#define BLYNK_AUTH_TOKEN "bHkawb3264l7nbPSnwUZ1YJZeqoDYb9O"

#include <HX711.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//#define BLYNK_TEMPLATE_ID "TMPLR0OTM_ro"
//#define BLYNK_TEMPLATE_NAME "QCBIoT"
//#define BLYNK_AUTH_TOKEN "sm0VLv7U-U0BaFFyToP18-QLLebuzNXc"

char auth[] = "bHkawb3264l7nbPSnwUZ1YJZeqoDYb9O";
//old//char auth[] = "sor72X3FYYhlbrbpjbqGk8X5BXv6heTa";       // You should get Auth Token in the Blynk App.
char ssid[] = "Darshan's X7 PRO 5G";                    // Your Wi-Fi Credentials
char pass[] = "Babu@08012003";
const int DTpin = 27;
const int SCKpin = 14;
HX711 mass;
float V=0.00005647022; //volume of metal ball 4/3pirqube
float g=9.8;
//brown gnd
//vcc orange
//blue=12
//white=13[clk]
void setup()
{
    Serial.begin(9600);
    mass.begin(DTpin, SCKpin);
    Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  //R,B,G,W
  //float F=force.read();
  //Serial.println(mass.read());
  float m = ((((mass.read()-189172.000)/22234)*9.81)/1000); //22234 is the ref weight //force = mass * g //phy terms
  //F = ((((F-187630)/13200)*6)/1000);
  //F = ((((F-189172.000)/22234)*10)/1000)-0.001;
  //Serial.println(F,3);
  //Serial.print("\n");
  float density = (m/V); //mass/vol
  density = abs(density)-40;
  Serial.print("density: ");
  Serial.println(density,3);
  Blynk.virtualWrite(V0,density);
  //float Ft=((((F-158219.00)/19324.00)*50)/1000.00)*9.81;
  /*
  Serial.print(millis()/1000.00,3);
  Serial.print("*");
  Serial.println((Ft)/(V*g),3);
  */
}
