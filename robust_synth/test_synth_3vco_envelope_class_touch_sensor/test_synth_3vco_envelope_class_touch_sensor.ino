
#include "synth_vco.h"
#include "note_freq.h"

#include "touch.h"

SynthVco sv = SynthVco();
NoteFreq nf = NoteFreq();
Touch    to = Touch();

void setup() {
  SerialUSB.begin(115200);
  sv.setup();
  to.setup();
  sv.setFreq(440.0);
  sv.setVolume(1.0);
}

int n = 0;
void loop() {
  // put your main code here, to run repeatedly:

  double vol = sv.getVolumeKnob();
  sv.setVolume(vol*2.0);
  
  
  int n = 60; 
  
  int note = 0;
  int t = to.getTouch(&note);
  int the_note = to.getNote(note);
  SerialUSB.println(the_note);
  if ( the_note > 0 )
  {
    double freq = nf.note( n + the_note );
    sv.setFreq(freq);
  }

  if     ( t == TOUCH_START ) { sv.noteOn();  SerialUSB.println("noteOn");  }
  else if( t == TOUCH_STOP  ) { sv.noteOff(); SerialUSB.println("noteOff"); }
  
}
