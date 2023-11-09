#include <FastLED.h>

#define DATA_PIN 13
#define LED_TYPE NEOPIXEL
#define NUM_LEDS 53
#define BRIGHTNESS 255

#define TWINKLE_SPEED 3
#define TWINKLE_DENSITY 4
#define MIN_BRIGHTNESS 30

CRGB leds[NUM_LEDS];
CRGB colors[NUM_LEDS];
uint8_t brightness[NUM_LEDS];

/* clang-format off */
//uint8_t x[] = {73, 77, 79, 79, 77, 76, 76, 78, 59, 56,
//               56, 58, 60, 62, 64, 65, 62, 57, 52, 47,
//               41, 34, 29, 20, 26, 33, 39, 46, 55, 64,
//               74, 69, 63, 55, 44, 32, 23, 15, 10,  8,
//               9,  14, 21, 29, 19, 19, 24, 27, 32, 60};
//
//uint8_t y[] = { 41,  51,  62,  78, 85, 95, 106, 117, 153, 143,
//               132, 121, 112, 102, 92, 81,  71,  62,  54,  90,
//                84,  78,  71,  67, 60, 55,  49,  45,  39,  35,
//                32,  23,  16,  11,  8,  9,  13,  18,  28,  38,
//                49,  58,  52,  45, 42, 31,  24,  35,  39,  26};
/* clang-format on */

// uint8_t xMin = 8;
// uint8_t xMax = 79;
//
// uint8_t yMin = 8;
// uint8_t yMax = 153;

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FastLED.clear();

  // Pivot index
  int top = 2;
  int right1 = 10; // top right
  int right2 = 21; // bottom right
  int left1 = 41;  // top left
  int left2 = 31;  // bottom right
  int bottom = 26;

  // Pivot colors - main colors fill gradient between
  CRGB white = CRGB(203, 234, 226); // White
  CRGB blue = CRGB(14, 50, 255);    // Blue
  CRGB teal = CRGB(43, 255, 100);   // Teal
  CRGB shark = CRGB(202, 218, 176); // Tan-ish shark color

  // Right side
  colors[top] = white;
  colors[right1] = blue;
  colors[right2] = teal;
  colors[bottom] = shark;
  fillGradientBetween(top, right1);
  fillGradientBetween(right1, right2);
  fillGradientBetween(right2, bottom);

  // Left side
  colors[left1] = blue;
  colors[left2] = teal;
  fillGradientBetween(left2, left1);
  fillGradientBetween(bottom, left2);

  // Fill in last segment manually because it wraps over index zero
  colors[42] = colors[9];
  colors[43] = colors[8];
  colors[44] = colors[7];
  colors[45] = colors[6];
  colors[0] = colors[4];
  colors[1] = colors[3];

  // Back fin
  colors[52] = CRGB(0, 0, 80);
  colors[46] = CRGB(0, 0, 10);
  fillGradientBetween(46, 52);

  // computeTwinkles();
  // setTwinkles();

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colors[i];
  }

  // Manually add some blending to certain pixels
  leds[left2] = blend(leds[left2], leds[left2 + 1], 200);
  leds[right2] = blend(leds[right2], leds[right2 - 1], 200);
  leds[top + 1] = blend(leds[top], leds[top + 1], 127);
  leds[top - 1] = blend(leds[top], leds[top - 1], 127);
  leds[top + 2] = blend(leds[top + 1], leds[top + 2], 5);
  leds[top - 2] = blend(leds[top - 1], leds[top - 2], 5);

  FastLED.show();
}

void fillGradientBetween(int i, int j) {
  CRGB diff =
      CRGB(abs(colors[i].r - colors[j].r), abs(colors[i].g - colors[j].g),
           abs(colors[i].b - colors[j].b));
  CRGB mi = CRGB(min(colors[i].r, colors[j].r), min(colors[i].g, colors[j].g),
                 min(colors[i].b, colors[j].b));
  int count = abs(j - i);
  for (int k = i + 1; k < j; k++) {
    colors[k].r = constrain(mi.r + (diff.r / count), 0, 255);
    colors[k].g = constrain(mi.g + (diff.g / count), 0, 255);
    colors[k].b = constrain(mi.b + (diff.b / count), 0, 255);
  }
}

uint8_t attackDecayWave8(uint8_t i) {
  if (i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i / 2));
  }
}

uint8_t getBrightness(uint32_t ms, uint8_t salt) {
  uint16_t ticks = ms >> (8 - TWINKLE_SPEED);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8(slowcycle16);
  slowcycle16 = (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

  return ((slowcycle8 & 0x0E) / 2) < TWINKLE_DENSITY
             ? attackDecayWave8(fastcycle8)
             : 0;
}

void computeTwinkles() {
  uint16_t PRNG16 = 11337;
  uint32_t clock32 = millis();

  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    // Use pseudo random number generator to get values for the clock speed
    // adjustment and clock offset of this pixel
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    uint16_t myclockoffset16 = PRNG16; // use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    // use that number as clock speed adjustment factor (in 8ths, from
    // 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 =
        ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 =
        (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

    // We now have the adjusted 'clock' for this pixel, now we call
    // the function that computes what color the pixel should be based
    // on the "brightness = f( time )" idea.
    brightness[i] = getBrightness(myclock30, myunique8);
  }
}

void setTwinkles() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = colors[i].nscale8(max((uint8_t)MIN_BRIGHTNESS, brightness[i]));
  }
}
