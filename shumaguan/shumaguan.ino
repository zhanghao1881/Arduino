//Number[16] 数组 储存数码管数字0到15
char Number[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
                   0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
                  };
                  
#define S1 10       //对应电路上S1 控制数码管的开关 HING开 LOW关
#define S2 11      //对应电路上S2 控制数码管的开关 HING开 LOW关
#define K1 A0      //对应电路上K1 按键开关，按键数码管+1
#define K2 A1      //对应电路上K2 按键开关，按键数码管-1
bool var = 0;
int n = 0;         //0对应数码管0 以此类推，数码管显示为16进制数
void Show();       //显示数码管数字函数
void Show_Set();   //初始检测数码管函数

void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 12; i++)  //初始化2到11号引脚 模式设置为输出模式
  {
    pinMode( i, OUTPUT);
  }
  pinMode(K1, INPUT);         //初始化A0 A1 引脚，模式设置为输入
  pinMode(K2, INPUT);         // 用于检测按键K1 K2 
//  Show_Set();
  Serial.begin(9600);       //调试用。。此程序带Serial的可不理会
}

void loop() {
  // put your main code here, to run repeatedly:
  if (n >= 16 || n <= 0)n = 0;
  if (digitalRead(K1) == 0)         //检测按键是否按下
  {
    delay(100);                    //
    if (digitalRead(K1) == 0)     //再次检测按键是否按下
    {                             // 以上两步为按键消抖  
      n++;
      Serial.println("+1");
    }
  }
  if (digitalRead(K2) == 0)
  {
    delay(100);
    if (digitalRead(K2) == 0)
    {
      n--;
      Serial.println("-1");
    }
  }
  Show();

}
//数码管初始检测函数实现
void Show_Set()
{
  bool var = 0;
  for ( n = 0; n < 16 ; n++)
  {
    Show();
    delay(500);
    digitalWrite(S1, 0);
    digitalWrite(S2, 0);
  }
}
//数码管显示函数实现
void Show()
{
  digitalWrite(S1, 1);
  digitalWrite(S2, 1);
  for (int i = 2; i < 10; i++)
  {
    var = bitRead( Number[n] , i - 2 ) & 0x01;
    digitalWrite( i, var);
  }
  delay(20);
}
