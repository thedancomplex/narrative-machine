// cmidiin.cpp
#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

RtMidiIn *midiin = new RtMidiIn();

int the_midi_port = 1;

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData );
int  setup();
int setup(int midi_port);
int  cleanup();

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

  /* Make Midi Callback */
  // Set our callback function.  This should be done immediately after
  // opening the port to avoid having incoming messages written to the
  // queue.
  midiin->setCallback( &mycallback );

  /* Set Midi Read Types */
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );
  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  char input;
  std::cin.get(input);

  return 0;
}

int cleanup()
{
  delete midiin;
  return 0;
}

int main()
{
  setup();
  return 0;
}

