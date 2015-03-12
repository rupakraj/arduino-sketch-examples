#include<Servo.h>

Servo servoX;
Servo servoY;

//PIN
int JAYS_PUSH = 2;
int JAYS_Y    = 0;  // analog A0
int JAYS_X    = 1;  // analog A0
int SERVO_X     = 9;
int SERVO_Y     = 10;

int servo_pos_x = 0;
int servo_pos_y = 0;
int jays_val_x = 0;
int jays_val_y = 0;


void setup(){ 
  //pin mode
  pinMode(SERVO_X,OUTPUT);
  pinMode(SERVO_Y,OUTPUT);
  pinMode(JAYS_PUSH,INPUT);
  //initalize
  servoX.attach(SERVO_X);
  servoY.attach(SERVO_Y);
  Serial.begin(9600);
  delay(2000);
}

void loop(){
  
  jays_val_x = analogRead(JAYS_X);
  jays_val_y = analogRead(JAYS_Y);

  servo_pos_x = map(jays_val_x, 0, 1023, 0, 180); // scaling in the rage of 0 to 180
  servo_pos_y = map(jays_val_y, 0, 1023, 0, 180); // scaling in the rage of 0 to 180
  delay(10);
  servoX.write(servo_pos_x);
  servoY.write(servo_pos_y);  
  
  
//  int btn = digitalRead(JAYS_PUSH);
//  Serial.print("PIN:");
//  Serial.println(btn);
//  if(btn==0){
//    Serial.println("Inside"); 
//    if(pos==90) pos =10;
//    else pos = 90;
//    myservo.write(pos);
//    delay(100);
//  }
//  
  delay(100);
}
