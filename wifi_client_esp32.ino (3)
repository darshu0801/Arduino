#include <WiFi.h>
#include <HTTPClient.h>
#include <google-tts.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

WiFiScanClass WiFiMulti;
const char* ssid = "ABCD";
TTS tts;
File file;
String url;

// Your IP address or domain name with URL path
const char* serverNameans = "http://192.168.4.1/ans";

String answer;
HTTPClient http;

String file_name = "/123.mp3"; //Random file name just to do the test

unsigned long previousMillis = 0;
const long interval = 5000;

const char* ssid1 = "DBKS";
const char* password1 = "Babu@08012003";

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      answer = httpGETRequest(serverNameans);
      String extractedString = extractString(answer);
      Serial.println("answer: " + extractedString);
      String url = tts.getSpeechUrl(extractedString);
      // save the last HTTP GET Request
      Serial.println(url);
      previousMillis = currentMillis;
    } else {
      Serial.println("WiFi Disconnected");
    }
  }
  //dbks(url);
  /*
  connectWiFi();
  Serial.println("Initializing SD card...");
  if (!SD.begin(5)) { // see if the card is present and can be initialised.
    Serial.println("Card failed or not present, no SD Card data logging possible...");
  }
  else{
    Serial.println("Card initialised... file access enabled...");
  }

  if(WiFi.status() == WL_CONNECTED) {

        Serial.println("[HTTP] Begin...");

        http.begin(url); //We make the call to the address
        Serial.println(url);
        int httpCode = http.GET(); // We capture the code returned by the URL address
        Serial.println(httpCode);
        if(httpCode == 200) { //Code 200 means that everything has gone well
         
          if (SD.exists(file_name)) { // If the test file exists, delete it
            SD.remove(file_name);
            Serial.println("File exist, removed ..");
          }
         
          File f = SD.open(file_name, FILE_WRITE); // We create the file in writing mode
         
          if (!f) {
            Serial.println("Could not create file");
            while (1);
          } else {
            Serial.println("File was created");
          }
          //We take the data from the embedded audio file from the URL
          //and temporarily save it in a string variable
          String payload = http.getString();

          f.print(payload); // We write the data in the test file and close it
          f.close();
         
        } else {
            // If the call to the URL address failed, we print the error code
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            Serial.println("");
        }
        http.end(); // We close/end the http connection
    }
    */
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  String payload = "--";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    ESP.restart();
  }

  // Free resources
  http.end();

  return payload;
}

String extractString(String input) {
  if (input.indexOf("cmpl") != -1) {
    return "Hey there, I'm VEDA, I'm a new kind of AI. Deep questions, small talk; facts or fiction. I got you.";
  } else if (input.indexOf("You are here.") != -1) {
    //connectWiFi();
    String address = reverseGeocode(12.282496, 76.640755);
    //Serial.print("Latitude: ");
    //Serial.println(latitude, 6);
    //Serial.print("Longitude: ");
    //Serial.println(longitude, 6);
    //Serial.print("Address: ");
    int start1 = address.indexOf("formatted") + 12;
    int end1 = address.indexOf("geometry") - 3;
    return "You are at Narayan Murthy School Of Electrical Sciences, " + address.substring(start1, end1);
  } else if (input.indexOf("My name is") != -1) {
    return "I'm VEDA, I'm a new kind of AI. Deep questions, small talk; facts or fiction. I got you.";
    //return "My name is VEDA, an AI-powered VIRTUALLY ELECTRONIC DIGITAL ASSISTANT";
  }

  return input;
}

String reverseGeocode(float lat, float lng) {
  String result = "";
  WiFiClient client;
  String url = "http://api.opencagedata.com/geocode/v1/json?q=" + String(lat) + "+" + String(lng) + "&key=6ed70ca170dc47c28f177c7968185bb7";
  http.begin(client, url);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    result = http.getString();
  }
  http.end();
  return result;
}
/*
void dbks(String url1)
{
  connectWiFi();
  Serial.println("Initializing SD card...");
  if (!SD.begin(5)) { // see if the card is present and can be initialised.
    Serial.println("Card failed or not present, no SD Card data logging possible...");
  }
  else{
    Serial.println("Card initialised... file access enabled...");
  }

  if(WiFi.status() == WL_CONNECTED) {

    Serial.println("[HTTP] Begin...");

    http.begin(url1); //We make the call to the address
    Serial.println(url1);
    int httpCode = http.GET(); // We capture the code returned by the URL address
    Serial.println(httpCode);
    if(httpCode == 200) { //Code 200 means that everything has gone well
      
      if (SD.exists(file_name)) { // If the test file exists, delete it
        SD.remove(file_name);
        Serial.println("File exist, removed ..");
      }
      
      File f = SD.open(file_name, FILE_WRITE); // We create the file in writing mode
      
      if (!f) {
        Serial.println("Could not create file");
        while (1);
      } else {
        Serial.println("File was created");
      }
      //We take the data from the embedded audio file from the URL
      //and temporarily save it in a string variable
      String payload = http.getString();

      f.print(payload); // We write the data in the test file and close it
      f.close();
      
    } else {
        // If the call to the URL address failed, we print the error code
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        Serial.println("");
    }
    http.end(); // We close/end the http connection
    }
}
*/
void connectWiFi() {
  Serial.printf("Connecting to WiFi network: %s\n", ssid1);
  WiFi.begin(ssid1, password1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("WiFi connected! IP address: %s\n", WiFi.localIP().toString().c_str());
}
