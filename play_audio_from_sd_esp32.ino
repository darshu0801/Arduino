#define SD_CS_PIN 5
#define AUDIO_DEBUG

/*********************************************************/
#include <SPI.h>
#include <SD.h>
#include <AutoAnalogAudio.h>
/*********************************************************/
AutoAnalog aaAudio;
File myFile;
/*********************************************************/
#include "myWAV.h"
/*********************************************************/
//File f = SD.open("/test.wav", FILE_READ);
void setup() {

  Serial.begin(115200);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD init failed!");
    return;
  }
  Serial.println("SD ok\nAnalog Audio Begin");

  aaAudio.begin(0, 1);     // Start AAAudio with only the DAC
  aaAudio.autoAdjust = 0;  // Disable automatic timer adjustment

}

/*********************************************************/

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    switch (input) {

      case '1':  playAudio("/test.wav");  break; //Play a *.wav file by name - 8bit, 24khz, Mono
      case '5':  channelSelection = 0;      break; //Play the audio on DAC0
      case '6':  channelSelection = 1;      break; //Play the audio on DAC1
      case '7':  channelSelection = 2;      break; //Play the audio on DAC0 & DAC1
      case '8': Serial.println("OK");       break;
    }
  }
}
