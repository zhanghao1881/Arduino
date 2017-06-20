//************************************************************//
//*********************Read me*******************************//
//****************常见问题及解决方式*************************//
/*请一定先按照程序注释接线。
  请一定先按照程序注释接线。
  请一定先按照程序注释接线。

  1.小车向后跑：将向后的轮子的接线引脚交换
  例如：左轮向后跑，
  #define LEFT_MOTOR_FRONT 4
  #define LEFT_MOTOR_BACK 5
  将4和5交换位置改为
  #define LEFT_MOTOR_FRONT 5
  #define LEFT_MOTOR_BACK 4

  2.小车左右控制颠倒，在保证五个红外传感器接线和运行正常的情况下

  #define LEFT_MOTOR_FRONT 4
  #define LEFT_MOTOR_BACK 5

  #define RIGHT_MOTOR_FRONT 2
  #define RIGHT_MOTOR_BACK 3

  将两个FRONT和BACK对应的数字交换
  改为

  #define LEFT_MOTOR_FRONT 2
  #define LEFT_MOTOR_BACK 3

  #define RIGHT_MOTOR_FRONT 4
  #define RIGHT_MOTOR_BACK 5

  如果小车能够正常寻线了，那就可以进一步调试了
  但此时的小车寻线并不稳定，是因为电机的物理差异，
  所以在电压相同的情况下，电机的转速并不相同。
  因此需要我们在程序上修改数据
  详情见程序*/


//电机控制引脚相关宏定义
#define LEFT_MOTOR_FRONT 2  //左电机前进为D4引脚
#define LEFT_MOTOR_BACK 3  //左电机后退为D5引脚
#define LEFT_PWM 9            //控制左电机速度的D9引脚
#define RIGHT_MOTOR_FRONT 5  //右电机前进为D2引脚
#define RIGHT_MOTOR_BACK 4 //右电机后退为D3引脚
#define RIGHT_PWM 10         //控制右电机速度的D10引脚
#define MOTOR_EN 6           //控制电机驱动板使能的D6引脚

/*寻黑线传感器相关引脚宏定义
   --------------------------------------------车头-------------------------------------
   INFO_COLLECT_L2---INFO_COLLECT_L1---INFO_COLLECT_0---INFO_COLLECT_R1---INFO_COLLECT_R2
*/
#define INFO_COLLECT_L2 A0               //最左边的传感器接A4引脚
#define INFO_COLLECT_L1 A1               //次左边的传感器接A3引脚
#define INFO_COLLECT_0 A2                //中间的传感器接A2引脚
#define INFO_COLLECT_R1 A3               //次右边边的传感器接A3引脚
#define INFO_COLLECT_R2 A4               //最右边的传感器接A4引脚


//小车状态
enum {S_FRONT, S_RIGHT_30, S_RIGHT_60, S_LEFT_30, S_LEFT_60,} STATA;


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
  Serial.begin(9600);
}

void Motor(int pwm_l, int pwm_r)
{
  /*LEFT_MOTOR_FRONT--前进开关HIGH(开)/LOW(关)
     LEFT_MOTOR_BACK--后退开关HIGH(开)/LOW(关)
     所以前进状态为(LEFT_MOTOR_FRONT,HIGH)    (LEFT_MOTOR_BACK,LOW)*/
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

void Control(byte STATA)
{
  switch (STATA)         //想让小车跑的快跑的稳，请慢慢自行调试和修改以下五个参数
  {
    case S_FRONT:
      Motor(200, 200); //小车直行时左右电机的速度Motor(左电机速度, 右电机速度);
      break;
    case S_RIGHT_30:
      Motor(150, 50); //小车 小右转时左右电机的速度Motor(左电机速度, 右电机速度);
      break;
    case S_RIGHT_60:
      Motor(200, 50); //小车 大右转时左右电机的速度 Motor(左电机速度, 右电机速度);
      break;
    case S_LEFT_30:
      Motor(50, 150); //小车 小左转时左右电机的速度Motor(左电机速度, 右电机速度);
      break;
    case S_LEFT_60:
      Motor(50, 200); //小车 大左转时左右电机的速度Motor(左电机速度, 右电机速度);
      break;
    default:
      Motor(200, 200);
      break;
  }
}

//黑线信息采集
void Collect_Info()
{
  if (digitalRead(INFO_COLLECT_L2))
  {
    Serial.println("l2");
    STATA = S_LEFT_60;
  }
  else if (digitalRead(INFO_COLLECT_L1))
  {
    Serial.println("l1");
    STATA = S_LEFT_30;
  }
  else if (digitalRead(INFO_COLLECT_0))
  {
    Serial.println("0");
    STATA = S_FRONT;
  }
  else if (digitalRead(INFO_COLLECT_R1))
  {
    Serial.println("r1");
    STATA = S_RIGHT_30;
  }
  else if (digitalRead(INFO_COLLECT_R2))
  {
    Serial.println("r2");
    STATA = S_RIGHT_60;
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
  delay(10);
}
