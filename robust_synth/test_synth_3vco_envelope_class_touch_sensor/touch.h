#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

#define TOUCH_NONE    0
#define TOUCH_START   1
#define TOUCH_STOP    2
#define TOUCH_HOLD    3

class Touch
{
  public:
    Touch();
    int setup();
    int getTouch();
    int debug();

  private:
    Adafruit_MPR121 cap = Adafruit_MPR121();
    // Keeps track of the last pins touched
    
    // so we know when buttons are 'released'
    uint16_t lasttouched = 0;
    uint16_t currtouched = 0;
    int touch_state = 0;
};

Touch::Touch()
{
  return;
}

int Touch::setup()
{
  if (!cap.begin(0x5A)) {
    /* no device found */
    return 1;
  }
  return 0;
}

int Touch::debug()
{
    // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}

int Touch::getTouch()
{
  int ret = 0;
  int ret_touched = 0;
  int ret_release = 0;
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
//      Serial.print(i); Serial.println(" touched");
      ret_touched++;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
//      Serial.print(i); Serial.println(" released");
      ret_release++;
    }
  }

  //Serial.println(currtouched);
  if      ( ( currtouched > 0  ) & ( lasttouched >  0 ) ) ret = TOUCH_HOLD;
  else if ( ( currtouched == 0 ) & ( lasttouched == 0 ) ) ret = TOUCH_NONE;
  else if ( currtouched >  0                            ) ret = TOUCH_START;
  else if ( currtouched == 0                            ) ret = TOUCH_STOP;

  // reset our state
  lasttouched = currtouched;

  return ret;
}
