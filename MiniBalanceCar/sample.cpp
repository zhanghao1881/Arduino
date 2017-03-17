#include"public.h"
#define Get_Velocity_A 

/*卡尔曼滤波相关常数*/
#define K1  0.05                                          // 对加速度计取值的权重
#define Q_angle  0.001
#define Q_gyro  0.005
#define R_angle  0.5
#define C_0  1
#define dt  0.005

//x,y,z
u16 ax, ay, az;
u16 gx, gy, gz;

volatile long VCount_L = 0;
volatile long VCount_R = 0;

MPU6050 M6050; //instantiation MPU6050,
KalmanFilter KalFilter;


void Get_Info()
{
  M6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  KalFilter.Angletest(ax, ay, az, gx, gy, gz, dt, Q_angle, Q_gyro, R_angle, C_0, K1);
}
float Get_Angle()
{
  Get_Info();
  return KalFilter.angle6;
}

float Get_AngleV()
{
  return KalFilter.Gyro_y;
}

void Read_Encoder_L()
{
  if (digitalRead(ENCODER_L) == LOW) {     //如果是下降沿触发的中断
    if (digitalRead(DIRECTION_L) == LOW)      VCount_L--;  //根据另外一相电平判定方向
    else      VCount_L++;
  }
  else {     //如果是上升沿触发的中断
    if (digitalRead(DIRECTION_L) == LOW)      VCount_L++; //根据另外一相电平判定方向
    else     VCount_L--;
  }
}
void Read_Encoder_R() {
  if (digitalRead(ENCODER_R) == LOW) { //如果是下降沿触发的中断
    if (digitalRead(DIRECTION_R) == LOW)      VCount_R--;//根据另外一相电平判定方向
    else      VCount_R++;
  }
  else {   //如果是上升沿触发的中断
    if (digitalRead(DIRECTION_R) == LOW)      VCount_R++; //根据另外一相电平判定方向
    else     VCount_R--;
  }
}
int Get_Velocity_L()
{
  return VCount_L;
}
int Get_Velocity_R()
{
  return VCount_R;
}
void testPoseInfo()
{
  // read raw accel/gyro measurements from device
  M6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  KalFilter.Angletest(ax, ay, az, gx, gy, gz, dt, Q_angle, Q_gyro, R_angle, C_0, K1);          //通过卡尔曼滤波获取角度
  Serial.print(KalFilter.angle); Serial.print("\t");
  // display tab-separated accel/gyro x/y/z values
  /* Serial.print("a/g:\t");
    Serial.print(ax/131.00); Serial.print("\t");
    Serial.print(ay/131.00); Serial.print("\t");
    Serial.print(az/131.00); Serial.print("\t");
    Serial.print(gx/8192.00); Serial.print("\t");
    Serial.print(gy/8192.00); Serial.print("\t");
    Serial.println(gz/8192.00);
  */

}
