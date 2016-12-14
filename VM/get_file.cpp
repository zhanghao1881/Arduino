#include"public.h"
#include"get_file.h"
int state = 0;
int frame_len = 0;
int data_pt = 0 ;
int need_checksum = false ;

int check_sum(unsigned int *data, unsigned int len)
{
  int ans = 0;
  int i;
  for ( i = 0; i < len; i++)
  {
    ans ^= *(data + 1);
  }
  return ans;
};

void get_cmd(int data)
{
  switch (state)
  {
    case 0:
      {
        if (data == 255) state = 1;
        break;
      }
    case 1:
      {
        frame_len = data;
        //length
        Serial.println(data);
        state = 2;
        break;
      }
    case 2:
      {
        buf[data_pt++] = data;
        Serial.println(buf[--data_pt]);
        if (data_pt >= MAX_BUF || data_pt >= frame_len)
        {
          state = 3;
          break;
        }
      }
    case 3:
      {
        if (!need_checksum)
        {
          load_cmd(buf);
        }
        else
        {
          if (check_sum(buf, frame_len) == data)
            load_cmd(buf);
        }
        state = 0;
        break;
      }
  }
};

void load_cmd(unsigned int *buf)
{
  int i,j;
  for (i = 0,j=0; i < frame_len; i += 2)
  {
    MEM[j++] = (buf[i] << 8) + buf[i + 1];
  }
  buf[MAX_BUF] = {0};
}

void get_file()
{
  bool flag = 0;

  while (1)
  {
    while (Serial.available() > 0)
    {
      get_cmd(Serial.read());
      flag = 1;
      delay(2);
    }
    if (flag == 1)
    {
      break;
    }
  }
}
