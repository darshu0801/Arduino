#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;
File file;

const char* ssid = "DBKS";
const char* password =  "Babu@08012003";

// String variable just to do the test
String URL = "https://translate.google.com/translate_tts?ie=UTF-8&q=My+name+is+VEDA,+an+AI+powered+VIRTUALLY+ELECTRONIC+DIGITAL+ASSISTANT&tl=en&client=tw-ob&ttsspeed=1";

String file_name = "/123.wav"; //Random file name just to do the test

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password); // Pass the WIFI parameters and start connection

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

// Start the SD card and check if it is present
  Serial.println("Initializing SD card...");
  if (!SD.begin(5)) { // see if the card is present and can be initialised.
    Serial.println("Card failed or not present, no SD Card data logging possible...");
  }
  else{
    Serial.println("Card initialised... file access enabled...");
  }

  if(WiFi.status() == WL_CONNECTED) {

        Serial.println("[HTTP] Begin...");

        http.begin(URL); //We make the call to the address

        int httpCode = http.GET(); // We capture the code returned by the URL address
       
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

void loop() {
}
