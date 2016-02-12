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

// Setup the PID loops with
PID rightPID(&InputR, &OutputR, &SetpointR, kp, ki, kd, DIRECT);
PID leftPID(&InputL, &OutputL, &SetpointL, kp, ki, kd, DIRECT);

void setup() {
  // Start up the encoder library
  enc.init(encRA, encRB, encLA, encLB);
  
  //turn the PID on
  rightPID.SetMode(AUTOMATIC);
  leftPID.SetMode(AUTOMATIC);
  rightPID.SetOutputLimits(-255, 255);
  leftPID.SetOutputLimits(-255, 255);
  
  //Serial.begin(9600);

  //reverse(1);
  
 turn(1);
 delay(500);
 turn(-1);
}

void loop() {

}

void forward(int cells){
  move((cells * DIST) + buff, (cells * DIST) + buff);
}

void reverse(int cells){
  move((-1 * cells * DIST) - buff, (-1 * cells * DIST) - buff);
}

void turn(int quarters){
  move((-45*quarters)-buff, (45*quarters)+buff);
}

void move(int right, int left) {
  SetpointR = right;
  SetpointL = left;
  bool rrev = right < 0;
  bool lrev = left < 0;
  
  int deltaR = deltas(SetpointR, InputR);
  int deltaL = deltas(SetpointL, InputL);
  Serial.println("starting the forward sequence");
  while (deltaR > 12) {
    // get encoder counts and set them into the PID inputs
    InputR = enc.getCountsM1() / 12;
    InputL = enc.getCountsM2() / 12;
    deltaR = deltas(SetpointR, InputR);
    deltaL = deltas(SetpointL, InputL);
    
//    Serial.print("   Input R: ");
//    Serial.print(InputR);
//    Serial.print("   Input L: ");
//    Serial.println(InputL);
    
    // compute the PID outputs
    rightPID.Compute();
    leftPID.Compute();
    
    // use newly computed outputs to set the motor voltages 0-255
    // we also compensate for the difference between each motor to
    // keep the robot in a straight line
    if (deltaR < deltaL) {
      if (rrev) setMotors(OutputR + 3, OutputL);
      else setMotors(OutputR - 3, OutputL);
      
    }
    else {
       if (lrev) setMotors(OutputR, OutputL + 3);
      else setMotors(OutputR, OutputL - 3);
    }
  }
  // we've gone forward the corrent amount of blocks
  // now we shutoff motors, reset counts and set both inputs to 0
  offReset();
}

int deltas(int a, int b){
  return abs(a) - abs(b);
}

void offReset(){
  setMotors(0, 0);
  enc.getCountsAndResetM1();
  enc.getCountsAndResetM2();
  InputR = 0;
  InputL = 0;
}

void setMotors(int speedR, int speedL){
  bool rRev = speedR<0;
  bool lRev = speedL>0;
 
  digitalWrite(directionPinR, rRev);
  digitalWrite(directionPinL, lRev);
  delay(5);
  analogWrite(speedPinR, abs(speedR));
  analogWrite(speedPinL, abs(speedL));
  
}
