#include "synth_3vco.h"
#include "note_freq.h"

Synth3Vco s3v = Synth3Vco();
NoteFreq  nf  = NoteFreq();

void setup() 
{
  s3v.setSetup();
}


void loop() 
{
  // put your main code here, to run repeatedly:
  s3v.setFreq(nf.note(nf.c4));
  delay(1000);
  s3v.setFreq(nf.note(nf.a4));
  delay(1000);
}
