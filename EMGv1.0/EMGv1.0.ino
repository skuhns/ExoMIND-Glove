//DIY EMG TESTER
#include "math.h"
#include "Wire.h"


int emg;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1,INPUT);
  delay(5);
  Serial.begin(9600);
  while(!Serial){}

}

void loop() {
  emg = analogRead(A1);
  //Serial.print("EMG:");
  Serial.println(emg);
  delay(10);
  // put your main code here, to run repeatedly:

}
