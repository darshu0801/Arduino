#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define RX_PIN 15
#define TX_PIN 2
#define BAUD_RATE 9600

HardwareSerial gpsSerial(1);
TinyGPSPlus gps;
float latitude, longitude;

const char* ssid = "DBKS";
const char* password = "Babu@08012003";

void setup() {
  Serial.begin(9600);
  connectWiFi();
  gpsSerial.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
}

void loop() {
  if (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      String address = reverseGeocode(latitude, longitude);
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);
      Serial.print("Address: ");
      Serial.println(address);
    }
  }
}

String reverseGeocode(float lat, float lng) {
  String result = "";
  WiFiClient client;
  HTTPClient http;
  String url = "http://api.opencagedata.com/geocode/v1/json?q=" + String(lat) + "+" + String(lng) + "&key=6ed70ca170dc47c28f177c7968185bb7";
  http.begin(client, url);
  result = http.getString();
  //String extractedString = extractString(answer);
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
