//************************************************************//
//*********************Read me*******************************//
//****************常见问题及解决方式*************************//
请一定先按照程序注释接线。
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
详情见程序
