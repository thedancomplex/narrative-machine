
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


double getRand()
{
  int the_rand = random();
  double v = (double)(the_rand & 0xffff) / (double)(0xffff);
  return v;
}

int prev_rand = 0;
int doRand()
{
  double vol = sv.getVolumeKnob();
  int the_rand = 0;
  if ( vol > 0.5 ) the_rand = 1;
  else             the_rand = 0;

  int do_rand = 0;

  if ( ( the_rand == 1 ) & ( prev_rand == 0 ) ) do_rand = 1;
  else do_rand = 0;
  prev_rand = the_rand;

  if(do_rand == 1)
  {
    double v = getRand();
    for (int vco = 0; vco < NUM_VCO; vco++)
    {
      for (int type = 0; type < NUM_VOICES; type++)
      {
        double vol = getRand();
        if( vol < 0.5 ) vol = 0.0;
        sv.setVolume( vco,  type,  vol);
      }
    }
    SerialUSB.println("New Voice");
  }
  return do_rand;
}
void loop() {
  // put your main code here, to run repeatedly:

  //double vol = sv.getVolumeKnob();
  //sv.setVolume(vol*2.0);
  
  
  int n = 60; 
  
  int note     = 0;
  int t        = to.getTouch(&note);
  int the_note = to.getNote(note);
  
  //SerialUSB.println(the_note);
  doRand();
  
  if ( the_note > 0 )
  {
    double freq = nf.note( n + the_note );
    sv.setFreq(freq);
  }

  if     ( ( t == TOUCH_START ) ) { sv.noteOn();  SerialUSB.println("noteOn");  }
  else if( ( t == TOUCH_STOP  ) ) { sv.noteOff(); SerialUSB.println("noteOff"); }
  else if( ( t == TOUCH_NONE  ) ) { sv.noteOff();                               }
  
}
