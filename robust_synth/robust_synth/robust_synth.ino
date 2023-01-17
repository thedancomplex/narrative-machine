#include "synth_3vco.h"
#include "note_freq.h"

Synth3Vco s3v = Synth3Vco();
NoteFreq  nf  = NoteFreq();

#define LED_PIN 13

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  s3v.setSetup();
  s3v.setVolume(10.0);
  SerialUSB.begin(115200);
}


double freq = nf.note(nf.c4);
void loop() 
{
  int ret = -1;
  // put your main code here, to run repeatedly:
  freq = nf.note(nf.c4);
  freq = 880.0;
  ret = s3v.setFreq(freq);
  SerialUSB.print(ret);
  SerialUSB.print(" ");
  SerialUSB.println(freq);
  digitalWrite(LED_PIN, HIGH);
  s3v.setVolume(10.0);
  delay(1000);
  
  freq = nf.note(nf.a4);
  freq = 440.0;
  SerialUSB.print(ret);
  SerialUSB.print(" ");
  ret = s3v.setFreq(freq);
  SerialUSB.println(freq);
  digitalWrite(LED_PIN, LOW);
  s3v.setVolume(1.0);
  delay(1000);
}
