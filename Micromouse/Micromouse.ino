/*
  Stevens IEEE 2016
  Bryan Charalambous
*/

#include <PID_v1.h>
#include "PololuWheelEncoders.h"

//Pin definitions
#define speedPinR 9
#define directionPinR 8
#define speedPinL 10
#define directionPinL 11
#define encRA 2
#define encRB 3
#define encLA 5
#define encLB 4

// Define PID constants
#define buff 15
#define DIST 140

#define kp 2.5
#define ki .15
#define kd .30

PololuWheelEncoders enc;

// Define Variables we'll be connecting the PIDs to
double SetpointR, InputR, OutputR;
double SetpointL, InputL, OutputL;

double setX, InputX, OutputX;
double setY, InputY, OutputY;

byte extraR = 0;
byte extraL = 0;
// Setup the PID loops with
PID rightPID(&InputR, &OutputR, &SetpointR, kp, ki, kd, DIRECT);
PID leftPID(&InputL, &OutputL, &SetpointL, kp, ki, kd, DIRECT);

PID xPID(&InputX, &OutputY, &setX, kp, ki, kd, DIRECT);
PID yPID(&InputL, &OutputL, &setY, kp, ki, kd, DIRECT);

void setup() {
  setX = 1;
  setY = 1;
  // Start up the encoder library
  enc.init(encRA, encRB, encLA, encLB);
  
  //turn the PID on
  rightPID.SetMode(AUTOMATIC);
  leftPID.SetMode(AUTOMATIC);
  rightPID.SetOutputLimits(-255, 255);
  leftPID.SetOutputLimits(-255, 255);

  rightPID.SetMode(AUTOMATIC);
  leftPID.SetMode(AUTOMATIC);
  xPID.SetOutputLimits(5, 13);
  yPID.SetOutputLimits(5, 13);
  
 Serial.begin(9600);

  //reverse(1);
  forward(1);
  delay(2000);
  reverse(1);
  delay(2000);
  forward(1);
}

void loop() {


}

void forward(int cells){
  move(DIST*cells, DIST*cells);
}

void reverse(int cells){
  move(-1*DIST*cells, -1*DIST*cells);
}

void turn(int quarters){
 
}

void move(int right, int left) {
   Serial.print(" Y ");
  SetpointR = right;
  SetpointL = left;
  bool rrev = right < 0;
  bool lrev = left < 0;


  float x;
  float y;
  
  while(deltas(SetpointR, InputR)>10){
    InputR = enc.getCountsM1() / 12;
    InputL = enc.getCountsM2() / 12;
    
    x = (float)InputR/(float)InputL;
    y = InputL/InputR;
    
    rightPID.Compute();
    leftPID.Compute();
    xPID.Compute();
    yPID.Compute();

    setMotors(OutputX*OutputR, OutputY*OutputL);
    Serial.print(" Xo ");
    Serial.print(OutputX);
    Serial.print(" Yo ");
    Serial.println(OutputY);
    Serial.print(" Xi ");
    Serial.println(InputR);
    Serial.print(" Yi ");
    Serial.println(InputY);
  }
 
  offReset();
}

int deltas(int a, int b){
  return abs(a) - abs(b);
}

void offReset(){
  
  setMotors(0, 0);
  delay(500);
  
//  Serial.print("Resetting now, current values: M1 ");
//  Serial.print(enc.getCountsM1()/12);
//  Serial.print(" M2 ");
//  Serial.println(enc.getCountsM2()/12);
//  
  enc.getCountsAndResetM1();
  enc.getCountsAndResetM2();
  InputR = 0;
  InputL = 0;
}

void setMotors(int speedR, int speedL){
  bool rRev = speedR>0;
  bool lRev = speedL>0;
 
  digitalWrite(directionPinR, rRev);
  digitalWrite(directionPinL, lRev);
  delay(5);
  analogWrite(speedPinR, abs(speedR));
  analogWrite(speedPinL, abs(speedL));
 
  
}
