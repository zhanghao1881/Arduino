#pragma once
#include "Wire.h" 
//SCL-A5 SDA-A4

#include<math.h>

/* Register address*/
#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define ADXLAddress 0x53 //0xA6>>1 转化为7位地址

#define X 0x32
#define Y 0x34
#define Z 0x36

 class ADXL345Class
{
  public:
        ADXL345Class();
        void begin();
        float readAcceleration(const int _direction);
        float readAngle(const int _direction,const int _direction);//yu x zhou de angle
  };
  
extern ADXL345Class ADXL345;
