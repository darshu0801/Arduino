#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define RX_PIN 14
#define TX_PIN 12
#define BAUD_RATE 9600

SoftwareSerial gpsSerial(RX_PIN, TX_PIN);
TinyGPSPlus gps;
float latitude, longitude;

const char* ssid = "DBKS";
const char* password = "Babu@08012003";

void setup() {
  Serial.begin(9600);
  connectWiFi();
  gpsSerial.begin(BAUD_RATE);
}

void loop() {
  if (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      String address = reverseGeocode(latitude, longitude);
      //Serial.print("Latitude: ");
      //Serial.println(latitude, 6);
      //Serial.print("Longitude: ");
      //Serial.println(longitude, 6);
      Serial.print("Address: ");
      int start1 = address.indexOf("formatted") + 12;
      int end1 = address.indexOf("geometry") - 3;
      String extractedString1 = address.substring(start1, end1);
      Serial.println(extractedString1);
    }
  }
}

String reverseGeocode(float lat, float lng) {
  String result = "";
  WiFiClient client;
  HTTPClient http;
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
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("WiFi connected! IP address: %s\n", WiFi.localIP().toString().c_str());
}
