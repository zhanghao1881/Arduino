#include<SoftwareSerial.h>
SoftwareSerial softSerial(10,11);
String str1;

char y[100];//定义数组y存储串口返回的信息
int i;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);                  //初始化虚拟串口
softSerial.begin(9600);
softSerial.listen();
wifiInit();//wifI初始化
for(i=2;i<=9;i++)
{
   pinMode(i,OUTPUT);
   digitalWrite(i,LOW);
}

}

void loop() {
  // put your main code here, to run repeatedly:
  String str2;
if(softSerial.read()>0)
{
   String s=softSerial.readString();              //读取串口的数据
   str1=s; 
   char Array[str1.length() + 1];                      //将string 转化为char 
   str1.toCharArray(Array,str1.length() + 1);
   
   stringcut(Array);                           //除去没有用的信息
                       //打印到串口监视器
   for(i=0;i<100&y[i]!='\0';i++){                  
      str2 += y[i];                                 //转化为String
    }                                         
  Serial.println(str2);
  ledcontro(str2 );
  


}
}
void wifiInit()                         //初始化ＷＩＦＩ
{
softSerial.print("AT+CWMODE=2\r\n");
delay(100);
softSerial.print("AT+RST\r\n");
delay(500);

delay(100);
softSerial.print("AT+CIPMUX=1\r\n");
delay(100);
softSerial.print("AT+CIPSERVER=1,8080\r\n");
}
void stringcut(char *s)   //要求输入的是 char[]或者  char *s　　　　　　　　　除去ＯＫ等字符，保留输入数据到ｙ数组中来
{  
    
    int i=0;
   while(*s!='\0')
   {  
     if(*s==':')    //字符串隔断标志；将从此字符后开始截取一段新的字符串
     { 
         s++;
        while(*s!='\0')
        { 
           y[i]=*s;
          i++;
         s++;
        }
        y[i]='\0';
        
      }
      s++;
 }
}
void ledcontro(String s )
{
   if(s== "led1on")
        
        digitalWrite(2,HIGH);
        
                
   if(s== "led2on")            
       digitalWrite(3,HIGH);
               
    if(s== "led3on")       
       digitalWrite(4,HIGH);
               
    if(s== "led4on")     
       digitalWrite(5,HIGH);
               
     if(s== "led5on")           
       digitalWrite(6,HIGH);
             
    if(s== "led6on")          
       digitalWrite(7,HIGH);
                
    if(s== "led7on")          
       digitalWrite(8,HIGH);
                 
    if(s== "led1on")         
       digitalWrite(9,HIGH);


     if(s== "led1off")
        digitalWrite(2,LOW);
                
   if(s== "led2off")            
       digitalWrite(3,LOW);
               
    if(s== "led3off")       
       digitalWrite(4,LOW);
               
    if(s== "led4off")     
       digitalWrite(5,LOW);
               
     if(s== "led5off")           
       digitalWrite(6,LOW);
             
    if(s== "led6off")          
       digitalWrite(7,LOW);
                
    if(s== "led7off")          
       digitalWrite(8,LOW);
                 
    if(s== "led8off")         
       digitalWrite(9,LOW);
                

    }


