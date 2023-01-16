#include "synth_3vco.h"
#include "note_freq.h"

Synth3Vco s3v = Synth3Vco();
NoteFreq  nf  = NoteFreq();

#define LED_PIN 13

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  s3v.setSetup();
}


double freq = nf.note(nf.c4);
void loop() 
{
  // put your main code here, to run repeatedly:
  freq = nf.note(nf.c4);
  s3v.setFreq(freq);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  freq = nf.note(nf.a4);
  s3v.setFreq(freq);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
