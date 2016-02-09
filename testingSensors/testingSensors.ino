int IRpin = A0;                                    // analog pin for reading the IR sensor

void setup() {
  Serial.begin(9600);                             // start the serial port
}

void loop() {
  int value = analogRead(IRpin);   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  
  Serial.println(value);                       // print the distance
  delay(100);                                     // arbitary wait time.
}
