/*
Copyright (C) 2012 James Coliz, Jr. <maniacbug@ymail.com>
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 Update 2014 - TMRh20
 */
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
RF24 radio(9,10); // nRF24L01(+) radio attached using Getting Started board
RF24Network network(radio); // Network uses that radio
const uint16_t this_node = 0; // Address of our node
const uint16_t other_node = 1; // Address of the other node
struct payload_t { // Structure of our payload
  unsigned long ms;
  unsigned long counter;
     
};
void setup(void)
{
  Serial.begin(57600);
  Serial.println("RF24Network/examples/helloworld_rx/");
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}
void loop(void){
  network.update(); // Check the network regularly
  while ( network.available() ) { // Is there anything ready for us?
    RF24NetworkHeader header; // If so, grab it and print it out
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    Serial.print("Received packet #");
    Serial.print(payload.counter);
    //Serial.print(" at ");
    //Serial.println(payload.ms);
   // Serial.println("      Value = "+payload.value);
  }
}

