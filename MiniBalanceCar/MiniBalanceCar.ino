//THE MOTOR INFORMATION
#define ENCODER_L 2
#define ENCODER_R 3
#define DIRECTION_L 4
#define DIRECTION_R 5

//THE MOTOR CONTROL
#define MA1 6
#define MA2 7
#define MB1 8
#define MB2 9
#define PWMA 10
#define PWMB 11

//IIC SDA A4 SCL A5
#include<Wire.h>

//MPU6050
#include<MPU6050.h>
//
#include <KalmanFilter.h>


MPU6050 poseInfo; //instantiation MPU6050,
KalmanFilter KalFilter;//实例化一个卡尔曼滤波器对象，对象名称为 KalFilter

//x,y,z
int16_t ax, ay, az;
int16_t gx, gy, gz;
//***************下面是卡尔曼滤波相关变量***************//
float K1 = 0.05; // 对加速度计取值的权重
float Q_angle = 0.001, Q_gyro = 0.005;
float R_angle = 0.5 , C_0 = 1;
float dt = 0.005; //注意：dt的取值为滤波器采样时间 5ms
int addr = 0;

void setup() {
  // put your setup code here, to run once:
  Initialize();

}

void loop() {
  // put your main code here, to run repeatedly:
  testPoseInfo();

}

void Initialize()
{
  Wire.begin();

  Serial.begin(38400);

  // initialize device MPU6050
  Serial.println("Initializing I2C devices...");
  poseInfo.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(poseInfo.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


}

void testPoseInfo()
{
  // read raw accel/gyro measurements from device
  poseInfo.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

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
