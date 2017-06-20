#include "protocol.h"

PROTOCOL test;
String data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = 0;i<20;i++)
{
  test.SendData(i+10,i);
  delay(100);
  }
  
}
