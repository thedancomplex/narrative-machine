//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Jan  3 21:02:02 PST 1999
// Last Modified: Mon Jan  4 01:28:05 PST 1999
// Filename:      Sequencer.cpp
// Syntax:        C++ 
// $Smake:        g++ -Wall -g -c %f && rm -f %b.o
//


#include <linux/soundcard.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include "Sequencer.h"


// define static variables:
const char* Sequencer::sequencer       = "/dev/sequencer";
int    Sequencer::sequencer_fd         = -1;
int    Sequencer::class_count          =  0;
uchar  Sequencer::midi_write_packet[4] = {SEQ_MIDIPUTC, 0, 0, 0};
uchar  Sequencer::midi_read_packet[4];


// static variables for MIDI I/O information database
int    Sequencer::indevcount      = 0;
int    Sequencer::outdevcount     = 0;

int*   Sequencer::indevnum        = NULL;
int*   Sequencer::outdevnum       = NULL;

int*   Sequencer::indevtype       = NULL;
int*   Sequencer::outdevtype      = NULL;

char** Sequencer::indevnames      = NULL;
char** Sequencer::outdevnames     = NULL;



///////////////////////////////
//
// Sequencer::Sequencer --
//	default value: autoOpen = 1;
//

Sequencer::Sequencer(int autoOpen) {
   if (autoOpen) {
      open();
   }

   if (class_count < 0) {
      cerr << "Unusual class instatiation count: " << class_count << endl;
      exit(1);
   } else if (class_count == 0) {
      buildInfoDatabase();
   }

   class_count++;
}



//////////////////////////////
//
// Sequencer::~Sequencer --
//

Sequencer::~Sequencer() {
   class_count--;

   if (class_count == 0) {
      close();
      removeInfoDatabase();
   } else if (class_count < 0) {
      cerr << "Unusual class instatiation count: " << class_count << endl;
      exit(1);
   }
}



//////////////////////////////
//
// Sequencer::close -- close the sequencer device.  The device
//   automatically closes once the program ends, but you can close it
//   so that other programs can use it.
//

void Sequencer::close(void) {
   ::close(getFd());
}



//////////////////////////////
//
// Sequencer::displayInputs -- display a list of the
//     available MIDI input devices.
//	default values: out = cout, initial = "\t"
//
 
void Sequencer::displayInputs(ostream& out, char* initial) const {
   for (int i=0; i<getNumInputs(); i++) {
      out << initial << i << ": " << getInputName(i) << '\n';
   }
}



//////////////////////////////
//
// Sequencer::displayOutputs -- display a list of the
//     available MIDI output devices.
//	default values: out = cout, initial = "\t"
//
 
void Sequencer::displayOutputs(ostream& out, char* initial) const {
   for (int i=0; i<getNumOutputs(); i++) {
      out << initial << i << ": " << getOutputName(i) << '\n';
   }
}



//////////////////////////////
//
// Sequencer::getInputName -- returns a string to the name of
//    the specified input device.  The string will remain valid as
//    long as there are any sequencer devices in existence.
//

const char* Sequencer::getInputName(int aDevice) const {
   if (aDevice >= getNumInputs()) {
      cerr << "Error: " << aDevice << " is greater than max in (" 
           << getNumInputs() << ")" << endl;
      exit(1);
   }

   return indevnames[aDevice];
}



//////////////////////////////
//
// Sequencer::getNumInputs -- returns the total number of
//     MIDI inputs that can be used.
//

int Sequencer::getNumInputs(void) const {
   return indevcount;
}



//////////////////////////////
//
// Sequencer::getNumOutputs -- returns the total number of
//     MIDI inputs that can be used.
//

int Sequencer::getNumOutputs(void) const {
   return outdevcount;
}



//////////////////////////////
//
// Sequencer::getOutputName -- returns a string to the name of
//    the specified output device.  The string will remain valid as
//    long as there are any sequencer devices in existence.
//

