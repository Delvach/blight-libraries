#ifndef BikeEffectsUtils_h
#define BikeEffectsUtils_h


unsigned long mode_sparkle_update_interval = 60;
unsigned long mode_sparkle_last_update = 0;


/*
	Define radio ID's
	 0 Main node broadcast ID
	 1 Control node or control-enabled effects node broadcast ID
*/
byte addresses[][6] = {"1Mast", "2Left", "3Rght"};

int isMatrixLight = 0;

// Maximum brightness to display on neopixels
int max_brightness = 100;

byte data_received_active = 0;
unsigned long data_last_received = 0;
unsigned long data_timeout = 500;

unsigned long data_reception_last_check = 0;
unsigned long data_reception_check_interval = 500;

// Replicating .Color() method from Neopixel library
uint32_t rgbToColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Replicating .Color() method from Neopixel matrix library
uint16_t rgbToColor(uint8_t r, uint8_t g, uint8_t b, uint8_t isMatrix) {
  return ((uint16_t)(r & 0xF8) << 8) |
         ((uint16_t)(g & 0xFC) << 3) |
                    (b         >> 3);
}

void hsv2rgb(unsigned int hue, unsigned int sat, unsigned int val, \
             unsigned char * r, unsigned char * g, unsigned char * b, unsigned char maxBrightness ) {
  unsigned int H_accent = hue / 60;
  unsigned int bottom = ((255 - sat) * val) >> 8;
  unsigned int top = val;
  unsigned char rising  = ((top - bottom)  * (hue % 60   )  )  /  60  +  bottom;
  unsigned char falling = ((top - bottom)  * (60 - hue % 60)  )  /  60  +  bottom;

  switch (H_accent) {
    case 0:
      *r = top;
      *g = rising;
      *b = bottom;
      break;

    case 1:
      *r = falling;
      *g = top;
      *b = bottom;
      break;

    case 2:
      *r = bottom;
      *g = top;
      *b = rising;
      break;

    case 3:
      *r = bottom;
      *g = falling;
      *b = top;
      break;

    case 4:
      *r = rising;
      *g = bottom;
      *b = top;
      break;

    case 5:
      *r = top;
      *g = bottom;
      *b = falling;
      break;
  }
  // Scale values to maxBrightness
  *r = *r * maxBrightness / 255;
  *g = *g * maxBrightness / 255;
  *b = *b * maxBrightness / 255;
}



uint32_t getColorByBandAndVal(int band, int val) {
  unsigned char red, green, blue;
  int hue = map(band, 0, 6, 300, 0);
  int sat = 255;
  //  int maxBrightness = 100;

  hsv2rgb(hue, sat, val, &red, &green, &blue, max_brightness);
  return isMatrixLight ? rgbToColor(red, green, blue, 1) : rgbToColor(red, green, blue);
}


/*
   Get band-specific colors
*/
uint32_t getColorByBand(int band) {
  unsigned char red, green, blue;
  int val = 50;

  int ihue = map(band, 0, 13, 300, 0);
  //  int isat = map(strength, 0, 9, 0, 255); // ??

  // hue: 0-359, sat: 0-255, val (lightness): 0-255
  hsv2rgb(ihue, 255, 50, &red, &green, &blue, max_brightness);
  return isMatrixLight ? rgbToColor(red, green, blue, 1) : rgbToColor(red, green, blue);
}


void printSpaces(int num) {
  if (num < 100) {
    Serial.print("   ");
  } else if (num < 10) {
    Serial.print("  ");
  } else {
    Serial.print(" ");
  }
}

/*
   Serial output sound data
*/
void prettyPrintSoundData(byte sound[7], bool lineEnding) {
  for (int i = 0; i < 8; i++) {
    printSpaces(sound[i]);
    if (i == 7) {
      if (lineEnding) {

        Serial.println(sound[i]);
      } else {
        Serial.print(sound[i]); Serial.print("  --  ");
      }

    } else {
      Serial.print(sound[i]); Serial.print(',');
    }
  }
}


// Data has ben received
void toggleDataReceptionStatus(byte isTimeout) {
	data_received_active = !isTimeout;
}

void checkDataReceptionStatus() {
	toggleDataReceptionStatus(millis() >= (data_last_received + data_timeout));
}

void updateDataReceptionTimestamp() {
	data_last_received = millis();
}

byte isDataReceptionActive() {
	return data_received_active;
}



/*
  Get RGB light variable from HSV values
*/
uint32_t getColorByHue(int hue) {
  unsigned char red, green, blue;
  int sat = 255;
  int val = 50;

  hsv2rgb(hue, sat, val, &red, &green, &blue, max_brightness);

//  return lights.Color(red, green, blue);
  return isMatrixLight ? rgbToColor(red, green, blue, 1) : rgbToColor(red, green, blue);
}

/*
  Get RGB light variable from HSV values
*/
uint32_t getColorByHueAndVal(int hue, int val) {
  unsigned char red, green, blue;
  int sat = 255;

  hsv2rgb(hue, sat, val, &red, &green, &blue, max_brightness);

  return isMatrixLight ? rgbToColor(red, green, blue, 1) : rgbToColor(red, green, blue);
}

int getHueIndexByBand(int band, int hue) {
  int tempHue = map(band, 0, 13, hue, hue + 359);
  if (tempHue > 359) return tempHue - 359;
  return tempHue;
}

uint32_t getMatrixColorByBand(int band, int hue) {
  return getColorByHueAndVal(getHueIndexByBand(band, hue), 80);
}



#endif