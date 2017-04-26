void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);

}
int i =0;
void loop() {
  // put your main code here, to run repeatedly:
  if(i<255)
  {
    analogWrite(3,i++);
    }
  else 
  {
    i=0;
    }
    delay(10);
}
