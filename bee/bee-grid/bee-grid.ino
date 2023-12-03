#include <FastLED.h>

#include "colors.h"

#define LED_PIN 13
#define NUM_LEDS 160
#define BRIGHTNESS_MAX 100

#include "Palette.h"
Palette palette;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_MAX);
}

void loop() {
  FastLED.clear();

  static int activePalette = 0;
  static int activePattern = 0;

  palette.cycle();

  twinkle();

  FastLED.setBrightness(BRIGHTNESS_MAX);
  FastLED.show();
}
