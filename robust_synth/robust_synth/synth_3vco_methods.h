Synth3Vco::Synth3Vco()
{
  
  return;
}

int Synth3Vco::setSetup()
{
   // put your setup code here, to run once:
  AudioMemory(1300);

  int ret = RETURN_OK;

  /* Start the VCOs */
  ret += this->setStartVco();
  
  NOISE.amplitude(     starting_amp);

  /* Setup Each VCOs gains */
  /*                       id   k_sine    k_saw    k_square    k_triangle */ 
  ret += this->setVcoXGain( 1 ,    0.0 ,    1.0 ,       0.0 ,         0.0 );
  ret += this->setVcoXGain( 2 ,    0.0 ,    0.0 ,       0.0 ,         0.0 );
  ret += this->setVcoXGain( 3 ,    0.0 ,    0.0 ,       0.0 ,         0.0 );

  VCO1_AMP.gain(   vco1_amp);
  VCO2_AMP.gain(   vco2_amp);
  VCO3_AMP.gain(   vco3_amp);
  NOISE_AMP.gain(  noise_amp);
  VCO3_AMP_2.gain( vco3_amp_2);

  /* Set VCO mixing gain */
  ret += this->setVcoGain();

  AMP_PRE_FILTER.gain(amp_pre_filter);

  /* Set default filter value */
  ret += this->setFilterVal();


  /* Set gains of each Filter type */
  ret += this->setFilterGain();
  
  AMP_POST_FILTER.gain(amp_post_filter);

  /* Set envelope paramaters */
  ret += this->setEnvelope();

  AMP_ENVELOPE.gain(      envelope_amp);

  /* Set Final Mixer Gains */
  ret += this->setMixerFinalGain();

  AMP_FINAL.gain(amp_final);

  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);

  ret += this->setVolume(the_volume);

  return ret;
}

int Synth3Vco::setStartVco()
{
  return this->setStartVco(RETURN_OK);
}

int Synth3Vco::setStartVco(double val)
{
  return this->setStartVco(val, vco_2_delta);
}

int Synth3Vco::setStartVco(double val, double delta)
{
  int ret = this->setFreq(val, delta);
  return this->setStartVco(ret);
}

int Synth3Vco::setStartVco(int ret)
{ 
  VCO1_SINE.begin(     starting_amp, WAVEFORM_SINE,     vco_1_freq);
  VCO2_SINE.begin(     starting_amp, WAVEFORM_SINE,     vco_2_freq);
  VCO3_SINE.begin(     starting_amp, WAVEFORM_SINE,     vco_3_freq);

  VCO1_SAW.begin(      starting_amp, WAVEFORM_SAWTOOTH, vco_1_freq);
  VCO2_SAW.begin(      starting_amp, WAVEFORM_SAWTOOTH, vco_2_freq);
  VCO3_SAW.begin(      starting_amp, WAVEFORM_SAWTOOTH, vco_3_freq);

  VCO1_SQUARE.begin(   starting_amp, WAVEFORM_SAWTOOTH, vco_1_freq);
  VCO2_SQUARE.begin(   starting_amp, WAVEFORM_SAWTOOTH, vco_2_freq);
  VCO3_SQUARE.begin(   starting_amp, WAVEFORM_SAWTOOTH, vco_3_freq);

  VCO1_TRIANGLE.begin( starting_amp, WAVEFORM_TRIANGLE, vco_1_freq);
  VCO2_TRIANGLE.begin( starting_amp, WAVEFORM_TRIANGLE, vco_2_freq);
  VCO3_TRIANGLE.begin( starting_amp, WAVEFORM_TRIANGLE, vco_3_freq);

  return ret;
}

int Synth3Vco::setMixerFinalGain()
{
  return this->setMixerFinalGain(mixer_final_all, mixer_final_no_envelope, mixer_final_no_filter, mixer_final_vco3);
}

