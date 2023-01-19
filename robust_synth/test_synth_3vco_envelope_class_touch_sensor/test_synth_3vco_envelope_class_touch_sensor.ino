
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
  
  double freq = nf.note(n);
  
  n++;
  if ( n >= NUM_NOTES ) n = 0 ;
  /*
  sv.setFreq(freq);
  sv.setVolume(vol);
  SerialUSB.println(freq);
  sv.noteOn();
  delay(100);
  sv.noteOff();
  delay(200);
  */
  int t = to.getTouch();

  if( t == TOUCH_START ) { sv.noteOn();  SerialUSB.println("noteOn");  }
  if( t == TOUCH_STOP  ) { sv.noteOff(); SerialUSB.println("noteOff"); }
  
}
