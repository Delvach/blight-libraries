#ifndef BikeEffectsData_h
#define BikeEffectsData_h

// #include "RF24.h"

/*
   Define data to be received; struct must be replicated in any code that sends this
*/
struct BikeEffectsData {
  byte version = 0;
  short int hue = 0;
  byte pos = 50;
  byte on = 0;
  byte mode = 1;
  byte brightness = 50;
  byte percent = 20;

  byte right[7];  // 7 Channels of 0-255
  byte left[7];   // 7 Channels of 0-255
};




#endif

