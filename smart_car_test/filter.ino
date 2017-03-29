#include"public.h"

enum {COL_RV, COL_WV, COL_END} COL_STATA;


//采集标准值
extern float r_value = 0;
extern float w_value = 0;
//Ave_Value()
byte r_count = 0;
byte w_count = 0;
//Filter()
int new_value = 0;
int last_value = 0;

void Ave_Value()
{
  int temp = 0;
  while (COL_STATA != COL_END)
  {
    switch (COL_STATA)
    {
      case COL_RV:
        {
          temp = analogRead(INFO_COLLECT_0);
          if (BACKLINE_MIN < temp && temp < BACKLINE_MAX)
          {
            r_value += temp / 100.0;
            if (++r_count > 100)
            {
              COL_STATA = COL_WV;
              delay(5000);
            }
          }
          break;
        }
      case COL_WV:
        {
          temp = analogRead(INFO_COLLECT_0);
          if (BLANK_MIN < temp && temp < BLANK_MAX)
          {
            w_value += temp / 100.0;
            if (++w_count > 100)COL_STATA = COL_END;
          }
          break;
        }
    }
  }

}
void Test_print()
{
  Ave_Value();
  Serial.println(r_value);
  Serial.println(w_value);
}
float Filter(char info)
{
  last_value = new_value;
  new_value = analogRead(info);
  if ( ( new_value - r_value > THRESHOLD ) || ( r_value - new_value -  > THRESHOLD ))
  {
    return new_value;
  }
  else if ( ( new_value - w_value > THRESHOLD ) || ( w_value - new_value -  > THRESHOLD ))
  {
    return new_value;
  }
  else 
  {
    return last_value;
    }

}
