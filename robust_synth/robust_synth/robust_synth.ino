#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthNoiseWhite     NOISE;         //xy=124,1003
AudioSynthWaveformModulated VCO1_SINE;   //xy=310,138.75
AudioSynthWaveformModulated VCO1_SAW;   //xy=314,197
AudioSynthWaveformModulated VCO3_SINE; //xy=315,763
AudioSynthWaveformModulated VCO2_SINE; //xy=317,456
AudioSynthWaveformModulated VCO3_SAW; //xy=319,820
AudioSynthWaveformModulated VCO2_SAW; //xy=321,513
AudioSynthWaveformModulated VCO1_SQUARE;   //xy=328,260
AudioSynthWaveformModulated VCO1_TRIANGLE;   //xy=332,323
AudioSynthWaveformModulated VCO3_SQUARE; //xy=333,883
AudioSynthWaveformModulated VCO2_SQUARE; //xy=335,576
AudioSynthWaveformModulated VCO3_TRIANGLE; //xy=337,946
AudioSynthWaveformModulated VCO2_TRIANGLE; //xy=339,639
AudioMixer4              VCO1_MIX;         //xy=575,224
AudioMixer4              VCO3_MIX; //xy=580,847
AudioMixer4              VCO2_MIX; //xy=582,540
AudioAmplifier           VCO1_AMP;           //xy=745,222.25
AudioAmplifier           NOISE_AMP;           //xy=744.0000610351562,1011
AudioAmplifier           VCO3_AMP; //xy=750,845.25
AudioAmplifier           VCO2_AMP; //xy=752,538.25
AudioMixer4              VCO_MIXER;         //xy=1042.25,244.75003051757812
AudioAmplifier           AMP_PRE_FILTER;           //xy=1266.7500915527344,385.75
AudioAmplifier           VCO3_AMP_2;           //xy=1278.750244140625,831.25
AudioFilterStateVariable FILTER;        //xy=1494.5,326.25
AudioMixer4              MIXER_FILTER;         //xy=1675.5001220703125,333.0000305175781
AudioAmplifier           AMP_POST_FILTER;           //xy=1902.9999389648438,363.7143249511719
AudioEffectEnvelope      ENVELOPE;      //xy=2122.5,300
AudioAmplifier           AMP_ENVELOPE;           //xy=2307.5,301.25
AudioMixer4              MIXER_FINAL;         //xy=2525,382.5
AudioAmplifier           AMP_FINAL;           //xy=2703.75,382.5
AudioOutputI2S           i2s1;           //xy=2867.8570556640625,384.46429443359375
AudioConnection          patchCord1(NOISE, NOISE_AMP);
AudioConnection          patchCord2(VCO1_SINE, 0, VCO1_MIX, 0);
AudioConnection          patchCord3(VCO1_SAW, 0, VCO1_MIX, 1);
AudioConnection          patchCord4(VCO3_SINE, 0, VCO3_MIX, 0);
AudioConnection          patchCord5(VCO2_SINE, 0, VCO2_MIX, 0);
AudioConnection          patchCord6(VCO3_SAW, 0, VCO3_MIX, 1);
AudioConnection          patchCord7(VCO2_SAW, 0, VCO2_MIX, 1);
AudioConnection          patchCord8(VCO1_SQUARE, 0, VCO1_MIX, 2);
AudioConnection          patchCord9(VCO1_TRIANGLE, 0, VCO1_MIX, 3);
AudioConnection          patchCord10(VCO3_SQUARE, 0, VCO3_MIX, 2);
AudioConnection          patchCord11(VCO2_SQUARE, 0, VCO2_MIX, 2);
AudioConnection          patchCord12(VCO3_TRIANGLE, 0, VCO3_MIX, 3);
AudioConnection          patchCord13(VCO2_TRIANGLE, 0, VCO2_MIX, 3);
AudioConnection          patchCord14(VCO1_MIX, VCO1_AMP);
AudioConnection          patchCord15(VCO3_MIX, VCO3_AMP);
AudioConnection          patchCord16(VCO2_MIX, VCO2_AMP);
AudioConnection          patchCord17(VCO1_AMP, 0, VCO_MIXER, 0);
AudioConnection          patchCord18(NOISE_AMP, 0, VCO_MIXER, 3);
AudioConnection          patchCord19(VCO3_AMP, 0, VCO_MIXER, 2);
AudioConnection          patchCord20(VCO3_AMP, VCO3_AMP_2);
AudioConnection          patchCord21(VCO2_AMP, 0, VCO_MIXER, 1);
AudioConnection          patchCord22(VCO_MIXER, AMP_PRE_FILTER);
AudioConnection          patchCord23(AMP_PRE_FILTER, 0, FILTER, 0);
AudioConnection          patchCord24(AMP_PRE_FILTER, 0, MIXER_FINAL, 2);
AudioConnection          patchCord25(VCO3_AMP_2, 0, MIXER_FILTER, 3);
AudioConnection          patchCord26(VCO3_AMP_2, 0, MIXER_FINAL, 3);
AudioConnection          patchCord27(FILTER, 0, MIXER_FILTER, 0);
AudioConnection          patchCord28(FILTER, 1, MIXER_FILTER, 1);
AudioConnection          patchCord29(FILTER, 2, MIXER_FILTER, 2);
AudioConnection          patchCord30(MIXER_FILTER, AMP_POST_FILTER);
AudioConnection          patchCord31(AMP_POST_FILTER, ENVELOPE);
AudioConnection          patchCord32(AMP_POST_FILTER, 0, MIXER_FINAL, 1);
AudioConnection          patchCord33(ENVELOPE, AMP_ENVELOPE);
AudioConnection          patchCord34(AMP_ENVELOPE, 0, MIXER_FINAL, 0);
AudioConnection          patchCord35(MIXER_FINAL, AMP_FINAL);
AudioConnection          patchCord36(AMP_FINAL, 0, i2s1, 0);
AudioConnection          patchCord37(AMP_FINAL, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=116,47
// GUItool: end automatically generated code


#define RETURN_OK   0
#define RETURN_FAIL 1
#define FREQ_MAX    5000.0
#define FREQ_MIN    0.0

double the_volume = 0.25;

double vco_1_freq = 440.0;
double vco_2_delta  = 0.0;
double vco_2_freq = 440.0 + vco_2_delta;
double vco_3_div  = 2.0;
double vco_3_freq = vco_1_freq / vco_3_div;


double vco1_mix_sine_amp     = 0.25;
double vco1_mix_saw_amp      = 0.25;
double vco1_mix_square_amp   = 0.25;
double vco1_mix_triangle_amp = 0.25;

double vco2_mix_sine_amp     = 0.25;
double vco2_mix_saw_amp      = 0.25;
double vco2_mix_square_amp   = 0.25;
double vco2_mix_triangle_amp = 0.25;

double vco3_mix_sine_amp     = 0.25;
double vco3_mix_saw_amp      = 0.25;
double vco3_mix_square_amp   = 0.25;
double vco3_mix_triangle_amp = 0.25;



#define ENUM_VCO1_SIN_ID       0
#define ENUM_VCO1_SAW_ID       1
#define ENUM_VCO1_SQUARE_ID    2
#define ENUM_VCO1_TRIANGLE_ID  3

#define ENUM_VCO2_SIN_ID       0
#define ENUM_VCO2_SAW_ID       1
#define ENUM_VCO2_SQUARE_ID    2
#define ENUM_VCO2_TRIANGLE_ID  3

#define ENUM_VCO3_SIN_ID       0
#define ENUM_VCO3_SAW_ID       1
#define ENUM_VCO3_SQUARE_ID    2
#define ENUM_VCO3_TRIANGLE_ID  3

double vco1_amp  = 1.0;
double vco2_amp  = 1.0;
double vco3_amp  = 1.0;
double noise_amp = 1.0;

double vco3_amp_2 = 1.0;

#define ENUM_VCO1_ID  0
#define ENUM_VCO2_ID  1
#define ENUM_VCO3_ID  2
#define ENUM_NOSIE_ID 3

double vco1_mix_amp  = 0.0;
double vco2_mix_amp  = 0.0;
double vco3_mix_amp  = 0.0;
double noise_mix_amp = 0.0;

double amp_pre_filter =   1.0;
double filter_freq    = 440.0;
double filter_q       =   0.707;
double filter_octaves =   2.5;

double mixer_filter_low_pass  = 0.0;
double mixer_filter_band_pass = 0.0;
double mixer_filter_high_pass = 0.0;
double mixer_filter_vco3      = 0.0;

#define ENUM_MIXER_ID_LOW_PASS  0
#define ENUM_MIXER_ID_BAND_PASS 1
#define ENUM_MIXER_ID_HIGH_PASS 2
#define ENUM_MIXER_ID_LFO3      3

double mixer_low_pass  = 0.25;
double mixer_band_pass = 0.25;
double mixer_high_pass = 0.25;
double mixer_lfo3      = 0.25;

double amp_post_filter = 1.0;

double envelope_delay_ms        =   0.0;
double envelope_attack_ms       =  10.5;
double envelope_hold_ms         =   2.5;
double envelope_decay_ms        =  35.0;
double envelope_sustain_level   =   1.0;
double envelope_release_ms      = 300.0;
double envelope_relaseNoteOn_ms =   5.0;
double envelope_amp             =   1.0;

#define ENUM_MIXER_FINAL_ALL         0
#define ENUM_MIXER_FINAL_NO_ENVELOPE 1
#define ENUM_MIXER_FINAL_NO_FILTER   2
#define ENUM_MIXER_FINAL_VCO3        3

double mixer_final_all         = 1.0;
double mixer_final_no_envelope = 0.0;
double mixer_final_no_filter   = 0.0;
double mixer_final_vco3        = 0.0;

double amp_final = 1.0;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(1300);

  double starting_amp = 1.0;

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

  NOISE.amplitude(     starting_amp);


  VCO1_MIX.gain(ENUM_VCO1_SIN_ID,      vco1_mix_sine_amp);
  VCO1_MIX.gain(ENUM_VCO1_SAW_ID,      vco1_mix_saw_amp);
  VCO1_MIX.gain(ENUM_VCO1_SQUARE_ID,   vco1_mix_square_amp);
  VCO1_MIX.gain(ENUM_VCO1_TRIANGLE_ID, vco1_mix_triangle_amp);

  VCO2_MIX.gain(ENUM_VCO2_SIN_ID,      vco2_mix_sine_amp);
  VCO2_MIX.gain(ENUM_VCO2_SAW_ID,      vco2_mix_saw_amp);
  VCO2_MIX.gain(ENUM_VCO2_SQUARE_ID,   vco2_mix_square_amp);
  VCO2_MIX.gain(ENUM_VCO2_TRIANGLE_ID, vco2_mix_triangle_amp);

  VCO3_MIX.gain(ENUM_VCO3_SIN_ID,      vco3_mix_sine_amp);
  VCO3_MIX.gain(ENUM_VCO3_SAW_ID,      vco3_mix_saw_amp);
  VCO3_MIX.gain(ENUM_VCO3_SQUARE_ID,   vco3_mix_square_amp);
  VCO3_MIX.gain(ENUM_VCO3_TRIANGLE_ID, vco3_mix_triangle_amp);

  VCO1_AMP.gain(   vco1_amp);
  VCO2_AMP.gain(   vco2_amp);
  VCO3_AMP.gain(   vco3_amp);
  NOISE_AMP.gain(  noise_amp);
  VCO3_AMP_2.gain( vco3_amp_2);


  VCO_MIXER.gain(ENUM_VCO1_ID,  vco1_mix_amp);
  VCO_MIXER.gain(ENUM_VCO2_ID,  vco2_mix_amp);
  VCO_MIXER.gain(ENUM_VCO3_ID,  vco3_mix_amp);
  VCO_MIXER.gain(ENUM_NOSIE_ID, noise_mix_amp);


  AMP_PRE_FILTER.gain(amp_pre_filter);

  FILTER.frequency(filter_freq);
  FILTER.resonance(filter_q);
  FILTER.octaveControl(filter_octaves);

  MIXER_FILTER.gain(ENUM_MIXER_ID_LOW_PASS,  mixer_low_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_BAND_PASS, mixer_band_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_HIGH_PASS, mixer_high_pass);
  MIXER_FILTER.gain(ENUM_MIXER_ID_LFO3,      mixer_lfo3);

  AMP_POST_FILTER.gain(amp_post_filter);

  ENVELOPE.delay(         envelope_delay_ms);
  ENVELOPE.attack(        envelope_attack_ms);
  ENVELOPE.hold(          envelope_hold_ms);
  ENVELOPE.decay(         envelope_decay_ms);
  ENVELOPE.sustain(       envelope_sustain_level);
  ENVELOPE.release(       envelope_release_ms);
  ENVELOPE.releaseNoteOn( envelope_relaseNoteOn_ms);
  AMP_ENVELOPE.gain(      envelope_amp);

  MIXER_FINAL.gain(ENUM_MIXER_FINAL_ALL,         mixer_final_all);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_NO_ENVELOPE, mixer_final_no_envelope);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_NO_FILTER,   mixer_final_no_filter);
  MIXER_FINAL.gain(ENUM_MIXER_FINAL_VCO3,        mixer_final_vco3);

  AMP_FINAL.gain(amp_final);

  sgtl5000_1.enable();
  sgtl5000_1.volume(the_volume);

}

