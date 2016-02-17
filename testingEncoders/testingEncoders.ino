#include "PololuWheelEncoders.h"
#define encRA 2
#define encRB 3
#define encLA 5
#define encLB 4
PololuWheelEncoders enc;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  enc.init(encRA, encRB, encLA, encLB);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("R: ");
  Serial.print(enc.getCountsM1() / 12);
  Serial.print(" L: ");
  Serial.println(enc.getCountsM2() / 12);
}
