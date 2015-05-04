int BuzerPort = 3 ; // PWM

void setup(){
  pinMode(BuzerPort, OUTPUT);
}

void loop(){
  play();
}

void play(){
  int notes=8;  
  // 255
  int frequencies[] = {500, 690, 500, 400, 400, 440, 494, 523};
  
  for(int i=0;i<notes;i++){
    
    analogWrite(BuzerPort,frequencies[i]);
    delay(100);
    analogWrite(BuzerPort,frequencies[i]);
    delay(100);
    
  }
  analogWrite(BuzerPort,0);
  
}