int Synth3Vco::setMixerFinalGain(double final_all, double final_no_envelope, double final_no_filter, double final_vco3)
{
  int ret = RETURN_OK;
   
  if(final_all              < 0.0){ final_all           = 0.0; ret = RETURN_FAIL; }
  if(final_no_envelope      < 0.0){ final_no_envelope   = 0.0; ret = RETURN_FAIL; }
  if(final_no_filter        < 0.0){ final_no_filter     = 0.0; ret = RETURN_FAIL; }
  if(final_vco3             < 0.0){ final_vco3          = 0.0; ret = RETURN_FAIL; }

  mixer_final_all         = final_all;
  mixer_final_no_envelope = final_no_envelope;
  mixer_final_no_filter   = final_no_filter;
  mixer_final_vco3        = final_vco3;
  
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_ALL,         mixer_final_all);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_NO_ENVELOPE, mixer_final_no_envelope);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_NO_FILTER,   mixer_final_no_filter);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_VCO3,        mixer_final_vco3);

  return ret;
}

int Synth3Vco::setEnvelope()
{
  return this->setEnvelope(envelope_delay_ms, envelope_attack_ms, envelope_hold_ms, envelope_decay_ms, envelope_release_ms);
}

int Synth3Vco::setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double release_ms)
{
  return this->setEnvelope( delay_ms, attack_ms, hold_ms, decay_ms, envelope_sustain_level, release_ms, envelope_relaseNoteOn_ms);
}

int Synth3Vco::setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double sustain_level, double release_ms, double releaseNoteOn_ms)
{
  int ret = RETURN_OK;

  if( delay_ms         < 0.0 ) { delay_ms         = 0.0; ret = RETURN_FAIL; }
  if( attack_ms        < 0.0 ) { attack_ms        = 0.0; ret = RETURN_FAIL; }
  if( hold_ms          < 0.0 ) { hold_ms          = 0.0; ret = RETURN_FAIL; }
  if( decay_ms         < 0.0 ) { decay_ms         = 0.0; ret = RETURN_FAIL; }
  if( sustain_level    < 0.0 ) { sustain_level    = 0.0; ret = RETURN_FAIL; }
  if( release_ms       < 0.0 ) { release_ms       = 0.0; ret = RETURN_FAIL; }
  if( releaseNoteOn_ms < 0.0 ) { releaseNoteOn_ms = 0.0; ret = RETURN_FAIL; }

  //if( delay_ms         > 0.0 ) { delay_ms         = 0.0; ret = RETURN_FAIL; }
  if( attack_ms        > 11880.0 ) { attack_ms        = 11880.0; ret = RETURN_FAIL; }
  if( hold_ms          > 11880.0 ) { hold_ms          = 11880.0; ret = RETURN_FAIL; }
  if( decay_ms         < 11880.0 ) { decay_ms         = 11880.0; ret = RETURN_FAIL; }
  if( sustain_level    > 1.0     ) { sustain_level    = 1.0;     ret = RETURN_FAIL; }
  if( release_ms       < 11880.0 ) { release_ms       = 11880.0; ret = RETURN_FAIL; }
  //if( releaseNoteOn_ms < 0.0 ) { releaseNoteOn_ms = 0.0; ret = RETURN_FAIL; }

  envelope_delay_ms        = delay_ms;
  envelope_attack_ms       = attack_ms;
  envelope_hold_ms         = hold_ms;
  envelope_decay_ms        = decay_ms;
  envelope_sustain_level   = sustain_level;
  envelope_release_ms      = release_ms;
  envelope_relaseNoteOn_ms = releaseNoteOn_ms;
  
  ENVELOPE.delay(         envelope_delay_ms);
  ENVELOPE.attack(        envelope_attack_ms);
  ENVELOPE.hold(          envelope_hold_ms);
  ENVELOPE.decay(         envelope_decay_ms);
  ENVELOPE.sustain(       envelope_sustain_level);
  ENVELOPE.release(       envelope_release_ms);
  ENVELOPE.releaseNoteOn( envelope_relaseNoteOn_ms);

  return ret;
}
  

