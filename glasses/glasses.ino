#include"Wire.h"
#include"SSd1306_Wire.h"
#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 11;

SoftwareSerial mySerial (rxPin, txPin);

SSD1306_Wire ssd1306;

int i = 0;
String value;
void setup() {
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    ssd1306.Initial();
    delay(10);
    mySerial.begin(9600);
    Serial.begin(9600);
    ssd1306.Clear_Screen();
    ssd1306.Show_String(0, 2, "testtest");
    ssd1306.Show_String(0, 4, "testtest");
}

void loop() {
  if(mySerial.available()>0)
  {
    value = mySerial.readString();
    Serial.println(value);
    ssd1306.Clear_Screen();
    ssd1306.Show_String(0, 2, value);  
  }
    ssd1306.Show_String(0, 2, "testtest");
    ssd1306.Show_String(0, 4, "testtest");
  //ssd1306.Show_Ch(0,2,'A');
  //ssd1306.Fill_Screen();
  delay(1000);
}
