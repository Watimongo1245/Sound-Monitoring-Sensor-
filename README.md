# Sound Monitoring Sensor
This is a record of what progress we have made in the design of the sound monitoring sensor. We will review the methodology and the results from the tests we carried out and recommendations of what works best. 


**Resources** 

•	Compilation of all Codes used  is found here.
•	ESP32 , Raspberry pi, Arduino Uno, MAX4466, MAX9814, and SPH0645
Design requirements
•	record quality sound to SD CARD
•	 measure dB SPL
•	Upload Measured dB SPL to Thingspeak/ Any cloud server
•	Upload recorded sound from SD CARD



**Testing Analog Microphones MAX4466 and MAX9814 and Arduino Uno
Connections:**

SD Card Module Pin	Arduino Uno pin
CS	4
MISO	11
SCK	13
MOSI	12
GND	GND
VCC	5V

MAX4466 PIN CONFIGURATION
OUT	A1
VCC	VCC
GND	5V

MAX9814 PIN CONFICURATION
OUT	A1
GAIN	5V  (40 dB gain)
VCC	5V
GND	GND



Find Code [here ](https://github.com/Watimongo1245/Sound-Monitoring-Sensor-/blob/main/Arduino_Uno_MAX446.ino#L3): 

Results

•	Able to measure dB SPL ranges from 46 – 76 dB SPL
•	We successfully recorded sound to SD card 
•	Sound quality of MAX9814 is better than that of MAX4466

**Using ESP32 Microcontroller**

Using the ESp32, we tried to write I2S data signals from the SPH0645 microphone to the SD Card as well as measure dB SPL values. 


The code used for testing is [here](https://github.com/Watimongo1245/Sound-Monitoring-Sensor-/blob/main/I2S.ino).


Connection and Configuration
SD Card Module	ESP32 pin configuration
CS	5
SCLK	18
MISO	19
MOSI	23
VCC	VIN
GND	GND

SPH0645 PIN CONFIGURATION
VCC	3.3V
GND	GND
WS/ LRCLK	35
SD	33
SCK	32
SEL	Not connected ( listen to Right Channel)

Results
•	Able to measure dB SPL 26 – 180 SPL
•	Failed to record sound to SD Card
•	ESP32 got overloaded with memory.

**Using Raspberry Pi, Sound Card, and condenser microphone**

with  the Raspberry pi, we tried to achieve the design specifications of sound monitoring device

Configuration

Microphone via USB sound Card	Raspberry pi
USB 2.0 	USB port

Results

•	Recorded quality sound with the USB microphone
•	Uploaded dB SPL values to a server using Node red
•	Current dB range: 26 – 65 dB SPL
