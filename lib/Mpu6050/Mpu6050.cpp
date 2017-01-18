#include "Arduino.h"
#include "Mpu6050.h"
#include "Wire.h"

Mpu6050::Mpu6050(int sda, int scl, int address){
  Wire.begin(sda, scl);
  Wire.beginTransmission(address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  _AcX=0;
  _AcY=0;
  _AcZ=0;
}
int Mpu6050::readAcX()
{


}
