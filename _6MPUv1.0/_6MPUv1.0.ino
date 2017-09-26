//Example code for configuring 6 seperate MPU6050 accelerometers
/* Author(s): SRIRAM BOPPANA, Jason Ummel, Samuel Kuhns
*  Date: 02/19/2017
*  This code is based off the Jeff Rowberg I2Cdev.h and MPU6050.h library files
*  This code has not been tested and is only for reference
*
 */
 
 /*
  * Offsets must be set before each reading
  * Sensors are set to high and low via the AD0 pin because SCL and SDA are in series.
  * This code is best used to test the readings of all the sensors simultaneously
  */

 /*
  * Offsets for individual MIND MPU's are as follows

  * 

  * 
  * 
  * MPU 3
    Your offsets:  -3  -13 3814  0 -2  124

      accelgyroIC1.setXAccelOffset(-3);
      accelgyroIC1.setYAccelOffset(-13); 
      accelgyroIC1.setZAccelOffset(3814);
  * 
  * 
  * MPU 4
  * Your offsets:  -2  -25 3644  0 0 115

      accelgyroIC1.setXAccelOffset(-2);
      accelgyroIC1.setYAccelOffset(-25); 
      accelgyroIC1.setZAccelOffset(3644);

    MPU 5
    Your offsets:  -49 -94 3679  0 -1  126

      accelgyroIC1.setXAccelOffset(-49);
      accelgyroIC1.setYAccelOffset(-94); 
      accelgyroIC1.setZAccelOffset(3679);

    MPU 6
    Your offsets:  -72 0 3685  0 0 124

      accelgyroIC1.setXAccelOffset(-72);
      accelgyroIC1.setYAccelOffset(0); 
      accelgyroIC1.setZAccelOffset(3685);

    MPU 7
    Your offsets:  -38  -2  3684  0 0 123

      accelgyroIC1.setXAccelOffset(-38);
      accelgyroIC1.setYAccelOffset(-2); 
      accelgyroIC1.setZAccelOffset(3684);

    MPU 8
    Your offsets:  -72 -4  3684  0 0 125

      accelgyroIC1.setXAccelOffset(-72);
      accelgyroIC1.setYAccelOffset(-4); 
      accelgyroIC1.setZAccelOffset(3684);
    
  * 
  */
 
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"
//#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  //#include "Wire.h"
//#endif
#define OUTPUT_READABLE_ACCELGYRO
 
/*Declare digital pins to connect to AD0 pin on MPU6050*/
int MPU6050_8 = 8;  //digital pin 8
int MPU6050_3 = 3; //digital pin 2
int MPU6050_4 = 4; //digital pin 3
int MPU6050_5 = 5; //digital pin 4
int MPU6050_6 = 6; //digital pin 5
int MPU6050_7 = 7; //digital pin 6
 
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
 
  Serial.begin(19200);
 Serial.print("Initialize\n");
accelgyroIC1.initialize(); //default I2C address 0x68 when active LOW
accelgyroIC2.initialize(); // default I2C address 0x68 when inactive HIGH  



// Verify Connection
Serial.println("Testing device connections...");

 
  pinMode(MPU6050_8,OUTPUT);
 // pinMode(MPU6050_palm,OUTPUT);
  pinMode(MPU6050_3,OUTPUT);
  pinMode(MPU6050_4,OUTPUT);
  pinMode(MPU6050_5,OUTPUT);
  pinMode(MPU6050_6,OUTPUT);
  pinMode(MPU6050_7,OUTPUT);
  pinMode(A1,INPUT);
 
 
  delay(5);
 
}
 
void loop() {
  
//EMG Reading is completely optional and will be stored/implemented later. 
  emg = analogRead(A1);
  Serial.print("EMG Reading: ");
  Serial.println(emg);
  delay(5);

 /*
  * Offsets must be set before each reading
  * Sensors are set to high and low via the AD0 pin because SCL and SDA are in series.
  * This code is best used to test the readings of all the sensors simultaneously
  */
  
  for (int c = 1; c <= 6; c++){
    //Reset the address of all devices
    digitalWrite(MPU6050_8,HIGH);
    //digitalWrite(MPU6050_palm,HIGH);
    digitalWrite(MPU6050_3,HIGH);
    digitalWrite(MPU6050_4,HIGH);
    digitalWrite(MPU6050_5,HIGH);
    digitalWrite(MPU6050_6,HIGH);
    digitalWrite(MPU6050_7,HIGH);
  
    delay(15);
    if (c == 1){
      digitalWrite(MPU6050_8,LOW);// set MPU6050 # 1 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-72);
      accelgyroIC1.setYAccelOffset(-4); 
      accelgyroIC1.setZAccelOffset(3684);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer Central");
     
    }
    else if (c == 2){
      digitalWrite(MPU6050_3,LOW);// set MPU6050 # 2 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-3);
      accelgyroIC1.setYAccelOffset(-13); 
      accelgyroIC1.setZAccelOffset(3814);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 2");
    }
   else if (c == 3){
    digitalWrite(MPU6050_4,LOW);// set MPU6050 # 3 as the device being read
      delay(15);
      
      accelgyroIC1.setXAccelOffset(-2);
      accelgyroIC1.setYAccelOffset(-25); 
      accelgyroIC1.setZAccelOffset(3644);
    
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 3");
 
  }
  else if (c == 4){
    digitalWrite(MPU6050_5,LOW);// set MPU6050 # 4 as the device being read
      delay(15);
  
      accelgyroIC1.setXAccelOffset(-49);
      accelgyroIC1.setYAccelOffset(-94); 
      accelgyroIC1.setZAccelOffset(3679);
     
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 4");
  }
  else if (c == 5){
    digitalWrite(MPU6050_6,LOW);// set MPU6050 # 5 as the device being read
    delay(15);

      accelgyroIC1.setXAccelOffset(-72);
      accelgyroIC1.setYAccelOffset(0); 
      accelgyroIC1.setZAccelOffset(3685);
   
    accelgyroIC1.getAcceleration(&ax,&ay,&az);
    Serial.println("Accelerometer 5");
  }
    else if (c == 6){
    digitalWrite(MPU6050_7,LOW);// set MPU6050 # 5 as the device being read
      delay(15);


      accelgyroIC1.setXAccelOffset(-38);
      accelgyroIC1.setYAccelOffset(-2); 
      accelgyroIC1.setZAccelOffset(3684);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer 6");
  }
  /*else if (c == 7){
    digitalWrite(MPU6050_palm,LOW);// set MPU6050 # 5 as the device being read
     delay(15);

      accelgyroIC1.setXAccelOffset(-836);
      accelgyroIC1.setYAccelOffset(-2474); 
      accelgyroIC1.setZAccelOffset(490);
      
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      Serial.println("Accelerometer Palm");
  }*/
  
 
 
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
 
