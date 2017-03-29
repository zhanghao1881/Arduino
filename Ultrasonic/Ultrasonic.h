#include <arduino.h>
/*arduino nano pin*/
#define Trig 2
#define Echo 3

extern enum{M,CM,MM}UNIT;

class _Ultrasonic
{
  public:
      _Ultrasonic();
      void begin();
      float readDistant();
      float readDistant( word UNIT);
  };

  extern _Ultrasonic Ultrasonic;
