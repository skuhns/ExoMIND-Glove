//Example code for configuring 6 seperate MPU6050 accelerometers
/* Author(s): Samuel Kuhns
*  Date: 07/31/2017
*  This code is based off the Jeff Rowberg I2Cdev.h and MPU6050.h library files
*  This code has not been tested and is only for reference
*
 */
/*
 * This is used in tandem with the matlab GUI to display 5 bar graphs representing the % extension of the 5 fingers
 */
 /*
  * Offsets for individual MIND MPU's are as follows
  * Data is printed as: acelX acelY acelZ 
  * *********OFFSETS FOUND BEFORE CONTAINMENT RINGS WERE SECURED************
  * 
  * MPU Central (With plastic tie)  
      accelgyroIC1.setXAccelOffset(-552);
      accelgyroIC1.setYAccelOffset(-4848); 
      accelgyroIC1.setZAccelOffset(1546);
  * 
  * 
  * MPU 1
      accelgyroIC1.setXAccelOffset(-1388);
      accelgyroIC1.setYAccelOffset(-1390); 
      accelgyroIC1.setZAccelOffset(1613);
  * 
  * 
  * MPU 2
      accelgyroIC1.setXAccelOffset(-3531);
      accelgyroIC1.setYAccelOffset(-6565); 
      accelgyroIC1.setZAccelOffset(1717);

    MPU 3
      accelgyroIC1.setXAccelOffset(-1563);
      accelgyroIC1.setYAccelOffset(-257); 
      accelgyroIC1.setZAccelOffset(1602);

    MPU 4
      accelgyroIC1.setXAccelOffset(-1195);
      accelgyroIC1.setYAccelOffset(734); 
      accelgyroIC1.setZAccelOffset(1016);

    MPU 5
      accelgyroIC1.setXAccelOffset(-1662);
      accelgyroIC1.setYAccelOffset(-1299); 
      accelgyroIC1.setZAccelOffset(818);

    MPU Palm (with white velcro)
      accelgyroIC1.setXAccelOffset(-836);
      accelgyroIC1.setYAccelOffset(-2474); 
      accelgyroIC1.setZAccelOffset(490);
    
  * 
  */
 
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"
#include "Wire.h"
#include "CurieIMU.h"

//#include <SoftwareSerial.h> // added to try and solve issues
#define OUTPUT_READABLE_ACCELGYRO
 
/*Declare digital pins to connect to AD0 pin on MPU6050*/
int MPU6050_central = 8;  //digital pin 8
int MPU6050_palm = 7; //digital pin 7
int MPU6050_2 = 2; //digital pin 2
int MPU6050_3 = 3; //digital pin 3
int MPU6050_4 = 4; //digital pin 4
int MPU6050_5 = 5; //digital pin 5
int MPU6050_6 = 6; //digital pin 6


int state = 0;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t ac1_x, ac1_y, ac1_z, ac2_x, ac2_y, ac2_z, ac3_x, ac3_y, ac3_z, ac4_x, ac4_y, ac4_z, ac5_x, ac5_y, ac5_z, acc_x, acc_y, acc_z, acp_x, acp_y, acp_z;
int emg= 622;
 
// Declare I2C device with corresponding address
MPU6050 accelgyroIC1(0x68); // default I2C address 0x69 when inactive HIGH   //don't I need to have 2 declared???
MPU6050 accelgyroIC2(0x69); //default I2C address 0x68 when active LOW

void setup() {
  // put your setup code here, to run once:

 
  Wire.begin();

 
  Serial.begin(38400);
  while(!Serial){}
 
accelgyroIC1.initialize(); //default I2C address 0x68 when active LOW
accelgyroIC2.initialize(); // default I2C address 0x68 when inactive HIGH  

// Verify Connection
Serial.println("Testing device connections...");
 
 
  pinMode(MPU6050_central,OUTPUT);
  pinMode(MPU6050_palm,OUTPUT);
  pinMode(MPU6050_2,OUTPUT);
  pinMode(MPU6050_3,OUTPUT);
  pinMode(MPU6050_4,OUTPUT);
  pinMode(MPU6050_5,OUTPUT);
  pinMode(MPU6050_6,OUTPUT);
  pinMode(A1,INPUT);
  delay(500);
}

 
void loop() {
  getNumbers();

  ac1_z = ((ac1_z+9.81)/9.81) * 100.0;
  ac2_z = ((ac2_z+9.81)/9.81) * 100.0;
  ac3_z = ((ac3_z+9.81)/9.81) * 100.0;
  ac4_z = ((ac4_z+9.81)/9.81) * 100.0;
  ac5_z = ((ac5_z+9.81)/9.81) * 100.0;

  
  Serial.print(ac1_z); 
  Serial.print(" ");
  Serial.print(ac2_z); 
  Serial.print(" ");
  Serial.print(ac3_z);
  Serial.print(" ");
  Serial.print(ac4_z); 
  Serial.print(" ");
  Serial.print(ac5_z);
  Serial.print(" ");
  Serial.println(emg);
  delay(5);
}


