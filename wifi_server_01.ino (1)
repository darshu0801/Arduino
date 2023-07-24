
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>    
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid1 = "ABCD";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char* ssid     = "DBKS";   // your network SSID
const char* password = "Babu@08012003";   // your network password
String token = "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";  // openAI API Key
int max_tokens = 200;
String answer;

void setup() 
{
  Serial.begin(9600);
  delay(10);

  initWiFi();
}

//String answer; // Define the answer variable globally

void loop()
{
  Serial.println("Enter your question: ");
  while (!Serial.available()) {
    // Wait for input
  }
  String question = Serial.readStringUntil('\n');
  if (question.length() > 0) 
  {
    Serial.println("Hold tight, results incoming!");

    if (question.equalsIgnoreCase("hi")) {
      answer = "cmpl";
    }
    else if (question.equalsIgnoreCase("hello")) {
      answer = "cmpl";
    }
    else if (question.equalsIgnoreCase("what is your name")) {
      answer = "My name is";
    }
    else if (question.equalsIgnoreCase("where am i")) {
      answer = "You are here.";
    } 
    else {
      answer = openAI_text(question);
    }

    Serial.println();
    server.begin();
    WiFi.softAP(ssid1);
    IPAddress IP = WiFi.softAPIP();
  }
  
  server.on("/ans", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", answer);
  });
}



void initWiFi() {
  WiFi.mode(WIFI_STA);
  for (int i=0;i<2;i++) {
    WiFi.begin(ssid, password);
  
    delay(1000);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    long int StartTime=millis();
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if ((StartTime+5000) < millis()) break;
    } 
  
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("STAIP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
      
      break;
    }
  } 
}

String openAI_text(String request) { 
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();   //run version 1.0.5 or above

  //Serial.println(request);
  request = "{\"model\":\"text-davinci-003\",\"prompt\":\"" + request + "\",\"temperature\":0.9,\"max_tokens\":" + String(max_tokens) + ",\"frequency_penalty\":0,\"presence_penalty\":0.6,\"top_p\":1.0}";
  
  if (client_tcp.connect("api.openai.com", 443)) {
    client_tcp.println("POST /v1/completions HTTP/1.1");
    client_tcp.println("Connection: close"); 
    client_tcp.println("Host: api.openai.com");
    client_tcp.println("Authorization: Bearer " + token);
    client_tcp.println("Content-Type: application/json; charset=utf-8");
    client_tcp.println("Content-Length: " + String(request.length()));
    client_tcp.println();
    client_tcp.println(request);
    
    String getResponse="",Feedback="";
    boolean state = false;
    int waitTime = 15000;   // timeout 15 seconds
    long startTime = millis();
    while ((startTime + waitTime) > millis()) {     
      while (client_tcp.available()) {
          char c = client_tcp.read();
          Feedback += String(c);
    }
    }
    int start = Feedback.indexOf("choices") + 37;
    int end = Feedback.indexOf("index") - 10;
    String extractedString = Feedback.substring(start, end);

    // Print the extracted string
    //Serial.println(extractedString);
    client_tcp.stop();
    return extractedString;
  }
  else
    return "Connection failed";  
}