int Synth3Vco::setFilterVal()
{
  return this->setFilterVal(filter_freq, filter_q, filter_octaves);
}
int Synth3Vco::setFilterVal(double k_freq, double k_q, double k_octave)
{
  int ret = RETURN_OK;

  if( k_freq   < 0.0 ) { k_freq = 0.0;   ret = RETURN_FAIL; }
  if( k_q      < 0.7 ) { k_q    = 0.7;   ret = RETURN_FAIL; }
  if( k_q      > 5.0 ) { k_q    = 5.0;   ret = RETURN_FAIL; }
  if( k_octave < 0.0 ) { k_octave = 0.0; ret = RETURN_FAIL; }
  if( k_octave > 7.0 ) { k_octave = 7.0; ret = RETURN_FAIL; }

  filter_freq    = k_freq;
  filter_q       = k_q;
  filter_octaves = k_octave;
  
  FILTER.frequency(filter_freq);
  FILTER.resonance(filter_q);
  FILTER.octaveControl(filter_octaves);

  return ret;
}

int Synth3Vco::setVolume(double val)
{
  int ret = RETURN_OK;
  if( val > 1.0 ){ val = 1.0; ret = RETURN_FAIL; }
  if( val < 0.0 ){ val = 0.0; ret = RETURN_FAIL; }

  the_volume = val;
  
  sgtl5000_1.volume(the_volume);
  
  return ret;
}

int Synth3Vco::setFreq(double val)
{
  return this->setFreq(val, vco_2_delta);
}

int Synth3Vco::setFreq(double val, double delta)
{
  return this->setFreq(val, delta, vco_3_div);
}

int Synth3Vco::setFreq(double val, double delta, double the_div)
{
  int ret = RETURN_OK;

  double freq1 = val;

  if( freq1 > FREQ_MAX ){ freq1 = FREQ_MAX; ret = RETURN_FAIL; }
  if( freq1 < FREQ_MIN ){ freq1 = FREQ_MIN; ret = RETURN_FAIL; }
  
  double freq2 = freq1 + delta;
  
  if( freq2 > FREQ_MAX ){ freq2 = FREQ_MAX; ret = RETURN_FAIL; }
  if( freq2 < FREQ_MIN ){ freq2 = FREQ_MIN; ret = RETURN_FAIL; }

  double freq3 = freq1 / the_div;

  if( freq3 > FREQ_MAX ){ freq3 = FREQ_MAX; ret = RETURN_FAIL; }
  if( freq3 < FREQ_MIN ){ freq3 = FREQ_MIN; ret = RETURN_FAIL; }

  VCO1_SINE.frequency(    freq1);
  VCO1_SAW.frequency(     freq1);
  VCO1_SQUARE.frequency(  freq1);
  VCO1_TRIANGLE.frequency(freq1);

  VCO2_SINE.frequency(    freq2);
  VCO2_SAW.frequency(     freq2);
  VCO2_SQUARE.frequency(  freq2);
  VCO2_TRIANGLE.frequency(freq2);

  VCO3_SINE.frequency(    freq3);
  VCO3_SAW.frequency(     freq3);
  VCO3_SQUARE.frequency(  freq3);
  VCO3_TRIANGLE.frequency(freq3);

  
  return ret;
}

int Synth3Vco::setFilterGain()
{
  return this->setFilterGain(mixer_low_pass, mixer_band_pass, mixer_high_pass, mixer_lfo3);
}
int Synth3Vco::setFilterGain(double k_low_pass, double k_band_pass, double k_high_pass, double k_lof3)
{
  int ret = RETURN_OK;
  
  if(k_low_pass       < 0.0){ k_low_pass      = 0.0; ret = RETURN_FAIL; }
  if(k_band_pass      < 0.0){ k_band_pass     = 0.0; ret = RETURN_FAIL; }
  if(k_high_pass      < 0.0){ k_high_pass     = 0.0; ret = RETURN_FAIL; }
  if(k_lof3           < 0.0){ k_lof3          = 0.0; ret = RETURN_FAIL; }

  mixer_low_pass  = k_low_pass;
  mixer_band_pass = k_band_pass;
  mixer_high_pass = k_high_pass;
  mixer_lfo3      = k_lof3;
  
  MIXER_FILTER.gain(ENUM_MIXER_ID_LOW_PASS,  mixer_low_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_BAND_PASS, mixer_band_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_HIGH_PASS, mixer_high_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_LFO3,      mixer_lfo3);

  return ret;
}

