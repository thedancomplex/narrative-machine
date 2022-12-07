// cmidiin.cpp
#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include <narrative-machine-yamaha-dd5-drum-machine.h>
#include <unistd.h>
#include <string.h>
#include <thread>

/* Make Midi Object */
RtMidiIn *midiin = new RtMidiIn();

/* Make DD5 System Object */
NarrativeMachineYamahaDD5 dd5 = NarrativeMachineYamahaDD5();

int the_midi_port = 1;

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData );
int  setup();
int  setup(int midi_port);
int  cleanup();
int  wait_for_exit();
int  set_update_loop();
int  run_loop(int the_loop);

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  unsigned int nBytes = message->size();
  unsigned char status = 0;
  unsigned char data0  = 0;
  unsigned char data1  = 0;

  unsigned char chan   = 0;
  unsigned char mode   = 0;

  for ( unsigned int i=0; i<nBytes; i++ )
  {
    std::cout << "nBytes = "<< nBytes << " Byte " << i << " = " << (int)message->at(i) << ", ";
    if      ( i == 0 ) status = message->at(0);
    else if ( i == 1 ) data0  = message->at(1);
    else if ( i == 2 ) data1  = message->at(2);
  }

  mode = (status & 0b01110000) >> 4;
  chan = (status & 0b00001111) >> 0;


  if ( nBytes > 0 )
    {
      std::cout << " chan = " << (int)chan << " stamp = " << deltatime << std::endl;
      dd5.hit(MOT_ID_STICK_0);
      dd5.hit(MOT_ID_STICK_1);
    }
}

int run_loop(int the_loop)
{
  dd5.loop();
  return 0;
}

int set_update_loop()
{
  std::thread th1(run_loop, 0);
  th1.detach();
  return 0;
}

int setup()
{
  return setup(the_midi_port);
}

int setup(int midi_port)
{

  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    cleanup();
  }

  /* Open Midi Port */
  midiin->openPort( midi_port );


  /* Setup DD5 */
  int r = 0;

  /* Turn On System */
  r = dd5.on();
  dd5.sleep(1.0);

  /* Calibrate */
  printf("Calibrate %d and %d\n", MOT_ID_STICK_0, MOT_ID_STICK_1);
  r = dd5.calibrate(MOT_ID_STICK_0);
  r = dd5.calibrate(MOT_ID_STICK_1);

  printf("DD5 Calibrated\n");

  /* Make Midi Callback */
  // Set our callback function.  This should be done immediately after
  // opening the port to avoid having incoming messages written to the
  // queue.
  midiin->setCallback( &mycallback );

  /* Set Midi Read Types */
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  return 0;
}

int wait_for_exit()
{
  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  char input;
  std::cin.get(input);
  return 0;
}

int cleanup()
{
  /* Turn Off System */
  int r = dd5.off();

  delete midiin;
  return r;
}

int main()
{
  setup();
  set_update_loop();

  wait_for_exit();
  cleanup();
  return 0;
}

