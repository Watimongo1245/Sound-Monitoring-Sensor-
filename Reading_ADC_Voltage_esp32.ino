#include "Arduino.h"
#include <ESP32AnalogRead.h>

ESP32AnalogRead adc; // You will need to install the ESP32AnalogRead library from the library manger

void setup()
{
	adc.attach(33);
	Serial.begin(115200);
}

void loop()
{
	delay(50);
	Serial.println("Voltage = "+String(adc.readVoltage()));
}
