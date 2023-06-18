#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>    
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid1 = "EFGH";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String question;

void setup() 
{
  Serial.begin(9600);
  server.begin();
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid1);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

void loop()
{
  question = Serial.readStringUntil('\n');
  while (!Serial.available()) {
  // Wait for input
  }
  server.on("/ble", HTTP_GET, [question](AsyncWebServerRequest *request){  // Capture question by value
    request->send_P(200, "text/plain", question.c_str());
  });    
}