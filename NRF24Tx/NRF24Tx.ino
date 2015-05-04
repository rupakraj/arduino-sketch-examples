/*
 Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 Update 2014 - TMRh20
 */

/**
 * Simplest possible example of using RF24Network 
 *
 * TRANSMITTER NODE
 * Every 2 seconds, send a payload to the receiver node.
 */

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <dht.h>

DHT tempSensor = DHT();

RF24 radio(7,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 04;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent=0;             // When did we last send?
unsigned long packets_sent=0;          // How many have we sent already
int temp1,temp2,humid1,humid2;
int DEV_1 = 4;
int BuzerPort = 9;



struct payload_t {   // Structure of our payload
  unsigned int stationid;
  unsigned long temp;
  unsigned long humi;
};

void setup(void)
{
  Serial.begin(57600);
  //delay(2000);
  Serial.println("RF24Network/examples/helloworld_tx/");
  tempSensor.attach(A1);
  //delay(2000);
  SPI.begin();
  //delay(2000);
  radio.begin();
  //delay(2000);
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  //pinMode(DEV_1, OUTPUT);
  delay(2000);
}

void loop() {
  delay (2000);
  unsigned long now = millis();              // If it's time to send a message, send it!
  readTemp(now);  
  //Serial.println(now);
  //  Serial.println(temp1);

  network.update();                          // Check the network regularly
  //Serial.println("Updated Network");


  //if ( now - last_sent >= interval  )
  //{
  last_sent = now;

  Serial.print("Sending...");
  payload_t payload = { 
    this_node ,
    temp1,
    humid1
  };
  RF24NetworkHeader header(/*to node*/ other_node);
  bool ok = network.write(header,&payload,sizeof(payload));
  //digitalWrite(DEV_1,HIGH);
  //delay(1000);
  //digitalWrite(DEV_1,LOW);
  if (ok){
    Serial.print("OK...");
    Serial.print("T=");
    Serial.print(temp1);
    Serial.print("H=");
    Serial.println(humid1);
    play(BuzerPort);
  }
  else{
    Serial.println("failed.");
    Serial.print("T=");
    Serial.print(temp1);
    Serial.print("H=");
    Serial.println(humid1);
  }
  //}
}
void readTemp(long now)
{
  temp1=10;
  humid1=20;
  return;

  tempSensor.update();


  switch (tempSensor.getLastError())
  {
  case DHT_ERROR_OK:
    // sensor.getTemperatureInt()
    // sensor.getHumidityInt()
    temp1  = tempSensor.getTemperatureInt();
    //return;
    //Serial.println(msg);
    break;
  case DHT_ERROR_START_FAILED_1:
    //Serial.println("Error: start failed (stage 1)");
    break;
  case DHT_ERROR_START_FAILED_2:
    //Serial.println("Error: start failed (stage 2)");
    break;
  case DHT_ERROR_READ_TIMEOUT:
    //Serial.println("Error: read timeout");
    break;
  case DHT_ERROR_CHECKSUM_FAILURE:
    //Serial.println("Error: checksum error");
    break;
  }

}

void play(int BuzerPort){
  int notes=8;  
  // 255
  int frequencies[] = {
    500, 690, 500, 400, 400, 440, 494, 523    };

  //  for(int i=0;i<notes;i++){
  for(int i=0;i<2;i++){

    analogWrite(BuzerPort,frequencies[i]);
    delay(10);
    analogWrite(BuzerPort,frequencies[i]);
    delay(10);
  }
  analogWrite(BuzerPort,0);

}



