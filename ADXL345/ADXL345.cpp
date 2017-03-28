#include "ADXL345.h"

ADXL345Class::ADXL345Class()
{
  
  }

void ADXL345Class::begin()
{
  Wire.begin();
  Wire.beginTransmission(ADXLAddress);
  Wire.write(Register_2D);
  Wire.write(8);
  Wire.endTransmission();
  }

float ADXL345Class::readAcceleration(const int _direction)
{
  int data;
  int out=0;
  Wire.beginTransmission(ADXLAddress);
  Wire.write(_direction);
  Wire.write(_direction+1);
  Wire.endTransmission();
  Wire.requestFrom(ADXLAddress,2);
  if(Wire.available()<=2)
  {
    data=Wire.read();
    out=Wire.read();
    out=(out<<8)+data;
    }
    return out/256.00;
  }
  
// Preinstantiate Objects //////////////////////////////////////////////////////

ADXL345Class ADXL345 = ADXL345Class();
