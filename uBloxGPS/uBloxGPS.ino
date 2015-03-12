//uBlox Neo 6M
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial gpsSerial(4, 3); // RX, TX

void setup()
{ 
  Serial.begin(9600); 
  gpsSerial.begin(9600); 
  Serial.println("GPS uBloxGPS");
}

void loop() // run over and over
{
  bool newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    //Serial.println("Inside for");
    while (gpsSerial.available())
    {
      char c = gpsSerial.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  //Serial.println(newData);
  if(newData){
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat 
      == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon 
      == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() 
      == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.println(gps.hdop() 
      == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  delay(5000);
}
