#ifndef _PROTOCOL_H
#define _PROTOCOL_H


#include "Arduino.h"
#include "String.h"

#define BUFFER_LENGTH 16

class PROTOCOL
{


  public:
    static bool flag;
    static float value;

    void SendData(float voltage, float current);
    void RecData();
};



#endif
