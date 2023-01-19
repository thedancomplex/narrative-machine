
#include "synth_vco.h"
#include "note_freq.h"

SynthVco sv = SynthVco();
NoteFreq nf = NoteFreq();

void setup() {
  SerialUSB.begin(115200);
  sv.setup();
}

int n = 0;
void loop() {
  // put your main code here, to run repeatedly:

  double vol = sv.getVolumeKnob();
  
  double freq = nf.note(n);
  
  n++;
  if ( n >= NUM_NOTES ) n = 0 ;
  
  sv.setFreq(freq);
  sv.setVolume(vol);
  SerialUSB.println(freq);
  sv.noteOn();
  delay(100);
  sv.noteOff();
  delay(200);
}
