#include"public.h"



void Set_Pwm(int MotorA, int MotorB)
{
  //正反控制
  if (MotorA > 0)
  {
    digitalWrite(MA1, HIGH),      digitalWrite(MA2, LOW);
  }
  else
  {
    digitalWrite(MA1, LOW),      digitalWrite(MA2, HIGH);
  }
  if (MotorB < 0)
  {
    digitalWrite(MB1, HIGH),      digitalWrite(MB2, LOW);
  }
  else
  {
    digitalWrite(MB1, LOW),      digitalWrite(MB2, HIGH);
  }
  //速度控制
  analogWrite(PWMA, abs(MotorA));
  analogWrite(PWMB, abs(MotorB));
}
void Test_Motor(int Pwm)
{
  digitalWrite(MA1, HIGH),      digitalWrite(MA2, LOW);
  digitalWrite(MB1, LOW),      digitalWrite(MB2, HIGH);
  analogWrite(PWMA, abs(Pwm));
  analogWrite(PWMB, abs(Pwm));
}
