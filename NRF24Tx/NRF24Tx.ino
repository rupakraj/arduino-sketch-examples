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

const uint16_t this_node = 02;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already
int temp1,temp2,humid1,humid2;

struct payload_t {   // Structure of our payload
  unsigned int stationid;
  unsigned long temp;
  unsigned long humi;
};

void setup(void)
{
  Serial.begin(57600);
  delay(2000);
  Serial.println("RF24Network/examples/helloworld_tx/");
  tempSensor.attach(A0);
  delay(2000);
  SPI.begin();
  delay(2000);
  radio.begin();
  delay(2000);
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  delay(2000);
}

void loop() {

  network.update();                          // Check the network regularly

  unsigned long now = millis();              // If it's time to send a message, send it!

  readTemp(now);



  if ( now - last_sent >= interval  )
  {
    last_sent = now;

    Serial.print("Sending...");
    payload_t payload = { 
      2 ,
      temp1,
      humid1
    };
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok = network.write(header,&payload,sizeof(payload));
    if (ok){
      Serial.print("OK...");
      Serial.print("T=");
      Serial.print(temp1);
      Serial.print("H=");
      Serial.println(humid1);
    }
    else
      Serial.println("failed.");
  }
}
void readTemp(long now)
{


  tempSensor.update();


  switch (tempSensor.getLastError())
  {
  case DHT_ERROR_OK:
    // sensor.getTemperatureInt()
    // sensor.getHumidityInt()
    temp1  = tempSensor.getTemperatureInt();
    humid1 = tempSensor.getHumidityInt();
    return;
    if ( now - last_sent >= interval-interval/2  ){
      temp1  = tempSensor.getTemperatureInt();
      humid1 = tempSensor.getHumidityInt();
    }
    else{
      temp2  = tempSensor.getTemperatureInt();
      humid2 = tempSensor.getHumidityInt();
    }
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
