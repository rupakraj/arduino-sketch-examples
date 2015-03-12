
#include<SoftwareSerial.h>

SoftwareSerial blueComm(10,11); // Rx, Tx

void setup(){
  Serial.begin(57600);
  blueComm.begin(9600);
  while(!Serial){ ; }
  delay(1000);  
  Serial.println("Initialized");
}
void loop(){
  blueComm.write("Hello world\n");
  delay(2000);
}
