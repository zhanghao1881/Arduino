#include"public.h"

void setup() {
  // put your setup code here, to run once:
  Initialize();
}
 long Count_L = 0;
 long Count_R = 0;
 int n = 0;
 
void loop() {
  // put your main code here, to run repeatedly:
  Run();
  if(++n>100){
  testPoseInfo();
  n=0;}
}



