#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>    
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid1 = "CN_PROJ";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String answer;

void setup() 
{
  Serial.begin(9600);
  delay(10);

}

void loop()
{
  Serial.println("Enter your question: ");
  while (!Serial.available()) {
    // Wait for input
  }
  String question = Serial.readStringUntil('\n');
  if (question.length() > 0) {
    Serial.println("Question: " + question);
    answer = simple(question);  // Update the global variable
    //Serial.println("Answer: " + answer);
    Serial.println();
    server.begin();
    //Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ssid1);
    IPAddress IP = WiFi.softAPIP();
    //Serial.print("AP IP address: ");
    //Serial.println(IP);
    //Multipurpose Internet Mail Extensions
    server.on("/cn", HTTP_GET, [answer](AsyncWebServerRequest *request){  // Capture answer by value
      request->send_P(200, "text/plain", answer.c_str());
    });
    // Start server
    }
}

String simple(String request) { 
  if (request == "hi")
  {
    request = "Hello Darshan";
  }
  return request;  
}