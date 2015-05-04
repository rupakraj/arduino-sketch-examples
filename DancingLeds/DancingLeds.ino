/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 8;
int led2 = 9;
int led3 = 10;


// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(led2, OUTPUT);     
  pinMode(led3, OUTPUT);       
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led3, LOW);
  Serial.println("Sent");
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  
  Serial.println("Sent");
  
  delay(1000);               // wait for a second
  
}

