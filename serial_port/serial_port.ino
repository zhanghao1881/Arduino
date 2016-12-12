//串口通讯实验

char  n;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    n = Serial.read();
    if (n == 'a')
    Serial.println("hello word");
  }


}