int Synth3Vco::setVcoGain()
{
  return this->setVcoGain(vco1_mix_amp, vco2_mix_amp, vco3_mix_amp, noise_mix_amp);
}
int Synth3Vco::setVcoGain(double k_vco1, double k_vco2, double k_vco3, double k_noise)
{
  int ret = RETURN_OK;
  
  if(k_vco1      < 0.0){ k_vco1     = 0.0; ret = RETURN_FAIL; }
  if(k_vco2      < 0.0){ k_vco2     = 0.0; ret = RETURN_FAIL; }
  if(k_vco3      < 0.0){ k_vco3     = 0.0; ret = RETURN_FAIL; }
  if(k_noise     < 0.0){ k_noise    = 0.0; ret = RETURN_FAIL; }

  vco1_mix_amp  = k_vco1;
  vco2_mix_amp  = k_vco2;
  vco3_mix_amp  = k_vco3;
  noise_mix_amp = k_noise;
  
  VCO_MIXER.gain(ENUM_VCO1_ID,  vco1_mix_amp);
  VCO_MIXER.gain(ENUM_VCO2_ID,  vco2_mix_amp);
  VCO_MIXER.gain(ENUM_VCO3_ID,  vco3_mix_amp);
  VCO_MIXER.gain(ENUM_NOSIE_ID, noise_mix_amp);

  return ret;
}

int Synth3Vco::setVcoXGain(int id_vco, double k_sine, double k_saw, double k_square, double k_triangle)
{
  int ret = RETURN_OK;

  if(k_sine     < 0.0){ k_sine     = 0.0; ret = RETURN_FAIL; }
  if(k_saw      < 0.0){ k_saw      = 0.0; ret = RETURN_FAIL; }
  if(k_square   < 0.0){ k_square   = 0.0; ret = RETURN_FAIL; }
  if(k_triangle < 0.0){ k_triangle = 0.0; ret = RETURN_FAIL; }
  
  if( id_vco == 1 )
  {
    vco1_mix_sine_amp     = k_sine;
    vco1_mix_saw_amp      = k_saw;
    vco1_mix_square_amp   = k_saw;
    vco1_mix_triangle_amp = k_triangle;
    
    VCO1_MIX.gain(ENUM_VCO1_SIN_ID,      vco1_mix_sine_amp);
    VCO1_MIX.gain(ENUM_VCO1_SAW_ID,      vco1_mix_saw_amp);
    VCO1_MIX.gain(ENUM_VCO1_SQUARE_ID,   vco1_mix_square_amp);
    VCO1_MIX.gain(ENUM_VCO1_TRIANGLE_ID, vco1_mix_triangle_amp);

  }
  else if (id_vco == 2)
  {
    vco2_mix_sine_amp     = k_sine;
    vco2_mix_saw_amp      = k_saw;
    vco2_mix_square_amp   = k_saw;
    vco2_mix_triangle_amp = k_triangle;
    
    VCO2_MIX.gain(ENUM_VCO2_SIN_ID,      vco2_mix_sine_amp);
    VCO2_MIX.gain(ENUM_VCO2_SAW_ID,      vco2_mix_saw_amp);
    VCO2_MIX.gain(ENUM_VCO2_SQUARE_ID,   vco2_mix_square_amp);
    VCO2_MIX.gain(ENUM_VCO2_TRIANGLE_ID, vco2_mix_triangle_amp);
  }
  else if (id_vco == 3 )
  {
    vco3_mix_sine_amp     = k_sine;
    vco3_mix_saw_amp      = k_saw;
    vco3_mix_square_amp   = k_saw;
    vco3_mix_triangle_amp = k_triangle;
    
    VCO3_MIX.gain(ENUM_VCO3_SIN_ID,      vco3_mix_sine_amp);
    VCO3_MIX.gain(ENUM_VCO3_SAW_ID,      vco3_mix_saw_amp);
    VCO3_MIX.gain(ENUM_VCO3_SQUARE_ID,   vco3_mix_square_amp);
    VCO3_MIX.gain(ENUM_VCO3_TRIANGLE_ID, vco3_mix_triangle_amp);
  }
  else
  {
    ret = RETURN_FAIL;
  }
  
  return ret;
}