void getNumbers() {
  emg = analogRead(A1);
  for (int c = 1; c <= 7; c++){
    //Reset the address of all devices
    digitalWrite(MPU6050_central,HIGH);
    digitalWrite(MPU6050_palm,HIGH);
    digitalWrite(MPU6050_2,HIGH);
    digitalWrite(MPU6050_3,HIGH);
    digitalWrite(MPU6050_4,HIGH);
    digitalWrite(MPU6050_5,HIGH);
    digitalWrite(MPU6050_6,HIGH);
  
    delay(15);
    if (c == 1){
      digitalWrite(MPU6050_central,LOW);// set MPU6050 # 1 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-552);
      accelgyroIC1.setYAccelOffset(-4848); 
      accelgyroIC1.setZAccelOffset(1546);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer Central");
     
    }
    else if (c == 2){
      digitalWrite(MPU6050_2,LOW);// set MPU6050 # 2 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(1589);
      accelgyroIC1.setYAccelOffset(-1343); 
      accelgyroIC1.setZAccelOffset(830);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 2");
    }
   else if (c == 3){
    digitalWrite(MPU6050_3,LOW);// set MPU6050 # 3 as the device being read
      delay(15);
      
      accelgyroIC1.setXAccelOffset(-1309);
      accelgyroIC1.setYAccelOffset(-1403); 
      accelgyroIC1.setZAccelOffset(1660);
    
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 3");
 
  }
  else if (c == 4){
    digitalWrite(MPU6050_4,LOW);// set MPU6050 # 4 as the device being read
      delay(15);
  
      accelgyroIC1.setXAccelOffset(-12563);
      accelgyroIC1.setYAccelOffset(-2227); 
      accelgyroIC1.setZAccelOffset(12542);
     
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 4");
  }
  else if (c == 5){
    digitalWrite(MPU6050_5,LOW);// set MPU6050 # 5 as the device being read
    delay(15);

      accelgyroIC1.setXAccelOffset(-195);
      accelgyroIC1.setYAccelOffset(734); 
      accelgyroIC1.setZAccelOffset(-100);
   
    accelgyroIC1.getAcceleration(&ax,&ay,&az);
    //Serial.println("Accelerometer 5");
  }
    else if (c == 6){
    digitalWrite(MPU6050_6,LOW);// set MPU6050 # 5 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-1011);
      accelgyroIC1.setYAccelOffset(688); 
      accelgyroIC1.setZAccelOffset(905);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 6");
  }
  else if (c == 7){
    digitalWrite(MPU6050_palm,LOW);// set MPU6050 # 5 as the device being read
     delay(15);

      accelgyroIC1.setXAccelOffset(-836);
      accelgyroIC1.setYAccelOffset(-2474); 
      accelgyroIC1.setZAccelOffset(490);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer Palm");
  }
  // THIS ADJUSTS RAW VALUES TO GIVE m/s^2// (we probably just want angles in final output)
  switch(c) {
    case 1:
      acc_x = (ax/16384.00)*9.81;
      acc_y = (ay/16384.00)*9.81;
      acc_z = (az/16384.00)*9.81;
      //Serial.println(acc_x);
      //Serial.println(acc_y);
      //Serial.println(acc_z);
      break;
    case 2:
      ac1_x = (ax/16384.00)*9.81;
      ac1_y = (ay/16384.00)*9.81;
      ac1_z = (az/16384.00)*9.81;
      //Serial.println(ac1_x);
      //Serial.println(ac1_y);
      //Serial.println(ac1_z);
      break;
  case 3:
      ac  2_x = (ax/16384.00)*9.81;
      ac2_y = (ay/16384.00)*9.81;
      ac2_z = (az/16384.00)*9.81;
      //Serial.println(ac2_x);
      //Serial.println(ac2_y);
      //Serial.println(ac2_z);
      break;
  case 4:
      ac3_x = (ax/16384.00)*9.81;
      ac3_y = (ay/16384.00)*9.81;
      ac3_z = (az/16384.00)*9.81;
      //Serial.println(ac3_x);
      //Serial.println(ac3_y);
      //Serial.println(ac3_z);
      break;
  case 5:
      ac4_x = (ax/16384.00)*9.81;
      ac4_y = (ay/16384.00)*9.81;
      ac4_z = (az/16384.00)*9.81;
      //Serial.println(ac4_x);
      //Serial.println(ac4_y);
      //Serial.println(ac4_z);
      break;
  case 6:
      ac5_x = (ax/16384.00)*9.81;
      ac5_y = (ay/16384.00)*9.81;
      ac5_z = (az/16384.00)*9.81;
      //Serial.println(ac5_x);
      //Serial.println(ac5_y);
      //Serial.println(ac5_z);
      break;
  case 7:
      acp_x = (ax/16384.00)*9.81;
      acp_y = (ay/16384.00)*9.81;
      acp_z = (az/16384.00)*9.81;
      //Serial.println(acp_x); 
      //Serial.println(acp_y);
      //Serial.println(acp_z);
      break;    
  }
  /*
  ac_x = (ax/16384.00)*9.81;
  ac_y = (ay/16384.00)*9.81;
  ac_z = (az/16384.00)*9.81;
  Serial.println(ac_x);
  Serial.println(ac_y);
  Serial.println(ac_z);
  */
  
  //delay(10); //10 microsecond delay to prevent simultaneous reading and writing on I2C bus
  }
}


 
 

 
  


