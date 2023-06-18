/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include "DHT.h"

DHT dht2(2,DHT11);

void setup()
{
  Serial.begin(9600);

}


void loop()

{

    Serial.print("Temparature in C:");
    Serial.print((dht2.readTemperature( )));
    delay(5000);

}
