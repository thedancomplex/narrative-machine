
#include "synth_vco.h"

SynthVco sv = SynthVco();

void setup() {
  SerialUSB.begin(115200);
  sv.setup();
}

double freq = 440.0;

void loop() {
  // put your main code here, to run repeatedly:

  double vol = sv.getVolumeKnob();
  
  freq = 440.0;
  sv.setFreq(freq);
  sv.setVolume(vol);
  //SerialUSB.println(freq);
  sv.noteOn();
  delay(100);
  sv.noteOff();
  delay(200);
  
  freq = 880.0;
  sv.setFreq(freq);
  sv.setVolume(vol);
  //SerialUSB.println(freq);
  sv.noteOn();
  delay(100);
  sv.noteOff();
  delay(200);
  SerialUSB.println(vol);
}
