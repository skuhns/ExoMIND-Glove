//Example code for configuring 6 seperate MPU6050 accelerometers
/* Author(s): SRIRAM BOPPANA,  Jason Ummel, Samuel Kuhns
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
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
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
float ac1_x, ac1_y, ac1_z, ac2_x, ac2_y, ac2_z, ac3_x, ac3_y, ac3_z, ac4_x, ac4_y, ac4_z, ac5_x, ac5_y, ac5_z, acc_x, acc_y, acc_z, acp_x, acp_y, acp_z;
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
  while(!Serial){}
 
accelgyroIC1.initialize(); //default I2C address 0x68 when active LOW
accelgyroIC2.initialize(); // default I2C address 0x68 when inactive HIGH  

// Verify Connection
//Serial.println("Testing device connections...");
 
 
  pinMode(MPU6050_central,OUTPUT);
  pinMode(MPU6050_palm,OUTPUT);
  pinMode(MPU6050_2,OUTPUT);
  pinMode(MPU6050_3,OUTPUT);
  pinMode(MPU6050_4,OUTPUT);
  pinMode(MPU6050_5,OUTPUT);
  pinMode(MPU6050_6,OUTPUT);
  pinMode(A1,INPUT);
  Serial.println("Welcome, get ready to begin");
  delay(3500);
  delay(5);
}

 
void loop() {
  //Settling sensors to help ensure accuracy of data
  Serial.println("\nWaiting for sensors to settle");
  for(int i = 0; i < 10; i++) {
    getNumbers();
  }
  Serial.println("Done!");
  delay(1000);
        Serial.println("Hold forearm straight out...");

  while(state == 0) {
    //Sensing for the z axis forearm accelerometer to be still and level 
    //THESE NUMBER RANGES ARE GENEROUS FOR TESTING
    getNumbers();
    if(acc_x >= -2.0 && acc_x <= 2.0 && acc_y >= -2.0 && acc_y <= 2.0 && acc_z > 7.0 && acc_z < 11.5) {
        delay(1000);
        state = 1;
    }
  }
  Serial.println("Forearm straight out detected! Continue...");

  Serial.println("Begin opening hand as far as possible and hold until prompted...");
  float x1_ave,y1_ave,z1_ave,x2_ave,y2_ave,z2_ave,x3_ave,y3_ave,z3_ave,x4_ave,y4_ave,z4_ave,x5_ave,y5_ave,z5_ave,xc_ave,yc_ave,zc_ave,xp_ave,yp_ave,zp_ave;
  delay(7000);
  //This averages the final position of the hand after 7 seconds of straining to open
  for(int j = 0; j < 10; j++) {
      getNumbers();
      x1_ave += ac1_x;
      y1_ave += ac1_y;
      z1_ave += ac1_z;

      x2_ave += ac2_x;
      y2_ave += ac2_y;
      z2_ave += ac2_z;

      x3_ave += ac3_x;
      y3_ave += ac3_y;
      z3_ave += ac3_z;

      x4_ave += ac4_x;
      y4_ave += ac4_y;
      z4_ave += ac4_z;

      x5_ave += ac5_x;
      y5_ave += ac5_y;
      z5_ave += ac5_z;

      xc_ave += acc_x;
      yc_ave += acc_y;
      zc_ave += acc_z;

      xp_ave += acp_x;
      yp_ave += acp_y;
      zp_ave += acp_z;
  }
  
  x1_ave = x1_ave/10;
  y1_ave = y1_ave/10;
  z1_ave = z1_ave/10;

  x2_ave = x2_ave/10;
  y2_ave = y2_ave/10;
  z2_ave = z2_ave/10;

  x3_ave = x3_ave/10;
  y3_ave = y3_ave/10;
  z3_ave = z3_ave/10;

  x4_ave = x4_ave/10;
  y4_ave = y4_ave/10;
  z4_ave = z4_ave/10;

  x5_ave = x5_ave/10;
  y5_ave = y5_ave/10;
  z5_ave = z5_ave/10;

  xc_ave = xc_ave/10;
  yc_ave = yc_ave/10;
  zc_ave = zc_ave/10;

  xp_ave = xp_ave/10;
  yp_ave = yp_ave/10;
  zp_ave = zp_ave/10;
  
  Serial.println("Done finding values, you may relex hand");
  delay(1000);
  //Code below can be uncommented for extra information on each use.
/*
  Serial.println("Thumb:");
  Serial.println("Average x value");
  Serial.println(x1_ave);
  Serial.println("Average y value");
  Serial.println(y1_ave);  
  Serial.println("Average z value");
  Serial.println(z1_ave);

  Serial.println("Index Finger:");
  Serial.println("Average x value");
  Serial.println(x2_ave);
  Serial.println("Average y value");
  Serial.println(y2_ave);  
  Serial.println("Average z value");
  Serial.println(z2_ave);

  Serial.println("Middle Finger:");
  Serial.println("Average x value");
  Serial.println(x3_ave);
  Serial.println("Average y value");
  Serial.println(y3_ave);  
  Serial.println("Average z value");
  Serial.println(z3_ave);

  Serial.println("Ring Finger:");
  Serial.println("Average x value");
  Serial.println(x4_ave);
  Serial.println("Average y value");
  Serial.println(y4_ave);  
  Serial.println("Average z value");
  Serial.println(z4_ave);

  Serial.println("Small Finger:");
  Serial.println("Average x value");
  Serial.println(x5_ave);
  Serial.println("Average y value");
  Serial.println(y5_ave);  
  Serial.println("Average z value");
  Serial.println(z5_ave);


  Serial.println("Wrist:");
  Serial.println("Average x value");
  Serial.println(xp_ave);
  Serial.println("Average y value");
  Serial.println(yp_ave);  
  Serial.println("Average z value");
  Serial.println(zp_ave);  

  

  Serial.println("Forearm:");
  Serial.println(zc_ave);*/
  z1_ave = ((z1_ave)/9.81) * 100;
  z2_ave = ((z2_ave)/9.81) * 100;
  z3_ave = ((z3_ave)/9.81) * 100;
  z4_ave = ((z4_ave)/9.81) * 100;
  z5_ave = ((z5_ave)/9.81) * 100;

  Serial.println("Percent Range of Motion per Finger starting with thumb");
    
    Serial.println("Thumb ");
  Serial.println((z1_ave));
  
    Serial.println("Index %");
  Serial.println((z2_ave));
  
    Serial.println("Middle %");
  Serial.println((z3_ave));
  
    Serial.println("Ring %");
  Serial.println((z4_ave));
  
    Serial.println("Small %");
  Serial.println((z5_ave));


  Serial.println("If average z value is less than ~9.8 full motion is assumed for all fingers excluding thumb");
  Serial.println("Z value for thumb should be ~ 0 and x (or y can't recall) should be approximately 9.81");

  //WAIT TO RESTART SKETCH

  //This block works to restart sketch but doesn't reset variables.
  /*
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available()){
    //Serial.println(F("Send any character to restart detection.\n"));
    delay(9500);
  }               
  while (Serial.available() && Serial.read()); // empty buffer again
*/
  
}