const char* Sequencer::getOutputName(int aDevice) const {
   if (aDevice >= getNumOutputs()) {
      cerr << "Error: " << aDevice << " is greater than max out (" 
           << getNumOutputs() << ")" << endl;
      exit(1);
   }

   return outdevnames[aDevice];
}



//////////////////////////////
//
// Sequencer::is_open -- returns true if the
//     sequencer device is open, false otherwise.
//

int Sequencer::is_open(void) const {
   if (getFd() > 0) {
      return 1;
   } else {
      return 0;
   }
}



/////////////////////////////
//
// Sequencer::open -- returns true if the device
//	was successfully opended (or already opened)
//

int Sequencer::open(void) {
   if (getFd() <= 0) {
      setFd(::open(sequencer, O_RDWR, 0));
   }
   
   return is_open();
}
   


//////////////////////////////
//
// Sequencer::read -- reads MIDI bytes and also stores the 
//     device from which the byte was read from.  Timing is not
//     saved from the device.  If needed, then it would have to 
//     be saved in this function, or just return the raw packet
//     data (use rawread function).
//
 
void Sequencer::read(uchar* buf, uchar* dev, int count) {
   int i = 0;
   while (i < count) {
      ::read(getFd(), midi_read_packet, sizeof(midi_read_packet));
      if (midi_read_packet[1] == SEQ_MIDIPUTC) {
         buf[i] = midi_read_packet[1];
         dev[i] = midi_read_packet[2];
         i++;
      }
   }
}



//////////////////////////////
//
// Sequencer::rawread -- read Input MIDI packets.
//    each packet contains 4 bytes.
//

void Sequencer::rawread(uchar* buf, int packetCount) {
   ::read(getFd(), buf, packetCount * 4);
}



//////////////////////////////
//
// Sequencer::rebuildInfoDatabase -- rebuild the internal
//   database that keeps track of the MIDI input and output devices.
//

void Sequencer::rebuildInfoDatabase(void) {
   removeInfoDatabase();
   buildInfoDatabase();
}



///////////////////////////////
//
// Sequencer::write -- Send a byte out the specified MIDI
//    port which can be either an internal or an external synthesizer.
//

void Sequencer::write(int device, int aByte) {
   switch (getOutputType(device)) {
      case MIDI_EXTERNAL:
         midi_write_packet[1] = (uchar) (0xff & aByte);
         midi_write_packet[2] = getOutDeviceValue(device);
         ::write(getFd(), midi_write_packet, sizeof(midi_write_packet));
         break;
      case MIDI_INTERNAL:
         writeInternal(getOutDeviceValue(device), aByte);
         break;
   }
}


void Sequencer::write(int device, uchar* bytes, int count) {
   for (int i=0; i<count; i++) {
      write(device, bytes[i]);
   }
}


void Sequencer::write(int device, int* bytes, int count) {
   for (int i=0; i<count; i++) {
      write(device, bytes[i]);
   }
}



///////////////////////////////////////////////////////////////////////////
//
// private functions
//

//////////////////////////////
//
// Sequencer::buildInfoDatabase -- determines the number
//     of MIDI input and output devices available from
//     /dev/sequencer, and determines their names.
//

