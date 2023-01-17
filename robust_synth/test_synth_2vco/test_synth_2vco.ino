#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       VCO1_SQUARE;      //xy=251.6667022705078,229.99995613098145
AudioSynthWaveform       VCO1_TRIANGLE;      //xy=251.66665649414062,290.0000247955322
AudioSynthWaveform       VCO2_SQUARE;    //xy=264,464
AudioSynthWaveform       VCO2_TRIANGLE;  //xy=264,525
AudioSynthWaveform       VCO1_SINE;      //xy=266.6666717529297,118.33334922790527
AudioSynthWaveform       VCO1_SAW;      //xy=266.6666717529297,171.6666669845581
AudioSynthWaveform       VCO2_SINE;      //xy=279,353
AudioSynthWaveform       VCO2_SAW;       //xy=279,406
AudioMixer4              VCO1_MIX;       //xy=540,219
AudioMixer4              VCO2_MIX; //xy=553,454
AudioAmplifier           VCO1_AMP;       //xy=710,217
AudioAmplifier           VCO2_AMP; //xy=723,452
AudioOutputI2S           i2s1;           //xy=905.3332824707031,220.6666955947876
AudioConnection          patchCord1(VCO1_SQUARE, 0, VCO1_MIX, 2);
AudioConnection          patchCord2(VCO1_TRIANGLE, 0, VCO1_MIX, 3);
AudioConnection          patchCord3(VCO2_SQUARE, 0, VCO2_MIX, 2);
AudioConnection          patchCord4(VCO2_TRIANGLE, 0, VCO2_MIX, 3);
AudioConnection          patchCord5(VCO1_SINE, 0, VCO1_MIX, 0);
AudioConnection          patchCord6(VCO1_SAW, 0, VCO1_MIX, 1);
AudioConnection          patchCord7(VCO2_SINE, 0, VCO2_MIX, 0);
AudioConnection          patchCord8(VCO2_SAW, 0, VCO2_MIX, 1);
AudioConnection          patchCord9(VCO1_MIX, VCO1_AMP);
AudioConnection          patchCord10(VCO2_MIX, VCO2_AMP);
AudioConnection          patchCord11(VCO1_AMP, 0, i2s1, 0);
AudioConnection          patchCord12(VCO2_AMP, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=81,42
// GUItool: end automatically generated code


#define VOLUME_PIN 15

void setVolume(double vol)
{
  if( vol < 0.0 ) vol = 0.0;
  SerialUSB.print("Volume: ");
  SerialUSB.println(vol);
  VCO1_SINE.amplitude(vol);
  VCO1_SAW.amplitude(vol);
  VCO1_SQUARE.amplitude(vol);
  VCO1_TRIANGLE.amplitude(vol);

  VCO2_SINE.amplitude(vol);
  VCO2_SAW.amplitude(vol);
  VCO2_SQUARE.amplitude(vol);
  VCO2_TRIANGLE.amplitude(vol);
}

void setFreq(double hz)
{
  if( hz > 10000.0 ) return;
  if( hz < 0.0     ) return;
  SerialUSB.print("Freq: ");
  SerialUSB.println(hz);
  double vco_1_freq = hz;
  VCO1_SINE.frequency(     vco_1_freq);
  VCO1_SAW.frequency(      vco_1_freq);
  VCO1_SQUARE.frequency(   vco_1_freq);
  VCO1_TRIANGLE.frequency( vco_1_freq);

  double vco_2_freq = hz * 1.1;

  VCO2_SINE.frequency(     vco_2_freq);
  VCO2_SAW.frequency(      vco_2_freq);
  VCO2_SQUARE.frequency(   vco_2_freq);
  VCO2_TRIANGLE.frequency( vco_2_freq);
}

void setup() {

  pinMode(VOLUME_PIN, INPUT);
  
  // put your setup code here, to run once:
  AudioMemory(300);
  sgtl5000_1.enable();
//  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.unmuteHeadphone();
  sgtl5000_1.volume(1.0);

  VCO1_SINE.begin(WAVEFORM_SINE);
  VCO1_SAW.begin(WAVEFORM_SAWTOOTH);
  VCO1_SQUARE.begin(WAVEFORM_SQUARE);
  VCO1_TRIANGLE.begin(WAVEFORM_TRIANGLE);

  VCO2_SINE.begin(WAVEFORM_SINE);
  VCO2_SAW.begin(WAVEFORM_SAWTOOTH);
  VCO2_SQUARE.begin(WAVEFORM_SQUARE);
  VCO2_TRIANGLE.begin(WAVEFORM_TRIANGLE);

  VCO1_AMP.gain(1.0);
  VCO2_AMP.gain(1.0);

  for( int i = 0; i < 4; i++ )
  {
    VCO1_MIX.gain(i,0.25);
    VCO2_MIX.gain(i,0.25);
  }

  SerialUSB.begin(115200);
}

double freq = 440.0;

void loop() {
  // put your main code here, to run repeatedly:

  int v = analogRead(VOLUME_PIN);
  double vol = (double)v / 1023.0;
  
  freq = 440.0;
  setFreq(freq);
  setVolume(vol);
  delay(200);

  freq = 880.0;
  setFreq(freq);
  setVolume(vol);
  delay(200);
}
