#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     VCO1_f;            //xy=107,105
AudioSynthWaveformDc     VCO3_f; //xy=112,728
AudioSynthWaveformDc     VCO2_f; //xy=114,421
AudioSynthNoiseWhite     noise1;         //xy=124,1003
AudioSynthWaveformModulated VCO1_SINE;   //xy=310,140
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
AudioAmplifier           VCO3_AMP_1; //xy=750,845.25
AudioAmplifier           VCO2_AMP; //xy=752,538.25
AudioMixer4              VCO_MIXER;         //xy=1042.25,244.75003051757812
AudioAmplifier           AMP_PRE_FILTER;           //xy=1266.7500915527344,385.75
AudioAmplifier           VCO3_AMP_2;           //xy=1278.750244140625,831.25
AudioSynthWaveformDc     FREQ_FILTER;            //xy=1292.2500610351562,480.25
AudioFilterStateVariable filter1;        //xy=1494.5,326.25
AudioMixer4              MIXER_FILTER;         //xy=1675.5001220703125,333.0000305175781
AudioAmplifier           AMP_POST_FILTER;           //xy=1902.9999389648438,363.7143249511719
AudioEffectEnvelope      ENVELOPE;      //xy=2122.5,300
AudioAmplifier           AMP_ENVELOPE;           //xy=2307.5,301.25
AudioMixer4              MIXER_FINAL;         //xy=2525,382.5
AudioAmplifier           AMP_FINAL;           //xy=2703.75,382.5
AudioOutputI2S           i2s1;           //xy=2867.8570556640625,384.46429443359375
AudioConnection          patchCord1(VCO1_f, 0, VCO1_SINE, 0);
AudioConnection          patchCord2(VCO1_f, 0, VCO1_SAW, 0);
AudioConnection          patchCord3(VCO1_f, 0, VCO1_SQUARE, 0);
AudioConnection          patchCord4(VCO1_f, 0, VCO1_TRIANGLE, 0);
AudioConnection          patchCord5(VCO3_f, 0, VCO3_SINE, 0);
AudioConnection          patchCord6(VCO3_f, 0, VCO3_SAW, 0);
AudioConnection          patchCord7(VCO3_f, 0, VCO3_SQUARE, 0);
AudioConnection          patchCord8(VCO3_f, 0, VCO3_TRIANGLE, 0);
AudioConnection          patchCord9(VCO2_f, 0, VCO2_SINE, 0);
AudioConnection          patchCord10(VCO2_f, 0, VCO2_SAW, 0);
AudioConnection          patchCord11(VCO2_f, 0, VCO2_SQUARE, 0);
AudioConnection          patchCord12(VCO2_f, 0, VCO2_TRIANGLE, 0);
AudioConnection          patchCord13(noise1, NOISE_AMP);
AudioConnection          patchCord14(VCO1_SINE, 0, VCO1_MIX, 0);
AudioConnection          patchCord15(VCO1_SAW, 0, VCO1_MIX, 1);
AudioConnection          patchCord16(VCO3_SINE, 0, VCO3_MIX, 0);
AudioConnection          patchCord17(VCO2_SINE, 0, VCO2_MIX, 0);
AudioConnection          patchCord18(VCO3_SAW, 0, VCO3_MIX, 1);
AudioConnection          patchCord19(VCO2_SAW, 0, VCO2_MIX, 1);
AudioConnection          patchCord20(VCO1_SQUARE, 0, VCO1_MIX, 2);
AudioConnection          patchCord21(VCO1_TRIANGLE, 0, VCO1_MIX, 3);
AudioConnection          patchCord22(VCO3_SQUARE, 0, VCO3_MIX, 2);
AudioConnection          patchCord23(VCO2_SQUARE, 0, VCO2_MIX, 2);
AudioConnection          patchCord24(VCO3_TRIANGLE, 0, VCO3_MIX, 3);
AudioConnection          patchCord25(VCO2_TRIANGLE, 0, VCO2_MIX, 3);
AudioConnection          patchCord26(VCO1_MIX, VCO1_AMP);
AudioConnection          patchCord27(VCO3_MIX, VCO3_AMP_1);
AudioConnection          patchCord28(VCO2_MIX, VCO2_AMP);
AudioConnection          patchCord29(VCO1_AMP, 0, VCO_MIXER, 0);
AudioConnection          patchCord30(NOISE_AMP, 0, VCO_MIXER, 3);
AudioConnection          patchCord31(VCO3_AMP_1, 0, VCO_MIXER, 2);
AudioConnection          patchCord32(VCO3_AMP_1, VCO3_AMP_2);
AudioConnection          patchCord33(VCO2_AMP, 0, VCO_MIXER, 1);
AudioConnection          patchCord34(VCO_MIXER, AMP_PRE_FILTER);
AudioConnection          patchCord35(AMP_PRE_FILTER, 0, filter1, 0);
AudioConnection          patchCord36(AMP_PRE_FILTER, 0, MIXER_FINAL, 2);
AudioConnection          patchCord37(VCO3_AMP_2, 0, MIXER_FILTER, 3);
AudioConnection          patchCord38(VCO3_AMP_2, 0, MIXER_FINAL, 3);
AudioConnection          patchCord39(FREQ_FILTER, 0, filter1, 1);
AudioConnection          patchCord40(filter1, 0, MIXER_FILTER, 0);
AudioConnection          patchCord41(filter1, 1, MIXER_FILTER, 1);
AudioConnection          patchCord42(filter1, 2, MIXER_FILTER, 2);
AudioConnection          patchCord43(MIXER_FILTER, AMP_POST_FILTER);
AudioConnection          patchCord44(AMP_POST_FILTER, ENVELOPE);
AudioConnection          patchCord45(AMP_POST_FILTER, 0, MIXER_FINAL, 1);
AudioConnection          patchCord46(ENVELOPE, AMP_ENVELOPE);
AudioConnection          patchCord47(AMP_ENVELOPE, 0, MIXER_FINAL, 0);
AudioConnection          patchCord48(MIXER_FINAL, AMP_FINAL);
AudioConnection          patchCord49(AMP_FINAL, 0, i2s1, 0);
AudioConnection          patchCord50(AMP_FINAL, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=116,47
// GUItool: end automatically generated code




#define ENUM_VCO1_SIN_AMP      0.25
#define ENUM_VCO1_SAW_AMP      0.25
#define ENUM_VCO1_SQUARE_AMP   0.25
#define ENUM_VCO1_TRIANGLE_AMP 0.25

#define ENUM_VCO2_SIN_AMP      0.25
#define ENUM_VCO2_SAW_AMP      0.25
#define ENUM_VCO2_SQUARE_AMP   0.25
#define ENUM_VCO2_TRIANGLE_AMP 0.25

#define ENUM_VCO3_SIN_AMP      0.25
#define ENUM_VCO3_SAW_AMP      0.25
#define ENUM_VCO3_SQUARE_AMP   0.25
#define ENUM_VCO3_TRIANGLE_AMP 0.25

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

double vco1_amp  = 0.0;
double vco2_amp  = 0.0;
double vco3_amp  = 0.0;
double noise_amp = 0.0;

double vco3_amp_2 = 0.0;

#define ENUM_VCO1_ID  0
#define ENUM_VCO2_ID  1
#define ENUM_VCO3_ID  2
#define ENUM_NOSIE_ID 3

double amp_pre_filter =   1.0;
double filter_freq    = 440.0;
double filter_q       =   0.707;

double mixer_filter_low_pass  = 0.0;
double mixer_filter_band_pass = 0.0;
double mixer_filter_high_pass = 0.0;
double mixer_filter_vco3      = 0.0;

#define ENUM_MIXER_ID_LOW_PASS  0
#define ENUM_MIXER_ID_BAND_PASS 1
#define ENUM_MIXER_ID_HIGH_PASS 2
#define ENUM_MIXER_ID_LFO3      3

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
double mixer_final_no_envelope = 0.0;
double mixer_final_no_filter   = 0.0;
double mixer_final_vco3        = 0.0;

double amp_final = 1.0;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(1300);

}

void loop() {
  // put your main code here, to run repeatedly:

}
