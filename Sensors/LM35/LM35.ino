/*
Use: read the LM35 Analog data


Pin Configuration
=================
LM35: Flat surface on top
  1 = Vcc (+5V)
  2 = Output (Analog)
  3 = GND
  
Connection to arduino
=====================
  LM35    Arduino
  2       A0
  1       +5V
  3       GND  

*/

float OutputTemp;
int SENSOR_PIN          = 0;
float CorrectionFactor  = 0.48828125;
int DELAY               = 5000;

void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop()
{
  OutputTemp = analogRead(SENSOR_PIN);
  OutputTemp = OutputTemp /9.31 ;// CorrectionFactor;
  Serial.print("TEMPRATURE = ");
  Serial.print(OutputTemp);
  Serial.print("*C");
  Serial.println();
  delay(DELAY);
}
