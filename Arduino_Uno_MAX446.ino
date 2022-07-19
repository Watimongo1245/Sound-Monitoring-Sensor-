/*  In this code, it is meant to record sound when you send 'r' through the serial, and
stop recording when you send 's' to the arduino Uno. Sound is stored as 'testTMR.wav' file.

On top of that, it measures dB sound Pressure levels and prints them on the serial monitor

*/

#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 5 
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

TMRpcm audio;   
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  
   Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {  
    Serial.println("There might be a problem");
    return;
  }else{
    Serial.println("SD OK"); 
  }
  
  audio.CSPin = SD_ChipSelectPin;
}


void loop() {
  
 if(Serial.available()){                        
      switch(Serial.read()){
        case 'r': audio.startRecording("testTMR.wav", 16000, A1); break;   
        case 's': audio.stopRecording("testTMR.wav"); break;              
      }
      
    }
    unsigned long startMillis= millis();  // Start of sample window
    while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A1);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = ((peakToPeak * 3.3) / 1024); // * 0.707;  // convert to RMS voltage
   double first = log10(volts/0.00631)*20;
   double second1 = first + 94 - 44 - 25;
   Serial.println(volts);
   if (volts>0){
     Serial.println(second1);
   }

   
}
