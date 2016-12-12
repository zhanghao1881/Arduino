//串口通讯实验
//model a blink_led
void blink_led();
//model b follow_blink
void follow_blink();
//model c water_led
void water_led();
//model d binary_led
void binary_led();

char  n;
int s = 0;
int number = 0;


void setup() {
  // put your setup code here, to run once:
  //循环设置arduino引脚模式，OUTPUT输出，INPUT输入
  for (int i = 2; i < 10; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    n = int( Serial.read());
    if (n == 'a')s = 1;
    if (n == 'b')s = 2;
    if (n == 'c')s = 3;
    if (n == 'd')s = 4;
    Serial.println("hello word");
  }
  switch (s) {
    case 1: blink_led();
    case 2: follow_blink();
    case 3: water_led();
    case 4: binary_led();
      // default: Serial.println("error");
  }
}
void blink_led()
{
  int i;
  //循环点亮led
  for ( i = 2; i < 10; i++)
  {
    digitalWrite(i, LOW);      //将i引脚置于（LOW）低电平
  }
  //亮灯时间 1000ms=1s
  delay(1000);
  //循环熄灭led
  for ( i = 2; i < 10; i++)
  {
    digitalWrite(i, HIGH);     //将i引脚置于（HIGH）高电平
  }
  //熄灭时间
  delay(1000);
}

void follow_blink()
{
  int i;
  //循环
  for ( i = 2; i < 10; i++)
  {
    digitalWrite(i, LOW);      //将i引脚置于（LOW）低电平
    //亮灯时间 1000ms=1s
    delay(1000);
    digitalWrite(i, HIGH);     //将i引脚置于（HIGH）高电平
    //熄灭时间
    delay(1000);
  }

}

void water_led()
{
  int i;
  //循环

  for ( i = 2; i < 10; i++)
  {
    digitalWrite(i, LOW);
    delay(100);
  }
  for (int i = 2; i < 10; i++)
  {
    digitalWrite(i, HIGH);
    delay(100);
  }
}

void binary_led()
{
  int i;
  bool n;
  //循环
  for (i = 2; i < 10; i++)
  {
    n = ~bitRead(number, i - 2) & 0x01;
    digitalWrite(i, n);
  }
  delay(100);
  number++;

}
