// cmidiin.cpp
#include <iostream>
#include <cstdlib>
#include <narrative-machine-yamaha-dd5-drum-machine.h>
#include <unistd.h>
#include <string.h>
#include <thread>

/* Make DD5 System Object */
NarrativeMachineYamahaDD5 dd5 = NarrativeMachineYamahaDD5();

int setup()
{

  /* Setup DD5 */
  int r = 0;

  /* Add Neck Motors */
  dd5.add(MOT_ID_NKY);
  dd5.add(MOT_ID_NKY);
  dd5.add(MOT_ID_NKP1);
  dd5.add(MOT_ID_NKP2);
  dd5.add(MOT_ID_NKR);

  return 0;
}

int main()
{
  setup();

  double val = 0.2;
  for( int i = 0; i < 10; i++)
  {
    dd5.stageMot(MOT_ID_NKY, 0.0);
    dd5.stageMot(MOT_ID_NKP1, val);
    dd5.stageMot(MOT_ID_NKP2, -val);
    dd5.stageMot(MOT_ID_NKR, 0.0);
    dd5.postMot();
    dd5.sleep(2.0);
    val = -val;
  }

  return 0;
}

