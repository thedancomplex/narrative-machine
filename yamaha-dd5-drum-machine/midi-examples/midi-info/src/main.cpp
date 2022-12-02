//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Mon Jan  4 01:29:39 PST 1999
// Last Modified: Mon Jan  4 01:29:51 PST 1999
// Filename:      ...linuxmidi/cpp/midiinfo.cpp
// Syntax:        C++ 
// $Smake:        g++ -DLINUX -O3 -Wall -o %b %f Sequencer.cpp && strip %b
//
// Description:   displays the MIDI input/output devices which can be
//                accessed through /dev/sequencer.
//


#include <iostream>
#include "Sequencer.h"


int main(void) {
   Sequencer sequencer;

   cout << "\nNumber of MIDI outputs: " << sequencer.getNumOutputs() << '\n';
   sequencer.displayOutputs();

   cout << "\nNumber of MIDI inputs: " << sequencer.getNumInputs() << '\n';
   sequencer.displayInputs();

   cout << endl;

   return 0;
}


