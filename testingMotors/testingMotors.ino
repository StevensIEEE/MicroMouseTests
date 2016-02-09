/*
Stevens IEEE 2016
Bryan Charalambous
*/
 
int speedPinR = 5;
int directionPinR = 4;

int speedPinL = 6;
int directionPinL = 7;
 
void setup()
{
  pinMode(directionPinR, OUTPUT);
  pinMode(speedPinR, OUTPUT);

  pinMode(directionPinL, OUTPUT);
  pinMode(speedPinL, OUTPUT);

}
 
void loop()
{
  setMotors(50, false);
  delay(2000);
  setMotors(255, true);
  delay(2000);
}

void setMotors(int speed, boolean reverse)
{
  setMotorR(speed, reverse);
  setMotorL(speed, ! reverse);
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
