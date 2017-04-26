void setup() {
  // put your setup code here, to run once:
  pinMode(A0,OUTPUT);//INPUT
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A0,HIGH);
  delay(100);
  digitalWrite(A0,LOW);
  delay(100);
}
