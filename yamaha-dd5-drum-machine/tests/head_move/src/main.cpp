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

  /* Turn On System */
  r = dd5.on();
  dd5.sleep(1.0);

  /* Calibrate */
  printf("Calibrate %d and %d\n", MOT_ID_STICK_0, MOT_ID_STICK_1);
  r = dd5.calibrate(MOT_ID_STICK_0);
  r = dd5.calibrate(MOT_ID_STICK_1);
  r = dd5.calibrate(MOT_ID_STICK_2);
  r = dd5.calibrate(MOT_ID_STICK_3);

  printf("DD5 Calibrated\n");

  return 0;
}

int cleanup()
{
  /* Turn Off System */
  int r = dd5.off();

  return r;
}

int main()
{
  setup();

  double val = 1.0;
  for( int i = 0; i < 10; i++)
  {
    dd5.stageMot(MOT_ID_NKY, val);
    dd5.stageMot(MOT_ID_NKP1, val);
    dd5.stageMot(MOT_ID_NKP2, val);
    dd5.stageMot(MOT_ID_NKR, val);
    dd5.postMot();
    dd5.sleep(2.0);
    val = -val;
  }

  cleanup();
  return 0;
}

