#ifndef _SSD1306_Wire_H
#define _SSD1306_Wire_H

#include "Wire.h"
#include "Ccode.c"
#include "String.h"

#define CH_MAX 95

//屏幕y起始地址
#define BEGIN_ADRESS_Y 0xB2

//屏幕x起始地址，分高位XH和低位XL 
#define BEGIN_ADRESS_XL 0x00
#define BEGIN_ADRESS_XH 0x12

//字符高度
const unsigned char ch_high = 2;

//声明iic操作ssd1306类
class SSD1306_Wire
{
  public:

  void Initial();                                                         //初始化iic 和屏幕设置
  void WriteData(unsigned char dat);                                      //iic写数据
  void Show_Image(unsigned char *i);                                      //显示图片
  void WriteCommand(unsigned char ins);                                   //iic写命令 命令见手册
  void SetPos(unsigned char x, unsigned char y);                          //设置屏幕上显示位置，起始点屏幕左上角。
  void Fill_Screen();                                                     //填充屏幕
  void Show_Line(unsigned char x, unsigned char y);                       //显示线。测试
  void Clear_Screen();                                                    //清全屏
  void Show_Ch(unsigned char x, unsigned char y, char C);                 //显示字符
  void Show_String(unsigned char x, unsigned char y, String S);            //显示字符串
  private:
  bool Check_Range(unsigned char x, unsigned char y);                     //检测输入屏幕坐标是否超出显示。 
};

#endif