void getNumbers() {
  emg = analogRead(A1);
  /*Serial.println("EMG Reading: ");
  Serial.println(emg);*/
  //Serial.println("Entering getNumbers()");
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
      //Serial.println("Accelerometer Central");
     
    }
    else if (c == 2){
      digitalWrite(MPU6050_2,LOW);// set MPU6050 # 2 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-1388);
      accelgyroIC1.setYAccelOffset(-1390); 
      accelgyroIC1.setZAccelOffset(1613);

      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 2");
    }
   else if (c == 3){
    digitalWrite(MPU6050_3,LOW);// set MPU6050 # 3 as the device being read
      delay(15);
      
      accelgyroIC1.setXAccelOffset(-3531);
      accelgyroIC1.setYAccelOffset(-6565); 
      accelgyroIC1.setZAccelOffset(1717);
    
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 3");
 
  }
  else if (c == 4){
    digitalWrite(MPU6050_4,LOW);// set MPU6050 # 4 as the device being read
      delay(15);
  
      accelgyroIC1.setXAccelOffset(-1563);
      accelgyroIC1.setYAccelOffset(-257); 
      accelgyroIC1.setZAccelOffset(1602);
     
      accelgyroIC1.getAcceleration(&ax,&ay,&az);
      //Serial.println("Accelerometer 4");
  }
  else if (c == 5){
    digitalWrite(MPU6050_5,LOW);// set MPU6050 # 5 as the device being read
    delay(15);

    accelgyroIC1.setXAccelOffset(-1195);
    accelgyroIC1.setYAccelOffset(734); 
    accelgyroIC1.setZAccelOffset(1016);
   
    accelgyroIC1.getAcceleration(&ax,&ay,&az);
    //Serial.println("Accelerometer 5");
  }
    else if (c == 6){
    digitalWrite(MPU6050_6,LOW);// set MPU6050 # 5 as the device being read
      delay(15);

      accelgyroIC1.setXAccelOffset(-1662);
      accelgyroIC1.setYAccelOffset(-1299); 
      accelgyroIC1.setZAccelOffset(818);
      
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
      ac2_x = (ax/16384.00)*9.81;
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
  
  delay(40); //40 microsecond delay to prevent simultaneous reading and writing on I2C bus
  }
  //Serial.println("Exiting getNumbers()");
}


 
 

 
  


