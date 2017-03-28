void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);//x
  pinMode(A1,INPUT);//y
  pinMode(A2,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.println(digitalRead(A2));
  delay(300);

}
