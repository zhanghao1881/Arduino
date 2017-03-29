#include"public.h"


void Init()
{
  /* 引脚模式设定,
     OUTPUT:输出,操作外部设备
     INPUT:输入,可通过传感器采集信息
  */
  //控制电机的相关引脚,全部为输出模式
  pinMode(LEFT_MOTOR_FRONT, OUTPUT);
  pinMode(LEFT_MOTOR_BACK, OUTPUT);
  pinMode(RIGHT_MOTOR_FRONT, OUTPUT);
  pinMode(RIGHT_MOTOR_BACK, OUTPUT);
  pinMode(MOTOR_EN, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  //黑线信息采集相关引脚，全部为输入模式
  pinMode(INFO_COLLECT_L2, INPUT);
  pinMode(INFO_COLLECT_L1, INPUT);
  pinMode(INFO_COLLECT_0, INPUT);
  pinMode(INFO_COLLECT_R1, INPUT);
  pinMode(INFO_COLLECT_R2, INPUT);

  //打开电机驱动使能端
  digitalWrite(MOTOR_EN, HIGH);

  Serial.begin(BUAD);
  //现场采集真实值
  Ave_Value();
}
