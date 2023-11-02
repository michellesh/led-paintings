#include <FastLED.h>

#define DATA_PIN 13
#define LED_TYPE NEOPIXEL
#define NUM_LEDS 50
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

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

  leds[0] = CRGB(100, 33, 152);
  leds[1] = CRGB(101, 39, 142);
  leds[2] = CRGB(102, 45, 133);
  leds[3] = CRGB(103, 50, 124);
  leds[4] = CRGB(106, 62, 162);
  leds[5] = CRGB(108, 74, 199);
  leds[6] = CRGB(85, 88, 180);
  leds[7] = CRGB(62, 101, 161);
  leds[8] = CRGB(78, 132, 34);
  leds[9] = CRGB(87, 136, 49);
  leds[10] = CRGB(80, 200, 30);
  leds[11] = CRGB(66, 198, 32);
  leds[12] = CRGB(51, 196, 34);
  leds[13] = CRGB(36, 194, 36);
  leds[14] = CRGB(42, 198, 67);
  leds[15] = CRGB(49, 203, 99);
  leds[16] = CRGB(47, 168, 139);
  leds[17] = CRGB(45, 134, 179);
  leds[18] = CRGB(44, 100, 219);
  leds[19] = CRGB(6, 144, 72);
  leds[20] = CRGB(13, 127, 87);
  leds[21] = CRGB(20, 111, 102);
  leds[22] = CRGB(26, 95, 116);
  leds[23] = CRGB(12, 16, 240);
  leds[24] = CRGB(16, 56, 131);
  leds[25] = CRGB(20, 56, 185);
  leds[26] = CRGB(33, 52, 185);
  leds[27] = CRGB(47, 48, 185);
  leds[28] = CRGB(63, 35, 185);
  leds[29] = CRGB(47, 12, 130);
  leds[30] = CRGB(100, 31, 185);
  leds[31] = CRGB(116, 64, 176);
  leds[32] = CRGB(132, 97, 166);
  leds[33] = CRGB(147, 130, 156);
  leds[34] = CRGB(116, 113, 133);
  leds[35] = CRGB(85, 95, 111);
  leds[36] = CRGB(55, 77, 89);
  leds[37] = CRGB(47, 79, 104);
  leds[38] = CRGB(40, 82, 119);
  leds[39] = CRGB(33, 84, 135);
  leds[40] = CRGB(32, 54, 106);
  leds[41] = CRGB(22, 32, 185);
  leds[42] = CRGB(21, 21, 110);
  leds[43] = CRGB(87, 59, 185);
  leds[44] = CRGB(81, 134, 166);
  leds[45] = CRGB(175, 198, 185);
  leds[46] = CRGB(120, 139, 185);
  leds[47] = CRGB(196, 191, 185);
  leds[48] = CRGB(127, 108, 185);
  leds[49] = CRGB(133, 95, 193);

  // for (int i = 0; i < NUM_LEDS; i++) {
  //   int hue = map(x[i], xMin, xMax, 0, 255);
  //   leds[i] = CHSV(hue, 255, BRIGHTNESS);
  // }

  FastLED.show();
}