int setEnvelope()
{
  return setEnvelope(envelope_delay_ms, envelope_attack_ms, envelope_hold_ms, envelope_decay_ms, envelope_release_ms);
}

int setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double release_ms)
{
  return setEnvelope( delay_ms, attack_ms, hold_ms, decay_ms, envelope_sustain_level, release_ms, envelope_relaseNoteOn_ms);
}

int setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double sustain_level, double release_ms, double releaseNoteOn_ms)
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
  

int setFilterVal()
{
  return setFilterVal(filter_freq, filter_q, filter_octaves);
}
int setFilterVal(double k_freq, double k_q, double k_octave)
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

int setVolume(double val)
{
  int ret = RETURN_OK;
  if( val > 1.0 ){ val = 1.0; ret = RETURN_FAIL; }
  if( val < 0.0 ){ val = 0.0; ret = RETURN_FAIL; }

  the_volume = val;
  
  sgtl5000_1.volume(the_volume);
  
  return ret;
}

int setFreq(double val)
{
  return setFreq(val, vco_2_delta);
}

int setFreq(double val, double delta)
{
  return setFreq(val, delta, vco_3_div);
}

int setFreq(double val, double delta, double the_div)
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

int setFilterGain()
{
  return setFilterGain(mixer_low_pass, mixer_band_pass, mixer_high_pass, mixer_lfo3);
}
int setFilterGain(double k_low_pass, double k_band_pass, double k_high_pass, double k_lof3)
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

int setVcoGain()
{
  return setVcoGain(vco1_mix_amp, vco2_mix_amp, vco3_mix_amp, noise_mix_amp);
}
int setVcoGain(double k_vco1, double k_vco2, double k_vco3, double k_noise)
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

int setVcoXGain(int id_vco, double k_sine, double k_saw, double k_square, double k_triangle)
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

void loop() {
  // put your main code here, to run repeatedly:

}