void Sequencer::buildInfoDatabase(void) {
   int status;

   // read number of inputs available (external MIDI devices only)
   status = ioctl(getFd(), SNDCTL_SEQ_NRMIDIS, &indevcount);
   if (status!= 0) {
      cerr << "Error determining the number of MIDI inputs" << endl;
      exit(1);
   }

   // read number of output available
   int extmidi = indevcount;
   int intmidi;
   status = ioctl(getFd(), SNDCTL_SEQ_NRSYNTHS, &intmidi);
   if (status!= 0) {
      cerr << "Error determining the number of MIDI inputs" << endl;
      exit(1);
   }
   outdevcount = extmidi + intmidi;

   // allocate space for names and device number arrays
   if (indevnum != NULL || outdevnum != NULL || indevnames != NULL ||
         outdevnames != NULL || indevtype != NULL || outdevtype != NULL) {
      cerr << "Error: buildInfoDatabase called twice." << endl;
      exit(1);
   } 

   indevnum = new int[indevcount];
   outdevnum = new int[outdevcount];

   indevtype = new int[indevcount];
   outdevtype = new int[outdevcount];

   indevnames = new char*[indevcount];
   outdevnames = new char*[outdevcount];


   // fill in the device translation table and fill in the device names
   int i;
   struct midi_info midiinfo;
   for (i=0; i<indevcount; i++) {
      midiinfo.device = i;
      status = ioctl(getFd(), SNDCTL_MIDI_INFO, &midiinfo);
      if (status != 0) {
         cerr << "Error while reading MIDI device " << i << endl;
         exit(1);
      }

      indevnum[i]    = midiinfo.device;
      outdevnum[i]   = midiinfo.device;
      indevtype[i]   = MIDI_EXTERNAL;
      outdevtype[i]  = MIDI_EXTERNAL;
      indevnames[i]  = new char[strlen(midiinfo.name) + 1 + 10];
      outdevnames[i] = new char[strlen(midiinfo.name) + 1 + 11];
      strcpy(indevnames[i], midiinfo.name);
      strcpy(outdevnames[i], midiinfo.name);
      strcat(indevnames[i], " (MIDI In)");
      strcat(outdevnames[i], " (MIDI Out)");
   }

   char tempstring[1024] = {0};
   struct synth_info synthinfo;
   for (i=0; i<intmidi; i++) {
      synthinfo.device = i;
      status = ioctl(getFd(), SNDCTL_SYNTH_INFO, &synthinfo);
      if (status != 0) {
         cerr << "Error while reading MIDI device " << i << endl;
         exit(1);
      }
      outdevnum[extmidi+i] = i;
      outdevtype[extmidi + i] = MIDI_INTERNAL;

      strcpy(tempstring, synthinfo.name);
      switch (synthinfo.synth_type) {
         case SYNTH_TYPE_FM:           // 0
            strcat(tempstring, " (FM");
            switch (synthinfo.synth_subtype) {
               case FM_TYPE_ADLIB:     // 0
                  strcat(tempstring, " Adlib");
                  break;
               case FM_TYPE_OPL3:      // 1
                  strcat(tempstring, " OPL3");
                  break;
            }
            strcat(tempstring, ")");
            break;
         case SYNTH_TYPE_SAMPLE:       // 1
            strcat(tempstring, " (Wavetable)");
            break;
         case SYNTH_TYPE_MIDI:         // 2
            strcat(tempstring, " (MIDI Interface");
            switch (synthinfo.synth_subtype) {
               case SYNTH_TYPE_MIDI:   // 0x401
                  strcat(tempstring, " MPU401");
                  break;
            }
            strcat(tempstring, ")");
            break;
      }
      outdevnames[i+extmidi] = new char[strlen(tempstring) + 1];
      strcpy(outdevnames[i+extmidi], tempstring);
   }
}



//////////////////////////////
//
// Sequencer::getFd -- returns the file descriptor of the
//     sequencer device.
//

int Sequencer::getFd(void) const {
   return sequencer_fd;
}



//////////////////////////////
//
// Sequencer::getInDeviceValue --
//

int Sequencer::getInDeviceValue(int aDevice) const {
   if (aDevice >= getNumInputs()) {
      cerr << "Error: " << aDevice << " is greater than max in (" 
           << getNumInputs() << ")" << endl;
      exit(1);
   }

   return indevnum[aDevice];
}



//////////////////////////////
//
// Sequencer::getInputType -- returns 1 = external MIDI,
//     2 = internal MIDI
//

int Sequencer::getInputType(int aDevice) const {
   if (aDevice >= getNumInputs()) {
      cerr << "Error: " << aDevice << " is greater than max in (" 
           << getNumInputs() << ")" << endl;
      exit(1);
   }

   return indevtype[aDevice];
}



