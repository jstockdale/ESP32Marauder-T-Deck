#include "Trackball.h"
#include <Wire.h>

extern bool trackball_interrupted;
extern int trackball_up_count;
extern int trackball_down_count;
extern int trackball_left_count;
extern int trackball_right_count;

extern void IRAM_ATTR ISR_up();
extern void IRAM_ATTR ISR_down();
extern void IRAM_ATTR ISR_left();
extern void IRAM_ATTR ISR_right();

extern void IRAM_ATTR ISR_rst();

Trackball::Trackball() {
  trackball_interrupted = false;
  trackball_up_count = 0;
  trackball_down_count = 0;
  trackball_left_count = 0;
  trackball_right_count = 0;
}

bool Trackball::menuPress(int button){
  // 0 - Up
  // 1 - Down
  // 2 - Left
  // 3 - Right
  // 4 - Any
  if (trackball_interrupted)
  {
    uint8_t xx=1;
    uint8_t yy=1;
    xx += trackball_left_count;
    xx -= trackball_right_count;
    yy -= trackball_up_count;
    yy += trackball_down_count;
    if(xx==1 && yy==1) {
      ISR_rst();
      return false;
    } else if(button==4) return true; // any btn
    delay(50);
    // Print "button - xx - yy",  1 is normal value for xx and yy 0 and 2 means movement on the axis
    //Serial.print(button); Serial.print("-"); Serial.print(xx); Serial.print("-"); Serial.println(yy);
    if (xx < 1 && button==2)       { ISR_rst();   return true;  } // left
    else if (xx > 1 && button==3)  { ISR_rst();   return true;  } // right
    else if (yy < 1 && button==0)  { ISR_rst();   return true;  } // up
    else if (yy > 1 && button==1)  { ISR_rst();   return true;  } // down
    else return false;
  }
  else return false;

}
