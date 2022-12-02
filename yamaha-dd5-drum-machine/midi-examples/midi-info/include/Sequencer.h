//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Jan  3 21:02:02 PST 1999
// Last Modified: Mon Jan  4 01:27:42 PST 1999
// Filename:      Sequencer.h
// Syntax:        C++ 
//

#ifndef _SEQUENCER_H_INCLUDED
#define _SEQUENCER_H_INCLUDED


#include <iostream>
#include <fstream>

#define MIDI_EXTERNAL  (1)
#define MIDI_INTERNAL  (2)
using namespace std;

typedef unsigned char uchar;


class Sequencer {
   public:
                    Sequencer      (int autoOpen = 1);
                   ~Sequencer      ();

      void          close                (void);
      void          displayInputs        (ostream& out = cout, 
                                            char* initial = "\t") const;
      void          displayOutputs       (ostream& out = cout, 
                                            char* initial = "\t") const;
      int           getNumInputs         (void) const;
      int           getNumOutputs        (void) const;
      const char*   getInputName         (int aDevice) const;
      const char*   getOutputName        (int aDevice) const;
      int           is_open              (void) const;
      int           open                 (void);
      void          read                 (uchar* buf, uchar* dev, int count);
      void          rawread              (uchar* buf, int packetCount);
      void          rebuildInfoDatabase  (void);
      void          write                (int aDevice, int aByte);
      void          write                (int aDevice, uchar* bytes, int count);
      void          write                (int aDevice, int* bytes, int count);
      
   protected:
      static const char* sequencer;         // name of sequencer device
      static int    sequencer_fd;           // sequencer file descriptor
      static int    class_count;            // number of existing classes using
      static uchar  midi_write_packet[4];   // for writing MIDI bytes out
      static uchar  midi_read_packet[4];    // for reading MIDI bytes out
      static uchar  synth_write_message[8]; // for writing to internal seq
      static int    indevcount;             // number of MIDI input devices
      static int    outdevcount;            // number of MIDI output devices
      static char** indevnames;             // MIDI input device names
      static char** outdevnames;            // MIDI output device names
      static int*   indevnum;               // total number of MIDI inputs
      static int*   outdevnum;              // total number of MIDI outputs
      static int*   indevtype;              // 1 = External, 2 = Internal
      static int*   outdevtype;             // 1 = External, 2 = Internal
      static uchar  synth_message_buffer[1024];   // hold bytes for synth dev
      static int    synth_message_buffer_count;   // count of synth buffer
      static int    synth_message_bytes_expected; // expected count of synth
      static int    synth_message_curr_device;    // for keeping track of dev

   private:
      void          buildInfoDatabase     (void);
      int           getFd                 (void) const;   
      int           getInDeviceValue      (int aDevice) const;
      int           getInputType          (int aDevice) const;
      int           getOutDeviceValue     (int aDevice) const;
      int           getOutputType         (int aDevice) const;
      void          removeInfoDatabase    (void);
      void          setFd                 (int anFd);   

      void          writeInternal(int aDevice, int aByte);
      void          transmitMessageToInternalSynth(void);
      void          transmitVoiceMessage(void);
      void          transmitCommonMessage(void);
};




#endif  // _SEQUENCER_H_INCLUDED


