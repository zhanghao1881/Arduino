#include"Ultrasonic.h"

_Ultrasonic::_Ultrasonic()
{
  
  }

void _Ultrasonic::begin()
{
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  digitalWrite(Trig,LOW);
  }

float _Ultrasonic::readDistant()
{
  // 产生一个10us的高脉冲去触发TrigPin 
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  // 检测脉冲宽度，并计算出距离并返回，距离单位厘米
  return pulseIn(Echo,HIGH)/58.00;
  }
float _Ultrasonic::readDistant( word UNIT)
{
  float distant = readDistant();
  switch(UNIT)
  {
    case M:   return distant/100.00;
              break;
    case CM:  return distant;
              break;
    case MM:  return distant*10;
              break;
    default:
              break;
    }
    return 0;
  }
_Ultrasonic Ultrasonic = _Ultrasonic();
