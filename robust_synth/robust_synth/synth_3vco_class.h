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

class Synth3Vco
{

  public:
    Synth3Vco();
    int setSetup();
    int setMixerFinalGain();
    int setMixerFinalGain(double final_all, double final_no_envelope, double final_no_filter, double final_vco3);
    int setEnvelope();
    int setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double release_ms);
    int setEnvelope(double delay_ms, double attack_ms, double hold_ms, double decay_ms, double sustain_level, double release_ms, double releaseNoteOn_ms);
    int setFilterVal();
    int setFilterVal(double k_freq, double k_q, double k_octave);
    int setVolume(double val);
    int setFreq(double val);
    int setFreq(double val, double delta);
    int setFreq(double val, double delta, double the_div);
    int setFilterGain();
    int setFilterGain(double k_low_pass, double k_band_pass, double k_high_pass, double k_lof3);
    int setVcoGain();
    int setVcoGain(double k_vco1, double k_vco2, double k_vco3, double k_noise);
    int setVcoXGain(int id_vco, double k_sine, double k_saw, double k_square, double k_triangle);
    int setStartVco();
    int setStartVco(double val);
    int setStartVco(double val, double delta);
    int setStartVco(int ret);

  private:
    double starting_amp = 1.0;
  
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
    
    double vco1_mix_amp  = 1.0;
    double vco2_mix_amp  = 0.0;
    double vco3_mix_amp  = 0.0;
    double noise_mix_amp = 0.0;
    
    double amp_pre_filter =   1.0;
    double filter_freq    = 440.0;
    double filter_q       =   0.707;
    double filter_octaves =   2.5;
    
    double mixer_filter_low_pass  = 1.0;
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
    
    double mixer_final_all         = 0.0;
    double mixer_final_no_envelope = 1.0;
    double mixer_final_no_filter   = 0.0;
    double mixer_final_vco3        = 0.0;
    
    double amp_final = 1.0;
  
};
