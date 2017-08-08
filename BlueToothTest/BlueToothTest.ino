#include <BMI160.h>
#include <CurieIMU.h>

#include <BLEAttributeWithValue.h>
#include <BLECentral.h>
#include <BLECharacteristic.h>
#include <BLECommon.h>
#include <BLEDescriptor.h>
#include <BLEDevice.h>
#include <BLEPeripheral.h>
#include <BLEService.h>
#include <BLETypedCharacteristic.h>
#include <BLETypedCharacteristics.h>
#include <CurieBLE.h>
#include <math.h>
#include <Wire.h>
#include <MPU6050.h>

/****************************/

BLEPeripheral blePeripheral;
BLEService acclService("19B10010-E8F2-537E-4F6C-D104768A1214");

BLECharCharacteristic acclCharacteristic("19B10010-E8F2-537E-4F6C-D104768A1214", BLEWrite);
int16_t ax,ay,az;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 blePeripheral.setLocalName("acclValues");
 blePeripheral.setAdvertisedServiceUuid(acclService.uuid()); 
// blePeripheral.addAttribute(acclService);
// blePeripheral.addAttribute(acclCharacteristic);

 acclCharacteristic.setValue(0);

 blePeripheral.begin();

 Serial.println("Bluetooth device active, waiting for connections...");

}

void loop() {
  blePeripheral.poll();

   
  // put your main code here, to run repeatedly:

}
