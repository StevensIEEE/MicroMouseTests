/*
Stevens IEEE 2016
Bryan Charalambous
*/

int directionPinR = 8;
int speedPinR = 9;

int directionPinL = 11;
int speedPinL = 10;

void setup() {
 pinMode(directionPinR, OUTPUT);
 pinMode(speedPinR, OUTPUT);
 pinMode(directionPinL, OUTPUT);
 pinMode(speedPinL, OUTPUT);
 setMotors(0, false);
}

void loop() {
  delay(2000);
  setMotors(50, false);
  delay(2000);
  setMotors(255, true);
  
}

void setMotors(int speed, boolean reverse)
{
  setMotorR(speed, reverse);
  setMotorL(speed, reverse);  
}

void setMotorR(int speed, boolean reverse)
{
  analogWrite(speedPinR, speed);
  digitalWrite(directionPinR, reverse);
}

void setMotorL(int speed, boolean reverse)
{
  analogWrite(speedPinL, speed);
  digitalWrite(directionPinL, reverse);
}
