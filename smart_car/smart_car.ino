
//电机控制引脚相关宏定义
#define LEFT_MOTOR_FRONT 2
#define LEFT_MOTOR_BACK 3
#define LEFT_PWM 9
#define RIGHT_MOTOR_FRONT 4
#define RIGHT_MOTOR_BACK 5
#define RIGHT_PWM 10
#define MOTOR_EN 6

/*寻黑线传感器相关引脚宏定义
 * --------------------------------------------车头-------------------------------------
 * INFO_COLLECT_L2---INFO_COLLECT_L1---INFO_COLLECT_0---INFO_COLLECT_R1---INFO_COLLECT_R2
*/
#define INFO_COLLECT_L2 7
#define INFO_COLLECT_L1 8
#define INFO_COLLECT_0 9
#define INFO_COLLECT_R1 11
#define INFO_COLLECT_R2 12

//常量定义
#define normal_velocity_left 100
#define normal_velocity_right 100
#define turn_velocity_left_30 180
#define turn_velocity_left_60 230
#define turn_velocity_right_30 180
#define turn_velocity_right_60 230

//小车状态
enum{S_FRONT,S_RIGHT_30,S_RIGHT_60,S_LEFT_30,S_LEFT_60}STATA;

void Init()
{
  /* 引脚模式设定,
   * OUTPUT:输出,操作外部设备
   * INPUT:输入,可通过传感器采集信息
   */
  //控制电机的相关引脚,全部为输出模式
  pinMode(LEFT_MOTOR_FRONT,OUTPUT);
  pinMode(LEFT_MOTOR_BACK,OUTPUT);
  pinMode(RIGHT_MOTOR_FRONT,OUTPUT);
  pinMode(RIGHT_MOTOR_BACK,OUTPUT);
  pinMode(MOTOR_EN,OUTPUT);
  pinMode(LEFT_PWM,OUTPUT);
  pinMode(RIGHT_PWM,OUTPUT);
  
  //黑线信息采集相关引脚，全部为输入模式
  pinMode(INFO_COLLECT_L2,INPUT);
  pinMode(INFO_COLLECT_L1,INPUT);
  pinMode(INFO_COLLECT_0,INPUT);
  pinMode(INFO_COLLECT_R1,INPUT);
  pinMode(INFO_COLLECT_R2,INPUT);
   
  //打开电机驱动使能端
  digitalWrite(MOTOR_EN,HIGH);
  }
void Motor(int pwm_l,int pwm_r)
{
  /*LEFT_MOTOR_FRONT--前进开关HIGH(开)/LOW(关)
   * LEFT_MOTOR_BACK--后退开关HIGH(开)/LOW(关)
   * 所以前进状态为(LEFT_MOTOR_FRONT,HIGH)(LEFT_MOTOR_BACK,LOW)*/
  //左轮前进状态
  digitalWrite(LEFT_MOTOR_FRONT,HIGH);
  digitalWrite(LEFT_MOTOR_BACK,LOW);
  //右轮前进状态
  digitalWrite(RIGHT_MOTOR_FRONT,HIGH);
  digitalWrite(RIGHT_MOTOR_BACK,LOW);
  
  /*速度控制,pwm的控制范围为0-255,数字越大速度越快
   * 同时，也可以通过控制左右轮速度不同让小车转弯
   * 因此，小车直行需要控制左右电机速度相同，
   * 因为电机差异，pwm大小相同，也可能左右轮速度不同，小车直行参数需要大家自行调整
   */
  analogWrite(LEFT_PWM,pwm_l);
  analogWrite(RIGHT_PWM,pwm_r);
  }
void Control(byte STATA)
{
  switch (STATA)
  {
    case S_FRONT:
    {
      Motor(normal_velocity_left,normal_velocity_right);
      break;
      }
    case S_RIGHT_30:
    {
      Motor(turn_velocity_left_30,normal_velocity_right);
      break;
      }
    case S_RIGHT_60:
    {
      Motor(turn_velocity_left_60,normal_velocity_right);
      break;
      }
    case S_LEFT_30:
    {
      Motor(normal_velocity_left,turn_velocity_right_30);
      break;
      }
    case S_LEFT_60:
    {
      Motor(normal_velocity_left,turn_velocity_right_60);
      break;
      }
    default:break;
    }
  }

//黑线信息采集
void Collect_Info()
{
  if(digitalRead(INFO_COLLECT_L2))
  {
    STATA=S_LEFT_60;
    }
  if(digitalRead(INFO_COLLECT_L1))
  {
    STATA=S_LEFT_30;
    }
  if(digitalRead(INFO_COLLECT_0))
  {
    STATA=S_FRONT;
    }
  if(digitalRead(INFO_COLLECT_R1))
  {
    STATA=S_RIGHT_30;
    }
  if(digitalRead(INFO_COLLECT_R2))
  {
    STATA=S_RIGHT_60;
    }
  }
void setup() {
  // put your setup code here, to run once:
  Init();

}

void loop() {
  // put your main code here, to run repeatedly:
  Collect_Info();
  Control(STATA);

}
