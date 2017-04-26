#include"Wire.h"
#include"SSd1306_Wire.h"

SSD1306_Wire ssd1306;
void setup() {
  // put your setup code here, to run once:
  ssd1306.Initial();
    delay(10);
    Serial.begin(9600);
}
int i =0;
void loop() {
  // put your main code here, to run repeatedly:
  ssd1306.Clear_Screen();
  ssd1306.Show_String(0,2,"~220V");
  delay(1000);
}
