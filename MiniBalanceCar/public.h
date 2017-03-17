#ifndef  PUBLIC_H_
#define  PUBLIC_H_
#include<arduino.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <KalmanFilter.h>
#include<MPU6050.h>
/* IIC SDA A4 SCL A5 */
#include<Wire.h>

#define BAUD 38400
/*PID相关常数*/
//直立pid
#define BALANCE_KP 15
#define BALANCE_KD 1 /*（15）*/
//速度pid
#define  VELOCITY_KP  20
#define VELOCITY_KI  0.1

typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;

extern MPU6050 M6050;//instantiation MPU6050,
extern KalmanFilter KalFilter;//实例化一个卡尔曼滤波器对象，对象名称为 KalFilter

/*sample.cpp*/
/* MOTOR INFORMATION */
#define ENCODER_L 2
#define ENCODER_R 3
#define DIRECTION_L 4
#define DIRECTION_R 5

extern int Get_Velocity_L();
extern int Get_Velocity_R();

extern float Get_Angle();
extern float Get_AngleV();

extern void Read_Encoder_R();
extern void Read_Encoder_L();

extern void testPoseInfo();

/*control.cpp*/
extern void Initialize();
extern void Run();

/*motor.cpp*/
#define MA1 6
#define MA2 7
#define MB1 8
#define MB2 9
#define PWMA 10
#define PWMB 11
#define DIFFERENCE 2
#define CARMIDPOINT 0
extern void Set_Pwm(int motolA, int motolB);
extern void Test_Motor(int Pwm);
/*state.cpp*/
extern enum {ON, OFF, STAND,FORWARD,BACK,TRUN_L,TRUN_R} T_STATE;
extern enum {C_ON}C_STATE;
extern void Pick_Up();

extern void Put_Down();

extern void Stand_Up();

#endif
