#ifndef MPU6050_H
#define MPU6050_H

#include "Arduino.h"


class Mpu6050{
  public:
    Mpu6050( int sda, int scl, int address);
    int readAcX();
    int readAcY();
    int readAcZ();
    int readTemp();
    int readGyX();
    int readGyY();
    int readGyZ();

  private:
    int _pinSda;
    int _pinScl;
    int _AcX;
    int _AcY;
    int _AcZ;
    int _temp;
    int _GyX;
    int _GyY;
    int _GyZ;

};
#endif
