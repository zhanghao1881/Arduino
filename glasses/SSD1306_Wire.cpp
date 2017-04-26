#include"SSD1306_Wire.h"

//写命令
void SSD1306_Wire::WriteCommand(unsigned char ins)
{
  Wire.beginTransmission(0x78>>1);//屏幕iic地址
  Wire.write(0x00);
  Wire.write(ins);
  Wire.endTransmission();
}

//写数据
void SSD1306_Wire::WriteData(unsigned char dat)
{
  Wire.beginTransmission(0x78>>1);
  Wire.write(0x40);
  Wire.write(dat);
  Wire.endTransmission();
}

//设置开始位置
void SSD1306_Wire::SetPos(unsigned char x, unsigned char y )
{
  unsigned char x_l,x_h;
  if(Check_Range(x,y))
  {
    x_l = (x&0x0f)|BEGIN_ADRESS_XL;
    x_h = ((x&0xf0)>>4)+BEGIN_ADRESS_XH;
  }
  //y坐标，页地址 从上到下2-7页，每页有64行 每次都写入一行数据（从上到下8位）共阴——列行式——逆向输出
 WriteCommand(BEGIN_ADRESS_Y + y);   //0xb2
  WriteCommand(x_h);//|0x12
  WriteCommand(x_l);//|0x00
}

//清屏
void SSD1306_Wire::Clear_Screen()
{
     unsigned char x,y;

     WriteCommand(BEGIN_ADRESS_XL);    /*set lower column address*/       
     WriteCommand(BEGIN_ADRESS_XH);    /*set higher column address*/
     WriteCommand(BEGIN_ADRESS_Y);    /*set page address*/
     for(y=0;y<8;y++)
        {
           WriteCommand(BEGIN_ADRESS_Y + y);    /*set page address*/
           WriteCommand(BEGIN_ADRESS_XL);    /*set lower column address*/       
           WriteCommand(BEGIN_ADRESS_XH);    /*set higher column address*/
           for(x=0;x<64;x++)
             {
              WriteData(0x00);
              WriteData(0x00);
             }
       }
}

//填充
void SSD1306_Wire::Fill_Screen()
{
     unsigned char x,y;

     WriteCommand(BEGIN_ADRESS_XL);    /*set lower column address*/       
     WriteCommand(BEGIN_ADRESS_XH);    /*set higher column address*/
     WriteCommand(BEGIN_ADRESS_Y);    /*set page address*/
     for(y=2;y<8;y++)
        {
           WriteCommand(BEGIN_ADRESS_Y + y);    /*set page address*/
           WriteCommand(BEGIN_ADRESS_XL);    /*set lower column address*/       
           WriteCommand(BEGIN_ADRESS_XH);    /*set higher column address*/
           for(x=0;x<64;x++)
             {
              WriteData(0xff);
              
             }
       }
}

//显示线
void SSD1306_Wire::Show_Line(unsigned char x, unsigned char y)
{
  SetPos(x,y);
  WriteData(0xff);
}

//范围检查
bool SSD1306_Wire::Check_Range(unsigned char x, unsigned char y)
{
  if(x >= 64 || y >= 6)return false;
  else return true;
  }
  
//显示高16宽8的指定字符
void SSD1306_Wire::Show_Ch(unsigned char x, unsigned char y, char C)
{
  unsigned char num;
  unsigned int ch_wide;
  unsigned char row,col;
  unsigned int address = 0;
  unsigned char temp;
  for(num = 0;num < CH_MAX ;num++)
  {
    if(C == font[num].index)
    {
      address = 16 * font[num].address;
      Serial.println("ok");
      break;
      }
     else
     {
      Serial.println("error");
     }
    }
  if(font[num].flag)
  {
   ch_wide = 16; 
   Serial.println('T');
  }
  else 
  {
   ch_wide = 8; 
   Serial.println('F');
  }
  for(row = 0; row < ch_high; row++)
  {
    SetPos(x,y + row);
    for(col = 0;col < ch_wide; col++)
    {
      Serial.print(col);
      temp = pgm_read_byte(&ch[address]);//从flashrom中读取数据。
      WriteData(temp);
      address++;
    }
  }
  /*
//第一页
    SetPos(x,y);
    for(i = 0; i<CH_WIDE8;i++)
    {
      WriteData(CH168[adder]);
      adder++;
      }
//第二页
    SetPos(x,y+1);
    for(i = 0; i<CH_WIDE8;i++)
    {
      WriteData(CH168[adder]);
      adder++;
      } 
 */ 
  }
  
void SSD1306_Wire::Show_String(unsigned char x, unsigned char y, char *S)
{
  int number;
  for(number = 0;number < strlen(S);number++)
  {
    Show_Ch(x,y,S[number]);
    x+=8;
    }
}
//初始化
void SSD1306_Wire::Initial()
{
  Wire.begin();
  WriteCommand(0xAE);//display off
  WriteCommand(0x00);//set lower column address
  WriteCommand(0x10);//set higher column address
  
  WriteCommand(0x40);//set display start line
  
  WriteCommand(0xB0);//set page address
  
  WriteCommand(0x81);//对比度设置
  WriteCommand(0xCF);//0~255（对比度值……效果不是特别明显）
  
  WriteCommand(0xA1);//set segment remap
  
  WriteCommand(0xA6);//normal / reverse
  
  WriteCommand(0xA8);//multiplex ratio
  WriteCommand(0x3F);//duty = 1/64
  
  WriteCommand(0xC8);//Com scan direction
  
  WriteCommand(0xD3);//set display offset
  WriteCommand(0x00);
  
  WriteCommand(0xD5);//set osc division
  WriteCommand(0x80);
  
  WriteCommand(0xD9);//set pre-charge period
  WriteCommand(0xF1);
  
  WriteCommand(0xDA);//set COM pins
  WriteCommand(0x12);
  
  WriteCommand(0xDB);//set vcomh
  WriteCommand(0x40);
  
  WriteCommand(0x8D);//set charge pump enable
  WriteCommand(0x14);
  
  WriteCommand(0xAF);//display ON
}

