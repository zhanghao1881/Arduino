#include "Arduino.h"
#include"public.h"
extern  int state;
extern  int frame_len;
extern  int data_pt;
extern  bool nedd_checksum ;

void get_cmd(int data);
int check_sum(unsigned int *data, unsigned int len);
void load_cmd(unsigned int *buf);
void get_file();