//////////////////////////////
//
// Sequencer::getOutDeviceValue --
//

int Sequencer::getOutDeviceValue(int aDevice) const {
   if (aDevice >= getNumOutputs()) {
      cerr << "Error: " << aDevice << " is greater than max out (" 
           << getNumOutputs() << ")" << endl;
      exit(1);
   }

   return outdevnum[aDevice];
}



//////////////////////////////
//
// Sequencer::getOutputType -- returns 1 = external MIDI,
//     2 = internal MIDI
//

int Sequencer::getOutputType(int aDevice) const {
   if (aDevice >= getNumOutputs()) {
      cerr << "Error: " << aDevice << " is greater than max out (" 
           << getNumOutputs() << ")" << endl;
      exit(1);
   }

   return outdevtype[aDevice];
}



//////////////////////////////
//
// Sequencer::removeInfoDatabase --
//

void Sequencer::removeInfoDatabase(void) {
   if (indevnum   != NULL)   delete [] indevnum;
   if (outdevnum  != NULL)   delete [] outdevnum;
   if (indevtype  != NULL)   delete [] indevtype;
   if (outdevtype != NULL)   delete [] outdevtype;
  
   int i;
   if (indevnames != NULL) {
      for (i=0; i<indevcount; i++) {
         if (indevnames[i] != NULL)    delete [] indevnames[i];
      }
      delete [] indevnames;
   }

   if (outdevnames != NULL) {
      for (i=0; i<outdevcount; i++) {
         if (outdevnames[i] != NULL)   delete [] outdevnames[i];
      }
      delete [] outdevnames;
   }
 
   indevnum    = NULL;
   outdevnum   = NULL;
   indevtype   = NULL;
   outdevtype  = NULL;
   indevnames  = NULL;
   outdevnames = NULL;

   indevcount = 0;
   outdevcount = 0;
}



//////////////////////////////
//
// Sequencer::setFd --
//

void Sequencer::setFd(int anFd) {
   sequencer_fd = anFd;
}




///////////////////////////////////////////////////////////////////////////
//
// private functions dealing with the stupid internal sythesizer messages
//   which have to be processed as complete messages as opposed to 
//   external MIDI devices which are processed on the driver level as
//   discrete bytes.
// 

// static variables related to the processing of message for internal MIDI:
uchar  Sequencer::synth_write_message[8];
uchar  Sequencer::synth_message_buffer[1024]   = {0};
int    Sequencer::synth_message_buffer_count   =  0;
int    Sequencer::synth_message_bytes_expected =  0;
int    Sequencer::synth_message_curr_device    =  -1;


//////////////////////////////
//
// Sequencer::writeInternal -- the device number is the 
//     driver's device number *NOT* this class's device numbering
//     system.  MIDI bytes are stored in a buffer until a complete
//     message is received, then a synth message is generated.
//     While a complete message is being received, the device number
//     cannot change.  The first byte of a message must be a MIDI
//     command (i.e., no running status). 
//

