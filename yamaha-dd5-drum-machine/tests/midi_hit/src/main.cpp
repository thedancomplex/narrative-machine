// cmidiin.cpp
#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include <narrative-machine-yamaha-dd5-drum-machine.h>
#include <unistd.h>
#include <string.h>

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

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  unsigned int nBytes = message->size();
  for ( unsigned int i=0; i<nBytes; i++ )
    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  if ( nBytes > 0 )
    std::cout << "stamp = " << deltatime << std::endl;
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

  wait_for_exit();
  cleanup();
  return 0;
}

