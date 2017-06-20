#include "protocol.h"


bool PROTOCOL::flag = 0;
float PROTOCOL::value = 0.0;

void PROTOCOL::SendData(float voltage, float current)
{
  String data;
  data = 'V' + String(voltage) + 'A' + String(current);
  Serial.println(data);
}

void PROTOCOL::RecData()
{
  String floatchars = "";
  char flagchar = "";
  while(Serial.available())
  {
    char temp = Serial.read();
    if(isDigit(temp)||temp == '.')
    {
      floatchars+=temp;
      }
      else
      {
        flagchar = temp;
        }
    }
    value = floatchars.toFloat();
    if(flagchar == 'A'){
      flag = 1;
    }
    else if(flagchar =='V'){
      flag = 0;
    }
    
}

