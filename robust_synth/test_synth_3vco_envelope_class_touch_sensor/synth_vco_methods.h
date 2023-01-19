
SynthVco::SynthVco()
{
  return;
}

void SynthVco::noteOn()
{
  ENVELOPE.noteOn();
}

void SynthVco::noteOff()
{
  ENVELOPE.noteOff();
}

void SynthVco::setup()
{
  pinMode(VOLUME_PIN, INPUT);
  this->setAudioVectors();
  this->setupAudio();
}

double SynthVco::getVolumeKnob()
{
  int v = analogRead(VOLUME_PIN);
  double vol = (double)v / 1023.0;
  return vol;
}

void SynthVco::setAudioVectors()
{
  audio_vco[ENUM_VCO1][ENUM_SINE]     = &VCO1_SINE;
  audio_vco[ENUM_VCO2][ENUM_SINE]     = &VCO2_SINE;
  audio_vco[ENUM_VCO3][ENUM_SINE]     = &VCO3_SINE;

  audio_vco[ENUM_VCO1][ENUM_TRIANGLE] = &VCO1_TRIANGLE;
  audio_vco[ENUM_VCO2][ENUM_TRIANGLE] = &VCO2_TRIANGLE;
  audio_vco[ENUM_VCO3][ENUM_TRIANGLE] = &VCO3_TRIANGLE;
  
  audio_vco[ENUM_VCO1][ENUM_SQUARE]   = &VCO1_SQUARE;
  audio_vco[ENUM_VCO2][ENUM_SQUARE]   = &VCO2_SQUARE;
  audio_vco[ENUM_VCO3][ENUM_SQUARE]   = &VCO3_SQUARE;

  audio_vco[ENUM_VCO1][ENUM_SAW]      = &VCO1_SAW;
  audio_vco[ENUM_VCO2][ENUM_SAW]      = &VCO2_SAW;
  audio_vco[ENUM_VCO3][ENUM_SAW]      = &VCO3_SAW;
}

void SynthVco::setVolume(double vol)
{
  if( vol < 0.0 ) vol = 0.0;
  sgtl5000_1.volume(vol);
}

void SynthVco::setVolume(int vco, double vol)
{
  if      ( vol <  0.0 )            vol = 0.0;
  if      ( vco >  ENUM_VCO_COUNT ) return;
  if      ( vco == ENUM_VCO_NOISE ) NOISE_AMP.gain(vol);
  else if ( vco == ENUM_VCO1      ) VCO1_AMP.gain(vol);
  else if ( vco == ENUM_VCO2      ) VCO2_AMP.gain(vol);
  else if ( vco == ENUM_VCO3      ) VCO3_AMP.gain(vol);
  else if ( vco == ENUM_VCO_FINAL ) FINAL_AMP.gain(vol);

  return;
}

void SynthVco::setVolume(int vco, int type, double vol)
{
  if( vol < 0.0 ) vol = 0.0;
  audio_vco[vco][type]->amplitude(vol);
}

void SynthVco::setFreq(int vco, int type, double hz)
{
  if( hz > 10000.0 ) return;
  if( hz < 0.0     ) return;
  audio_vco[vco][type]->frequency(hz);
}

void SynthVco::setFreq(double hz)
{
  if( hz > 10000.0 ) return;
  if( hz < 0.0     ) return;

  double vco_1_freq = hz;

  this->setFreq(ENUM_VCO1, ENUM_SINE,     vco_1_freq);
  this->setFreq(ENUM_VCO1, ENUM_TRIANGLE, vco_1_freq);
  this->setFreq(ENUM_VCO1, ENUM_SQUARE,   vco_1_freq);
  this->setFreq(ENUM_VCO1, ENUM_SAW,      vco_1_freq);

  double vco_2_freq = hz * 1.1;

  this->setFreq(ENUM_VCO2, ENUM_SINE,     vco_2_freq);
  this->setFreq(ENUM_VCO2, ENUM_TRIANGLE, vco_2_freq);
  this->setFreq(ENUM_VCO2, ENUM_SQUARE,   vco_2_freq);
  this->setFreq(ENUM_VCO2, ENUM_SAW,      vco_2_freq);

  double vco_3_freq = hz / 4.0;

  this->setFreq(ENUM_VCO3, ENUM_SINE,     vco_3_freq);
  this->setFreq(ENUM_VCO3, ENUM_TRIANGLE, vco_3_freq);
  this->setFreq(ENUM_VCO3, ENUM_SQUARE,   vco_3_freq);
  this->setFreq(ENUM_VCO3, ENUM_SAW,      vco_3_freq);
}

void SynthVco::setupVcoVoice(int vco)
{
  if ( vco >= NUM_VCO ) return;
  if ( vco <  0       ) return;

  audio_vco[vco][ENUM_SINE]->begin(WAVEFORM_SINE);
  audio_vco[vco][ENUM_TRIANGLE]->begin(WAVEFORM_TRIANGLE);
  audio_vco[vco][ENUM_SQUARE]->begin(WAVEFORM_SQUARE);
  audio_vco[vco][ENUM_SAW]->begin(WAVEFORM_SAWTOOTH);  
}

void SynthVco::setupAudio()
{
  // put your setup code here, to run once:
  AudioMemory(300);
  sgtl5000_1.enable();

  /* Set Main Volume */
  this->setVolume(1.0);

  /* Set VCO Voices */
  this->setupVcoVoice(ENUM_VCO1);
  this->setupVcoVoice(ENUM_VCO2);
  this->setupVcoVoice(ENUM_VCO3);
  
  /* Set VCO Main Volume */
  this->setVolume(ENUM_VCO1,      1.0);
  this->setVolume(ENUM_VCO2,      1.0);
  this->setVolume(ENUM_VCO3,      1.0);
  this->setVolume(ENUM_VCO_NOISE, 1.0);
  this->setVolume(ENUM_VCO_FINAL, 1.0);

  for( int i = 0; i < NUM_VCO; i++ )
  {
    for( int j = 0; j < NUM_VOICES; j++ )
    {
       this->setVolume(i, j, 0.5);
    }
  }

  for( int i = 0; i < 4; i++ )
  {
    VCO1_MIX.gain(i,0.25);
    VCO2_MIX.gain(i,0.25);
    VCO3_MIX.gain(i,0.25);
    VCO_MIX_FINAL.gain(i,0.25);
  }

  this->setFreq(440.0);
}
