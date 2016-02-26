#define IRpinR 3
#define IRpinF 2
#define IRpinL 1

//Motor Pins
#define speedPinR 9
#define directionPinR 8
#define speedPinL 10
#define directionPinL 11

#include "PololuWheelEncoders.h"

// Encoder Pins
#define encRA 2
#define encRB 3
#define encLA 5
#define encLB 4

PololuWheelEncoders enc;

#define DEBUG 1

void setup() {
  Serial.begin(9600);  
  enc.init(encRA, encRB, encLA, encLB);
  forward(1);
}

void loop() {
  
}

void forward(int cells){
  
  int dist = 0;
  while(dist<130*cells){
    Serial.println(dist);
    dist = ((enc.getCountsM1() / 12) + (enc.getCountsM1() / 12))/2;
    int vR = analogRead(IRpinR);
    int vF = analogRead(IRpinF);
    int vL = analogRead(IRpinL);
  
    int err;
  
    if (vR < 200){
     // Serial.println("No right wall");
      err = 450 - vL;
    }
    else if(vL < 200){
      //Serial.println("No left wall");
      err = 450 - vR;
    }
    else{
     // Serial.println("2 walls");
      err = vR - vL;  
    }
    
    int fixed = map(err, -128, 128, -15, 30);
    //Serial.println(fixed);
    
    setMotors(127+fixed, 127-fixed);
  }

  offReset();
}

void setMotors(int speedR, int speedL){
  bool rRev = speedR>0;
  bool lRev = speedL>0;
  
  digitalWrite(directionPinR, rRev);
  digitalWrite(directionPinL, lRev);
  delay(5);
  analogWrite(speedPinR, abs(speedR));
  analogWrite(speedPinL, abs(speedL)-10);
}

void offReset(){
  analogWrite(speedPinR, 0);
  analogWrite(speedPinL, 0);
  delay(500);
  enc.getCountsAndResetM1();
  enc.getCountsAndResetM2();

}
