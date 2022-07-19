/*
  Adapted from Example from ThingSpeak Library (Mathworks)
  
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include "ThingSpeak.h"
 

const char* ssid = " SSID";   // your network SSID (name) 
const char* password = "Password";   // your network password
int sample;

WiFiClient  client;

unsigned long myChannelNumber = 123456;// enter appropriate channel Number
const char * myWriteAPIKey = "type your API Key here";

//Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
int SampleWindow = 20;

 
float dB_Sound;
 

 

void setup() {
  Serial.begin(115200);  //Initialize serial
//  initBME();
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 4095;

   // collect data for 50 mS
   while (millis() - lastTime < SampleWindow)
   {
      sample = analogRead(35); // Where the analog pin to the MAX9814 / MAX4466 is connected.
     
      if (sample < 4096)  // toss out spurious readings
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
   float volts = ((peakToPeak * 5) / 4095); // * 0.707;  // convert to RMS voltage
   float first = log10(volts/0.00631)*20;
   float second1 = first + 94 - 44 - 25;
    
    

     
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber,1,second1, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
      Serial.println(String(sample) +"  "+ String(signalMax)+ "  "+ String(signalMin));
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
