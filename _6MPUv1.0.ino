//Example code for configuring 6 seperate MPU6050 accelerometers
/* Author(s): SRIRAM BOPPANA, Jason Ummel
*  Date: 02/19/2017
*  This code is based off the Jeff Rowberg I2Cdev.h and MPU6050.h library files
*  This code has not been tested and is only for reference
*
 */

 /*
  * Offsets for individual MIND MPU's are as follows
  * Data is printed as: acelX acelY acelZ giroX giroY giroZ
  * *********DO NOT TRUST GYRO OFFSETS FROM THIS DATA************
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
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif
//#include <SoftwareSerial.h> // added to try and solve issues
#define OUTPUT_READABLE_ACCELGYRO
 
/*Declare digital pins to connect to AD0 pin on MPU6050*/
int MPU6050_central = 7;  //digital pin 7
int MPU6050_palm = 8; //digital pin 8
int MPU6050_2 = 2; //digital pin 2
int MPU6050_3 = 3; //digital pin 3
int MPU6050_4 = 4; //digital pin 4
int MPU6050_5 = 5; //digital pin 5
int MPU6050_6 = 6; //digital pin 6
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
float ac_x, ac_y, ac_z;
float ax_cor, ay_cor, az_cor;
float ax_m, ay_m, az_m;
float mag;
int emg;
bool blinkState = false;
int azr;
int ayr;
int axr;
 
// Declare I2C device with corresponding address
MPU6050 accelgyroIC1(0x68); // default I2C address 0x69 when inactive HIGH   //don't I need to have 2 declared???
MPU6050 accelgyroIC2(0x69); //default I2C address 0x68 when active LOW


 
    
 
void setup() {
  // put your setup code here, to run once:

 
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
 
  Serial.begin(38400);
 
accelgyroIC1.initialize(); //default I2C address 0x68 when active LOW
accelgyroIC2.initialize(); // default I2C address 0x68 when inactive HIGH  



// Verify Connection
Serial.println("Testing device connections...");
//Serial.println(accelgyroIC1.testConnection()?"MPU6050 1 connection successful": "MPU6050 1 connection failed");
//Serial.println(accelgyroIC2.testConnection()?"MPU6050 2 connection successful": "MPU6050 2 connection failed");
 
 
  pinMode(MPU6050_central,OUTPUT);
  pinMode(MPU6050_palm,OUTPUT);
  pinMode(MPU6050_2,OUTPUT);
  pinMode(MPU6050_3,OUTPUT);
  pinMode(MPU6050_4,OUTPUT);
  pinMode(MPU6050_5,OUTPUT);
  pinMode(MPU6050_6,OUTPUT);
  pinMode(A1,INPUT);
 
 
  delay(5);
 
}
 
void loop() {
 
  emg = analogRead(A1);
  //Serial.println("EMG Reading");
  //Serial.println(emg);
  delay(5);
  
  for (int c = 1; c <= 7; c++){                            //alter this depending on how many we are reading in (we want 6 eventually)
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
      Serial.println("Accelerometer Central");
     
    }
    else if (c == 2){
      digitalWrite(MPU6050_2,LOW);// set MPU6050 # 2 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-1388);
      accelgyroIC1.setYAccelOffset(-1390); 
      accelgyroIC1.setZAccelOffset(1613);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 2");
    }
   else if (c == 3){
    digitalWrite(MPU6050_3,LOW);// set MPU6050 # 3 as the device being read
      delay(15);
      
      accelgyroIC1.setXAccelOffset(-3531);
      accelgyroIC1.setYAccelOffset(-6565); 
      accelgyroIC1.setZAccelOffset(1717);
    
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 3");
 
  }
  else if (c == 4){
    digitalWrite(MPU6050_4,LOW);// set MPU6050 # 4 as the device being read
      delay(15);
  
      accelgyroIC1.setXAccelOffset(-1563);
      accelgyroIC1.setYAccelOffset(-257); 
      accelgyroIC1.setZAccelOffset(1602);
     
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 4");
  }
  else if (c == 5){
    digitalWrite(MPU6050_5,LOW);// set MPU6050 # 5 as the device being read
    delay(15);

    accelgyroIC1.setXAccelOffset(-1195);
    accelgyroIC1.setYAccelOffset(734); 
    accelgyroIC1.setZAccelOffset(1016);
   
    accelgyroIC1.getAcceleration(&ax,&ay,&az);
    Serial.println("Accelerometer 5");
  }
    else if (c == 6){
    digitalWrite(MPU6050_6,LOW);// set MPU6050 # 5 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-1662);
      accelgyroIC1.setYAccelOffset(-1299); 
      accelgyroIC1.setZAccelOffset(818);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 6");
  }
  else if (c == 7){
    digitalWrite(MPU6050_palm,LOW);// set MPU6050 # 5 as the device being read
     delay(15);

      accelgyroIC1.setXAccelOffset(-836);
      accelgyroIC1.setYAccelOffset(-2474); 
      accelgyroIC1.setZAccelOffset(490);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer Palm");
  }
  
 
 
  // THIS ADJUSTS RAW VALUES TO GIVE m/s^2// (we probably just want angles in final output)
  ac_x = (ax/16384.00)*9.81;
  ac_y = (ay/16384.00)*9.81;
  ac_z = (az/16384.00)*9.81;
  Serial.println(ac_x);
  Serial.println(ac_y);
  Serial.println(ac_z);
  delay(40); //40 microsecond delay to prevent simultaneous reading and writing on I2C bus
  }
 
}
 
