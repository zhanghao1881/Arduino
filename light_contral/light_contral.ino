//光敏电阻采集光照强度，强度规整为0到15，同时以led亮度表示 每隔0.5s检测一次光照
//显示数字需把LED_EN接上跳帽，led亮则去掉跳帽

//Number[16] 数组 储存数码管数字0到15
char Number[17] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
                   0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,0xBF
                  };

#define S1 10       //对应电路上S1 控制数码管的开关 HING开 LOW关
#define LED 9      //光敏电阻控制的LED
#define REST A2    //采集光照的引脚
int var = 0;
int n = 0;         //0对应数码管0 以此类推，数码管显示为16进制数
int LED_Var = 0;
void Show();       //显示数码管数字函数
void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 12; i++)  //初始化2到11号引脚 模式设置为输出模式
  {
    pinMode( i, OUTPUT);
  }
  pinMode(REST, INPUT);         //初始化A2  引脚，模式设置为输入
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  var=analogRead(REST);
  Serial.println(var);
  n = int(analogRead(REST) / 64) ;
  if(n>=16)n=16;
  Show();


}
//数码管显示函数实现
void Show()
{
  digitalWrite(S1, 1);
  for (int i = 2; i < 10; i++)
  {
    var = bitRead( Number[n] , i - 2 ) & 0x01;
    digitalWrite( i, var);
  }
  delay(500);
}
