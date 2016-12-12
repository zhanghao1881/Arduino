//点亮led
//arduino使用引脚 D2-D9 控制led，3V3供电，GND
// 3V3 接VCC  GND 接GND
//LED_EN 跳帽短接
//D2-D9接 A-G DP
void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<10;i++)
  pinMode(i,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    for(int i=2;i<10;i++)
    digitalWrite(i,LOW);

}
