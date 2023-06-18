#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("DBKS_MP");
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop()
{
  if (SerialBT.available())
  {
    String value = SerialBT.readString();
    Serial.println(value);
  }
}
