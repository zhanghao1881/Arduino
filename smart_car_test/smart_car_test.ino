#include"public.h"



float Collect_Info()
{
  
  }
void setup() {
  // put your setup code here, to run once:
  Init();
}

void loop() {
  // put your main code here, to run repeatedly:
 Test_print();
 Serial.println(analogRead(INFO_COLLECT_0));

}
