int flag=0;
char test[10];
int i=0;
String s;
float n;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available())
{
  s= Serial.readString();
  n = s.toFloat();
  Serial.println(n);
  flag =1;
  }
  flag = 0;
}
