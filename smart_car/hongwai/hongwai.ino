void setup() {
  // put your setup code here, to run once:
  pinMode(3,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(3))
  {
    Serial.println("black");
    }
   else
   {
    Serial.println("white");
    }
    delay(500);
}
