#Used Library

##Installation
 - Find TinyGPS https://github.com/mikalhart/TinyGPS

 - Put the cloned folder into the library of the Arduino installation.

##Consider following configuration

	uBlox Modules	|	Uno
	------------------------
	1 = GND			|	GND
	2 = Rx			|	3
	3 = Tx			|	4
	4 = VCC (+5V)	|	+5v



###Declare gps as a TinyGPS object
	TinyGPS gps;

###Declare gpsSerial on pins 4 and 3
	SoftwareSerial gpsSerial(4, 3); // RX, TX

###Set the rate of transfer as 9600

###Read gps data and then encode
	gpsSerial.read();
	gps.encode(c);

###Display data inside the loop throught the encoded gps object

Enjoy Code :P