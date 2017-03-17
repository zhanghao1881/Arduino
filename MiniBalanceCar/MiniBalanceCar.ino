#include"public.h"

void setup() {
  // put your setup code here, to run once:
  Initialize();
}
 long Count_L = 0;
 long Count_R = 0;
void loop() {
  // put your main code here, to run repeatedly:
 // Run();

 Test_Motor(100);
 // Serial.print("A:");
 Count_L=Get_Velocity_L()-Count_L;
  Count_R=Get_Velocity_R()-Count_R;
  Serial.print(Count_L);
  Serial.print("\t");
//  Serial.print("W:");
  Serial.println(Count_R);
  //Serial.println(Get_Velocity_R()-Get_Velocity_L());
  delay(40);
}



