#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>    

const char* ssid     = "DBKS";   // your network SSID
const char* password = "band unbidu";   // your network password
String token = "chutiya api key";  // openAI API Key
int max_tokens = 100;

void setup() 
{
  Serial.begin(115200);
  delay(10);

  initWiFi();
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
    String answer = openAI_text(question);
    Serial.println("Answer: " + answer);
  }
}


void initWiFi() {
  WiFi.mode(WIFI_STA);
  for (int i=0;i<2;i++) {
    WiFi.begin(ssid, password);
  
    delay(1000);
    Serial.println("");
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

  Serial.println(request);
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
    int waitTime = 60000;   // timeout 60 seconds
    long startTime = millis();
    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client_tcp.available()) {
          char c = client_tcp.read();
          if (state==true) {
            Feedback += String(c);
            if (Feedback.indexOf("\"text\":\"\\n\\n")!=-1)
               Feedback = "";
            if (Feedback.indexOf("\"text\":\"?\\n\\n")!=-1)
               Feedback = "";            
            if (Feedback.indexOf("\",\"index\"")!=-1) {
              client_tcp.stop();
              Serial.println();
              return Feedback.substring(0,Feedback.length()-9);               
            }
            if (Feedback.indexOf("\"}}")!=-1) {
              client_tcp.stop();
              Serial.println();
              return Feedback.substring(0,Feedback.length()-3);               
            }            
          }
          if (c == '\n') {
            if (getResponse.length()==0) state=true; 
            getResponse = "";
          } 
          else if (c != '\r')
            getResponse += String(c);
          startTime = millis();
       }
       if (getResponse.length()>0) break;
    }
    Serial.println(Feedback);
    client_tcp.stop();
    return "error";
  }
  else
    return "Connection failed";  
}
