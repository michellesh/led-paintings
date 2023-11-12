#include <FastLED.h>

#define DATA_PIN 13
#define LED_TYPE NEOPIXEL
#define NUM_LEDS 50
#define BRIGHTNESS 255

#define TWINKLE_SPEED 3
#define TWINKLE_DENSITY 4
#define MIN_BRIGHTNESS 30

CRGB leds[NUM_LEDS];
CRGB colors[NUM_LEDS];
uint8_t brightness[NUM_LEDS];

/* clang-format off */
uint8_t x[] = {73, 77, 79, 79, 77, 76, 76, 78, 59, 56,
               56, 58, 60, 62, 64, 65, 62, 57, 52, 47,
               41, 34, 29, 20, 26, 33, 39, 46, 55, 64,
               74, 69, 63, 55, 44, 32, 23, 15, 10,  8,
               9,  14, 21, 29, 19, 19, 24, 27, 32, 60};

uint8_t y[] = { 41,  51,  62,  78, 85, 95, 106, 117, 153, 143,
               132, 121, 112, 102, 92, 81,  71,  62,  54,  90,
                84,  78,  71,  67, 60, 55,  49,  45,  39,  35,
                32,  23,  16,  11,  8,  9,  13,  18,  28,  38,
                49,  58,  52,  45, 42, 31,  24,  35,  39,  26};
/* clang-format on */

uint8_t xMin = 8;
uint8_t xMax = 79;

uint8_t yMin = 8;
uint8_t yMax = 153;

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FastLED.clear();

  colors[0] = CRGB(100, 33, 152);
  colors[1] = CRGB(91, 30, 130);
  colors[2] = CRGB(102, 45, 133);
  colors[3] = CRGB(103, 50, 124);
  colors[4] = CRGB(106, 62, 162);
  colors[5] = CRGB(108, 74, 199);
  colors[6] = CRGB(85, 88, 180);
  colors[7] = CRGB(62, 101, 161);
  colors[8] = CRGB(78, 132, 34);
  colors[9] = CRGB(87, 136, 49);
  colors[10] = CRGB(80, 200, 30);
  colors[11] = CRGB(66, 198, 32);
  colors[12] = CRGB(51, 196, 34);
  colors[13] = CRGB(36, 194, 36);
  colors[14] = CRGB(42, 198, 67);
  colors[15] = CRGB(49, 203, 99);
  colors[16] = CRGB(47, 168, 139);
  colors[17] = CRGB(45, 134, 179);
  colors[18] = CRGB(44, 100, 219);
  colors[19] = CRGB(6, 144, 72);
  colors[20] = CRGB(13, 127, 87);
  colors[21] = CRGB(20, 111, 102);
  colors[22] = CRGB(26, 95, 116);
  colors[23] = CRGB(12, 16, 240);
  colors[24] = CRGB(16, 56, 131);
  colors[25] = CRGB(20, 56, 185);
  colors[26] = CRGB(33, 52, 185);
  colors[27] = CRGB(47, 48, 185);
  colors[28] = CRGB(63, 35, 185);
  colors[29] = CRGB(47, 12, 130);
  colors[30] = CRGB(100, 31, 185);
  colors[31] = CRGB(116, 64, 176);
  colors[32] = CRGB(132, 97, 166);
  colors[33] = CRGB(147, 130, 156);
  colors[34] = CRGB(116, 113, 133);
  colors[35] = CRGB(85, 95, 111);
  colors[36] = CRGB(55, 77, 89);
  colors[37] = CRGB(47, 79, 104);
  colors[38] = CRGB(40, 82, 119);
  colors[39] = CRGB(33, 84, 135);
  colors[40] = CRGB(32, 54, 106);
  colors[41] = CRGB(12, 16, 240);
  colors[42] = CRGB(21, 21, 110);
  colors[43] = CRGB(87, 59, 185);
  colors[44] = CRGB(81, 134, 166);
  colors[45] = CRGB(175, 198, 185);
  colors[46] = CRGB(120, 139, 185);
  colors[47] = CRGB(196, 191, 185);
  colors[48] = CRGB(127, 108, 185);
  colors[49] = CRGB(133, 95, 193);

  // for (int i = 0; i < NUM_LEDS; i++) {
  //   int hue = map(x[i], xMin, xMax, 0, 255);
  //   leds[i] = CHSV(hue, 255, BRIGHTNESS);
  // }

  computeTwinkles();
  setTwinkles();

  FastLED.show();
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
