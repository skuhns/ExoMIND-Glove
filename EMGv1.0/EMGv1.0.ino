//DIY EMG TESTER
#include "math.h"
#include "Wire.h"
//#include "CurieIMU.h"


int emg=0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  pinMode(A1,INPUT);
  delay(5);
  Serial.begin(9600);
  while(!Serial){}

}

void loop() {
  emg = analogRead(A1);
  Serial.print("EMG:");
  Serial.println(emg);
  delay(300);
  // put your main code here, to run repeatedly:

}
