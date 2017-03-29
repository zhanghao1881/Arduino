#include "Segment.h"

_Segment::_Segment()
{
  
  }

void _Segment::begin()
{
  for (int i = 2; i < 12; i++)  //初始化2到11号引脚 模式设置为输出模式
  {
    pinMode( i, OUTPUT);
  }
}

void _Segment::showH(char n)
{
  for (int i = 2; i < 10; i++)
  {
    var = bitRead( Number_H[n] , i - 2 ) & 0x01;
    digitalWrite( i, var);
  }
}

void _Segment::showL(char n)
{
  for (int i = 2; i < 10; i++)
  {
    var = bitRead( Number_L[n] , i - 2 ) & 0x01;
    digitalWrite( i, var);
  }
}

 _Segment Segment = _Segment();
