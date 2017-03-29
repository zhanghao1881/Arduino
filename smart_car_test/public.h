#ifndef  PUBLIC_H_
#define  PUBLIC_H_

//电机控制引脚相关宏定义
#define LEFT_MOTOR_FRONT 2
#define LEFT_MOTOR_BACK 3
#define LEFT_PWM 9
#define RIGHT_MOTOR_FRONT 4
#define RIGHT_MOTOR_BACK 5
#define RIGHT_PWM 10
#define MOTOR_EN 6

/*寻黑线传感器相关引脚宏定义
   --------------------------------------------车头-------------------------------------
   INFO_COLLECT_L2---INFO_COLLECT_L1---INFO_COLLECT_0---INFO_COLLECT_R1---INFO_COLLECT_R2
*/
#define INFO_COLLECT_L2 A4
#define INFO_COLLECT_L1 A2
#define INFO_COLLECT_0 A3
#define INFO_COLLECT_R1 A1
#define INFO_COLLECT_R2 A0

#define BUAD 9600

//control.cpp
extern void Init();
//motor.cpp
extern void Motor(int pwm_l, int pwm_r);
//filter.cpp

#define BACKLINE_MIN 450
#define BACKLINE_MAX 550
#define BLANK_MIN 50
#define BLANK_MAX 120
#define THRESHOLD 50 //偏移阈值

extern float r_value;
extern float w_value;
extern void Test_print();
extern void Ave_Value();













#endif
