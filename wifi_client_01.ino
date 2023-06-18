#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <LiquidCrystal_I2C.h>
#include <google-tts.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti WiFiMulti;
TTS tts;
const char* ssid = "ABCD";
//Your IP address or domain name with URL path
const char* serverNameans = "http://192.168.4.1/ans";

#define RX_PIN 14
#define TX_PIN 12
#define BAUD_RATE 9600

SoftwareSerial gpsSerial(RX_PIN, TX_PIN);
TinyGPSPlus gps;
float latitude, longitude;

const char* ssid1 = "DBKS";
const char* password1 = "Babu@08012003";

String answer;

unsigned long previousMillis = 0;
const long interval = 5000;

HTTPClient http;

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

String messageStatic = "PROJECT V.E.D.A";
String messageToScroll = "This is a scrolling message with more than 16 characters";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  lcd.init();
  lcd.backlight();
  gpsSerial.begin(BAUD_RATE);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Check WiFi connection status
    if (WiFiMulti.run() == WL_CONNECTED) {
      answer = httpGETRequest(serverNameans);
      String extractedString = extractString(answer);
      Serial.println("answer: " + extractedString);
      // save the last HTTP GET Request
      previousMillis = currentMillis;
      lcd.setCursor(0, 0);
      lcd.print(messageStatic);
      //Serial.println(tts.getSpeechUrl(extractedString));
      scrollText(1, extractedString, 250, lcdColumns);
    } else {
      Serial.println("WiFi Disconnected");
    }
  }
  if (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      //latitude = 12.282496;
      //longitude = 76.640755;
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);
  http.setReuse(true); // Enable connection reuse

  // Send HTTP POST request
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
    connectWiFi();
    String address = reverseGeocode(12.282496, 76.640755);
    //Serial.print("Latitude: ");
    //Serial.println(latitude, 6);
    //Serial.print("Longitude: ");
    //Serial.println(longitude, 6);
    //Serial.print("Address: ");
    int start1 = address.indexOf("formatted") + 12;
    int end1 = address.indexOf("geometry") - 3;
    String extractedString1 = "You are at Narayan Murthy School Of Electrical Sciences, " + address.substring(start1, end1);
    //Serial.println(extractedString1);
    return extractedString1;
  } else if (input.indexOf("My name is") != -1) {
    return "I'm VEDA, I'm a new kind of AI. Deep questions, small talk; facts or fiction. I got you.";
    //return "My name is VEDA, an AI powered VIRTUALLY ELECTRONIC DIGITAL ASSISTANT";
  }
  return input;
}

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
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

void connectWiFi() {
  Serial.printf("Connecting to WiFi network: %s\n", ssid);
  WiFi.begin(ssid1, password1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("WiFi connected! IP address: %s\n", WiFi.localIP().toString().c_str());
}
