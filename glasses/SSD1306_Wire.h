#ifndef _SSD1306_Wire_H
#define _SSD1306_Wire_H

#include "Wire.h"
#include "Ccode.c"
#include "String.h"

#define CH_MAX 95

#define BEGIN_ADRESS_Y 0xB2 
#define BEGIN_ADRESS_XL 0x00
#define BEGIN_ADRESS_XH 0x12

const unsigned char ch_high = 2;
class SSD1306_Wire
{
  public:

  void Initial();
  void WriteCommand(unsigned char ins);
  void WriteData(unsigned char dat);
  void SetPos(unsigned char x, unsigned char y);
  void Fill_Screen();
  void Show_Line(unsigned char x, unsigned char y);
  void Clear_Screen();
  void Show_Ch(unsigned char x, unsigned char y, char C);
  void Show_String(unsigned char x, unsigned char y, char *S);
  private:
  bool Check_Range(unsigned char x, unsigned char y);   
};

#endif
