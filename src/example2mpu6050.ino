
#include <Wire.h>


const int primary_MPU_address=0x68;
const int secondary_MPU_address=0x69;

int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double tmp_double;
int AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;
double tmp_double1;

double angolo_x_z = 0;
double angolo_y_z = 0;
double angolo_x_y = 0;

double angolo_x_z1 = 0;
double angolo_y_z1 = 0;
double angolo_x_y1 = 0;

/*
MPU primary
vcc -> 5v
gnd -> GND
SDA -> 2
SCL -> 3
AD0 -> GND

MPU secondary
vcc -> 5v
gnd -> GND
SDA -> 2
SCL -> 3
AD0 -> 3.3v
*/

void setup(){

  Serial.begin(115200);
  Wire.begin(D2,D3);
  Wire.beginTransmission(primary_MPU_address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Wire.beginTransmission(secondary_MPU_address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}


void loop(){
  
  
  Wire.beginTransmission(primary_MPU_address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(primary_MPU_address,14,1);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Wire.beginTransmission(secondary_MPU_address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(secondary_MPU_address,14,1);  // request a total of 14 registers
  AcX1=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY1=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ1=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp1=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX1=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY1=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ1=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //conversione da complemento a 2 in numeri con segno
  if(AcX>32000){AcX=-65336+AcX;}
  if(AcY>32000){AcY=-65336+AcY;}
  if(AcZ>32000){AcZ=-65336+AcZ;}
  if(AcX1>32000){AcX1=-65336+AcX1;}
  if(AcY1>32000){AcY1=-65336+AcY1;}
  if(AcZ1>32000){AcZ1=-65336+AcZ1;}

  if(GyX>32000){GyX=-65336+GyX;}
  if(GyY>32000){GyY=-65336+GyY;}
  if(GyZ>32000){GyZ=-65336+GyZ;}
  if(GyX1>32000){GyX1=-65336+GyX1;}
  if(GyY1>32000){GyY1=-65336+GyY1;}
  if(GyZ1>32000){GyZ1=-65336+GyZ1;}

  //CALCOLI
  angolo_x_z = (atan2(AcX, AcZ))*90/1.6384;
  angolo_y_z = ((atan2(AcY, AcZ))*90/1.6384);
  angolo_x_y = (atan2(AcX, AcY))*90/1.6384;
  tmp_double= ((Tmp/340.00)+36.53)/10;

  angolo_x_z1 = (atan2(AcX1, AcZ1))*90/1.6384;
  angolo_y_z1 = ((atan2(AcY1, AcZ1))*90/1.6384);
  angolo_x_y1 = (atan2(AcX1, AcY1))*90/1.6384;
  tmp_double1= ((Tmp1/340.00)+36.53)/10;


    String printLine="";
    printLine = printLine + ","+AcX+","+AcY+","+AcZ;
    printLine = printLine + ","+tmp_double;
    printLine = printLine + ","+GyX+","+GyY+","+GyZ;
    printLine = printLine + ","+AcX1+","+AcY1+","+AcZ1;
    printLine = printLine + ","+tmp_double1;
    printLine = printLine + ","+GyX1+","+GyY1+","+GyZ1;
    Serial.println(printLine);
 
    String printLin="";
    printLin = printLin + ","+angolo_x_z+","+angolo_y_z+","+angolo_x_z1+","+angolo_y_z1;
    Serial.println(printLin);
 
}
