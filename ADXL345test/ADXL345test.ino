#include <Wire.h>  //调用arduino自带的I2C库
#include <math.h>
#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37
//SCL-A5    SDA-A4

int ADXAddress = 0xA6>>1;  //转换为7位地址
int reading = 0;
int val = 0;
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
double Xg,Yg,Zg,Sg;

void setup()
{
  Serial.begin(9600);
  delay(100);
  Wire.begin();  //初始化I2C
  delay(100);
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_2D);
  Wire.write(8);
  Wire.endTransmission();
}

void loop()
{
  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_X0);
  Wire.write(Register_X1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2);
  if(Wire.available()<=2);
  {
    X0 = Wire.read();
    X_out = Wire.read();
    X_out = (X_out<<8) + X0;
   // X_out = X0+X1;
   // X_out = Wire.read()<<8 + X0;
  }

  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_Y0);
  Wire.write(Register_Y1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2);
  if(Wire.available()<=2);
  {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1<<8;
    Y_out = Y0+Y1;
  }

  Wire.beginTransmission(ADXAddress);
  Wire.write(Register_Z0);
  Wire.write(Register_Z1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress,2);
  if(Wire.available()<=2);
  {
    Z0 = Wire.read();
    Z1 = Wire.read();
    Z1 = Z1<<8;
    Z_out = Z0+Z1;
  }

  Xg = X_out/256.00;//把输出结果转换为重力加速度g,精确到小数点后2位。
  Yg = Y_out/256.00;
  Zg = Z_out/256.00;
  Sg = pow(Xg,2)+pow(Yg,2)+pow(Zg,2);
  Sg = sqrt(Sg);
  Serial.print("  Xg=");
  Serial.print(Xg);
  Serial.print("  Yg=");
  Serial.print(Yg);
  Serial.print("  Zg=");
  Serial.print(Zg);
  Serial.print("  Sg=");
  Serial.print(Sg);
  Serial.println();
  delay(500);  //延时0.3秒，刷新频率这里进行调整

}
