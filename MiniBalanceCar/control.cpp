#include"public.h"

float Balance_Kp = BALANCE_KP;
float Balance_Kd = BALANCE_KD;
float Velocity_Kp = VELOCITY_KP;
float Velocity_Ki = VELOCITY_KI;

int MotorA;
int MotorB;

int Velocity_Count = 0;

void Initialize()
{
  pinMode(MA1, OUTPUT);          //TB6612控制引脚，控制电机1的方向，01为正转，10为反转
  pinMode(MA2, OUTPUT);          //TB6612控制引脚，
  pinMode(MB1, OUTPUT);          //TB6612控制引脚，控制电机2的方向，01为正转，10为反转
  pinMode(MB2, OUTPUT);          //TB6612控制引脚，
  pinMode(PWMA, OUTPUT);         //TB6612控制引脚，电机PWM
  pinMode(PWMB, OUTPUT);         //TB6612控制引脚，电机PWM
  digitalWrite(MA1, 0);          //TB6612控制引脚拉低
  digitalWrite(MA2, 0);          //TB6612控制引脚拉低
  digitalWrite(MB1, 0);          //TB6612控制引脚拉低
  digitalWrite(MB2, 0);          //TB6612控制引脚拉低
  analogWrite(PWMA, 0);          //TB6612控制引脚拉低
  analogWrite(PWMB, 0);          //TB6612控制引脚拉低
  pinMode(ENCODER_L, INPUT_PULLUP);     //编码器中断触发引脚
  pinMode(ENCODER_R, INPUT_PULLUP);     //编码器中断触发引脚
  pinMode(DIRECTION_L, INPUT);   //编码器引脚
  pinMode(DIRECTION_R, INPUT);   //编码器引脚

  //IIC初始化
  Wire.begin();

  //串口通讯初始化
  Serial.begin(BAUD);

  // initialize device MPU6050
  Serial.println("Initializing I2C devices...");
  M6050.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(M6050.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  //开启外部中断 编码器接口
  attachInterrupt(digitalPinToInterrupt(ENCODER_L), Read_Encoder_L, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R), Read_Encoder_R, CHANGE);

  //计数
  Velocity_Count = 0;

}
void Telecontrol()
{
  switch (T_STATE)
  {
    case ON: break;
    case OFF: break;
    case STAND: break;
    case FORWARD: break;
    case BACK: break;
    case TRUN_L: break;
    case TRUN_R: break;
    default: break;
  }
}

int Balance_Pwm(float Angle, float Gyro)
{
  float Bias;
  int balance;
  Bias = Angle - 2;   //===求出平衡的角度中值 和机械相关
  balance = Balance_Kp * Bias + Gyro * Balance_Kd; //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数
  return balance;
}
int velocity_Pwm(int encoder_left, int encoder_right)
{
  static float Velocity, Encoder_Least, Encoder, Movement;
  static float Encoder_Integral, Target_Velocity;
  if (Encoder_Integral > 300)   Encoder_Integral -= 200;
  if (Encoder_Integral < -300)  Encoder_Integral += 200;
  //=============速度PI控制器=======================//
  Encoder_Least = (encoder_left + encoder_right) - 0;               //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）
  Encoder *= 0.7;                                                   //===一阶低通滤波器
  Encoder += Encoder_Least * 0.3;                                   //===一阶低通滤波器
  Encoder_Integral += Encoder;                                      //===积分出位移 积分时间：40ms
  Encoder_Integral = Encoder_Integral - Movement;                   //===接收遥控器数据，控制前进后退
  if (Encoder_Integral > 21000)    Encoder_Integral = 21000;        //===积分限幅
  if (Encoder_Integral < -21000) Encoder_Integral = -21000;         //===积分限幅
  Velocity = Encoder * Velocity_Kp + Encoder_Integral * Velocity_Ki;                  //===速度控制
  if (Get_Angle() < 5)    Encoder_Integral = 0; //小车停止的时候积分清零
  return Velocity;
}
void Limit_Pwm(void)
{
  int Amplitude = 250;  //===PWM满幅是255 限制在250
  //遥控标志Flag_Qian ，Flag_Hou
  //  if (Flag_Qian == 1)  Motor2 -= DIFFERENCE; //DIFFERENCE是一个衡量平衡小车电机和机械安装差异的一个变量。直接作用于输出，让小车具有更好的一致性。
  //  if (Flag_Hou == 1)   Motor2 -= DIFFERENCE - 2;
  if (MotorA < -Amplitude) MotorA = -Amplitude;
  if (MotorA > Amplitude)  MotorA = Amplitude;
  if (MotorB < -Amplitude) MotorB = -Amplitude;
  if (MotorB > Amplitude)  MotorB = Amplitude;
}

void Run()
{
  if (++Velocity_Count >= 8)
  {
    MotorA = Balance_Pwm(Get_Angle(), Get_AngleV())+velocity_Pwm(Get_Velocity_L(),Get_Velocity_R());
    MotorB = Balance_Pwm(Get_Angle(), Get_AngleV())+velocity_Pwm(Get_Velocity_L(),Get_Velocity_R());
  }
  MotorA = Balance_Pwm(Get_Angle(), Get_AngleV());
  MotorB = Balance_Pwm(Get_Angle(), Get_AngleV());
  Limit_Pwm();
  Set_Pwm(MotorA, MotorB);
}
