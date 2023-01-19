#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       VCO1_SQUARE;      //xy=251.6667022705078,229.99995613098145
AudioSynthWaveform       VCO1_TRIANGLE;      //xy=251.66665649414062,290.0000247955322
AudioSynthWaveform       VCO3_SQUARE; //xy=258,728
AudioSynthWaveform       VCO3_TRIANGLE; //xy=258,789
AudioSynthWaveform       VCO2_SQUARE;    //xy=264,464
AudioSynthWaveform       VCO2_TRIANGLE;  //xy=264,525
AudioSynthWaveform       VCO1_SINE;      //xy=266.6666717529297,118.33334922790527
AudioSynthWaveform       VCO1_SAW;      //xy=266.6666717529297,171.6666669845581
AudioSynthWaveform       VCO3_SINE; //xy=273,617
AudioSynthWaveform       VCO3_SAW; //xy=273,670
AudioSynthWaveform       VCO2_SINE;      //xy=279,353
AudioSynthWaveform       VCO2_SAW;       //xy=279,406
AudioSynthNoiseWhite     NOISE;         //xy=290,864
AudioMixer4              VCO1_MIX;       //xy=540,219
AudioMixer4              VCO3_MIX; //xy=547,718
AudioMixer4              VCO2_MIX; //xy=553,454
AudioAmplifier           VCO1_AMP;       //xy=710,217
AudioAmplifier           VCO3_AMP; //xy=717,716
AudioAmplifier           VCO2_AMP; //xy=723,452
AudioAmplifier           NOISE_AMP; //xy=727,855
AudioMixer4              VCO_MIX_FINAL; //xy=967,464
AudioEffectEnvelope      ENVELOPE;      //xy=1151,464
AudioAmplifier           FINAL_AMP; //xy=1324,465
AudioOutputI2S           i2s1;           //xy=1484.333251953125,463.66668701171875
AudioConnection          patchCord1(VCO1_SQUARE, 0, VCO1_MIX, 2);
AudioConnection          patchCord2(VCO1_TRIANGLE, 0, VCO1_MIX, 3);
AudioConnection          patchCord3(VCO3_SQUARE, 0, VCO3_MIX, 2);
AudioConnection          patchCord4(VCO3_TRIANGLE, 0, VCO3_MIX, 3);
AudioConnection          patchCord5(VCO2_SQUARE, 0, VCO2_MIX, 2);
AudioConnection          patchCord6(VCO2_TRIANGLE, 0, VCO2_MIX, 3);
AudioConnection          patchCord7(VCO1_SINE, 0, VCO1_MIX, 0);
AudioConnection          patchCord8(VCO1_SAW, 0, VCO1_MIX, 1);
AudioConnection          patchCord9(VCO3_SINE, 0, VCO3_MIX, 0);
AudioConnection          patchCord10(VCO3_SAW, 0, VCO3_MIX, 1);
AudioConnection          patchCord11(VCO2_SINE, 0, VCO2_MIX, 0);
AudioConnection          patchCord12(VCO2_SAW, 0, VCO2_MIX, 1);
AudioConnection          patchCord13(NOISE, NOISE_AMP);
AudioConnection          patchCord14(VCO1_MIX, VCO1_AMP);
AudioConnection          patchCord15(VCO3_MIX, VCO3_AMP);
AudioConnection          patchCord16(VCO2_MIX, VCO2_AMP);
AudioConnection          patchCord17(VCO1_AMP, 0, VCO_MIX_FINAL, 0);
AudioConnection          patchCord18(VCO3_AMP, 0, VCO_MIX_FINAL, 2);
AudioConnection          patchCord19(VCO2_AMP, 0, VCO_MIX_FINAL, 1);
AudioConnection          patchCord20(NOISE_AMP, 0, VCO_MIX_FINAL, 3);
AudioConnection          patchCord21(VCO_MIX_FINAL, ENVELOPE);
AudioConnection          patchCord22(ENVELOPE, FINAL_AMP);
AudioConnection          patchCord23(FINAL_AMP, 0, i2s1, 0);
AudioConnection          patchCord24(FINAL_AMP, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=81,42
// GUItool: end automatically generated code


#define NUM_AUDIO     12
#define NUM_VOICES    4
#define NUM_VCO       3
    
#define ENUM_VCO1         0
#define ENUM_VCO2         1
#define ENUM_VCO3         2
#define ENUM_VCO_NOISE    3
#define ENUM_VCO_FINAL    4
#define ENUM_VCO_COUNT    4

#define ENUM_SINE     0
#define ENUM_TRIANGLE 1
#define ENUM_SQUARE   2
#define ENUM_SAW      3


#define VOLUME_PIN    15

AudioSynthWaveform* audio_vco[NUM_VCO][NUM_VOICES];


class SynthVco
{
  public:
    SynthVco();

    void setup();
    void setupAudio();
    void setupVcoVoice(int vco);
    void setFreq(double hz);
    void setFreq(int vco, int type, double hz);
    void setVolume(int vco, int type, double vol);
    void setVolume(int type, double vol);
    void setVolume(double vol);
    void setAudioVectors();
    void noteOn();
    void noteOff();
    double getVolumeKnob();
    
  private:
    int tmp = 0;
};
