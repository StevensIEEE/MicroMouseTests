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
#define DEBUG 1
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

// Setup the PID loops with
PID rightPID(&InputR, &OutputR, &SetpointR, kp, ki, kd, DIRECT);
PID leftPID(&InputL, &OutputL, &SetpointL, kp, ki, kd, DIRECT);

void setup() {
  
  // Start up the encoder library
  enc.init(encRA, encRB, encLA, encLB);
  
  //turn the PID on
  
  rightPID.SetOutputLimits(-255, 255);
  leftPID.SetOutputLimits(-255, 255);
  
  if (DEBUG==1) Serial.begin(9600);

 //reverse(1);
  
 //forward(1);

 turn(1);
}

void loop(){
  
}

void forward(int cells){
  move(cells * 140, cells * 140);
}

void reverse(int cells){
  move(-1 * cells * 140, -1 * cells * 140);
}

void turn(int quarters){
  move(-44*quarters, 43*quarters);
}

void move(int right, int left){
  rightPID.SetMode(AUTOMATIC);
  leftPID.SetMode(AUTOMATIC);
  SetpointR = abs(right);
  SetpointL = abs(left);

  int reverseR = 1;
  int reverseL = 1;
  if (right < 0){
    reverseR = -1;
  }
  if (left < 0){
    reverseL = -1;
  }
  
  InputR = abs(enc.getCountsM1() / 12);
  InputL = abs(enc.getCountsM2() / 12);
  
  while(InputR < SetpointR && InputL < SetpointL){
    InputR = abs(reverseR*enc.getCountsM1() / 12);
    InputL = abs(reverseL*enc.getCountsM2() / 12);

    rightPID.Compute();
    leftPID.Compute();

    setMotors(OutputR*reverseR, OutputL*reverseL);
    
    Serial.print("Input R: ");
    Serial.print(InputR);
    Serial.print("   Input L: ");
    Serial.print(InputL);
  }
  offReset();
}


void offReset(){
  setMotors(0, 0);
  delay(500);
  enc.getCountsAndResetM1();
  enc.getCountsAndResetM2();
  InputR = 0;
  InputL = 0;
}

void setMotors(int speedR, int speedL){
  bool rRev = speedR>0;
  bool lRev = speedL>0;
  
  if (DEBUG==1){
      Serial.print("  Speed R: ");
      Serial.print(speedR);
      Serial.print("   Speed L: ");
      Serial.println(speedL);
    }
    
  digitalWrite(directionPinR, rRev);
  digitalWrite(directionPinL, lRev);
  delay(5);
  analogWrite(speedPinR, abs(speedR));
  analogWrite(speedPinL, abs(speedL));
  
}
