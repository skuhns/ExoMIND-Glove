

#include "MPU6050.h"
#include "I2Cdev.h"
#include "Wire.h"
//#include "CurieIMU.h"

MPU6050 accelgyroIC1(0x68); // default I2C address 0x69 when inactive HIGH   //don't I need to have 2 declared???
int16_t ax,ay,az;
int count;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("begin");

  Wire.begin();
  while(!Serial){}
  accelgyroIC1.initialize(); //default I2C address 0x68 when active LOW
  Serial.print("begin");
  count = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  accelgyroIC1.getAcceleration(&ax,&ay,&az);
  delay(100);
  Serial.print("x y and z");
  Serial.println(count);
  Serial.println(ax);
  Serial.println(ay);
  Serial.println(az);
  count++;
  
}
