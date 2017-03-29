#include "Ultrasonic.h"
// 设定SR04连接的Arduino引脚
//#define TrigPin  2 
//#define EchoPin  3 
float distance; 
void setup() 
{  
    Ultrasonic.begin();
    Serial.println("Ultrasonic sensor:");
} 
void loop() 
{ 

        distance = Ultrasonic.readDistant(M);
        Serial.print(distance); 
        Serial.print("m");
        distance = Ultrasonic.readDistant(CM);
        Serial.print(distance); 
        Serial.print("cm");  
        Serial.println(); 
        delay(1000); 
}
