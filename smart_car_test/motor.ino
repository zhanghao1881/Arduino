#include"public.h"

void Motor(int pwm_l, int pwm_r)
{
  /*LEFT_MOTOR_FRONT--前进开关HIGH(开)/LOW(关)
     LEFT_MOTOR_BACK--后退开关HIGH(开)/LOW(关)
     所以前进状态为(LEFT_MOTOR_FRONT,HIGH)(LEFT_MOTOR_BACK,LOW)*/
  //左轮前进状态
  digitalWrite(LEFT_MOTOR_FRONT, HIGH);
  digitalWrite(LEFT_MOTOR_BACK, LOW);
  //右轮前进状态
  digitalWrite(RIGHT_MOTOR_FRONT, HIGH);
  digitalWrite(RIGHT_MOTOR_BACK, LOW);

  /*速度控制,pwm的控制范围为0-255,数字越大速度越快
     同时，也可以通过控制左右轮速度不同让小车转弯
     因此，小车直行需要控制左右电机速度相同，
     因为电机差异，pwm大小相同，也可能左右轮速度不同，小车直行参数需要大家自行调整
  */
  analogWrite(LEFT_PWM, pwm_l);
  analogWrite(RIGHT_PWM, pwm_r);
}