void Sequencer::writeInternal(int aDevice, int aByte) {
   if (synth_message_bytes_expected == 0) {
      // a new message is coming in.
      synth_message_curr_device = aDevice;
      if (aByte < 128) {
         cerr << "Error: MIDI output byte: " << aByte 
              << " is not a command byte." << endl;
         exit(1);
      } else {
         synth_message_buffer[0] = aByte;
         synth_message_buffer_count = 1;
      }

      switch (aByte & 0xf0) {
         case 0x80:   synth_message_bytes_expected = 3;   break;
         case 0x90:   synth_message_bytes_expected = 3;   break;
         case 0xA0:   synth_message_bytes_expected = 3;   break;
         case 0xB0:   synth_message_bytes_expected = 3;   break;
         case 0xC0:   synth_message_bytes_expected = 2;   break;
         case 0xD0:   synth_message_bytes_expected = 2;   break;
         case 0xE0:   synth_message_bytes_expected = 3;   break;
         case 0xF0:   cerr << "Can't handle 0xE0 yet" << endl;   exit(1);
         default:     cerr << "Unknown error" << endl;   exit(1);
      }
   }

   // otherwise expecting at least one more byte for the MIDI message
   else {
      if (synth_message_curr_device != aDevice) {
         cerr << "Error: device number changed during message" << endl;
         exit(1);
      }
      if (aByte > 127) {
         cerr << "Error: expecting MIDI data but got MIDI command: "
              << aByte << endl;
         exit(1);
      }

      synth_message_buffer[synth_message_buffer_count++] = aByte;
   }

   // check to see if the message is complete:
   if (synth_message_bytes_expected == synth_message_buffer_count) {
      transmitMessageToInternalSynth();
      synth_message_bytes_expected = 0;
      synth_message_buffer_count = 0;
   }
}

     

//////////////////////////////
//
// Sequencer::transmitMessageToInternalSynth -- send the stored
//    MIDI message to the internal synthesizer.
//

void Sequencer::transmitMessageToInternalSynth(void) {
   switch (synth_message_buffer[0] & 0xf0) {
      case 0x80:                      // Note-off
      case 0x90:                      // Note-on
      case 0xA0:                      // Aftertouch
         transmitVoiceMessage();
         break;
      case 0xB0:                      // Control change
      case 0xC0:                      // Patch change
      case 0xD0:                      // Channel pressure
      case 0xE0:                      // Pitch wheel
         transmitCommonMessage();
         break;
      case 0xF0:
         cerr << "Cannot handle 0xf0 commands yet" << endl;
         exit(1);
         break;
      default:
         cerr << "Error: unknown MIDI command" << endl;
         exit(1);
   }
}



//////////////////////////////
//
// Sequencer::transmitVoiceMessage -- send a voice-type MIDI
//     message to an internal synthesizer.
//

void Sequencer::transmitVoiceMessage(void) {
   synth_write_message[0] = EV_CHN_VOICE;
   synth_write_message[1] = synth_message_curr_device;
   synth_write_message[2] = synth_message_buffer[0] & 0xf0;
   synth_write_message[3] = synth_message_buffer[0] & 0x0f;
   synth_write_message[4] = synth_message_buffer[1];
   synth_write_message[5] = synth_message_buffer[2];
   synth_write_message[6] = 0;
   synth_write_message[7] = 0;

   ::write(getFd(), synth_write_message, sizeof(synth_write_message));
}



//////////////////////////////
//
// Sequencer::transmitCommonMessage -- send a common-type MIDI
//     message to an internal synthesizer.
//

void Sequencer::transmitCommonMessage(void) {
   synth_write_message[0] = EV_CHN_COMMON;
   synth_write_message[1] = synth_message_curr_device;
   synth_write_message[2] = synth_message_buffer[0] & 0xf0;
   synth_write_message[3] = synth_message_buffer[0] & 0x0f;

   switch (synth_write_message[2]) {
      case 0xB0:                           // Control change
         synth_write_message[4] = synth_message_buffer[1];
         synth_write_message[5] = 0;
         synth_write_message[6] = synth_message_buffer[2];
         synth_write_message[7] = 0;
         break;
      case 0xC0:                           // Patch change
      case 0xD0:                           // Channel pressure
         synth_write_message[4] = synth_message_buffer[1];
         synth_write_message[5] = 0;
         synth_write_message[6] = 0;
         synth_write_message[7] = 0;
         break;
      case 0xE0:                           // Pitch wheel
         synth_write_message[4] = 0;
         synth_write_message[5] = 0;
         synth_write_message[6] = synth_message_buffer[1];
         synth_write_message[7] = synth_message_buffer[2];
         break;
      default:
         cerr << "Unknown Common MIDI message" << endl;
         exit(1);
   }

   ::write(getFd(), synth_write_message, sizeof(synth_write_message));
}




