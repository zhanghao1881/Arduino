#include "Wire.h"
#include "ADXL345.h"

float Xg;
void setup() {
  // put your setup code here, to run once:
  ADXL345.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Xg=ADXL345.readData(X);
  Serial.println(Xg);
  delay(500);

}
