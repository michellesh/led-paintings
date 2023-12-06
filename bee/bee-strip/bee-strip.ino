#include <FastLED.h>

#include "colors.h"

#define LED_PIN 13
#define NUM_LEDS 31
#define BRIGHTNESS_MAX 100

#include "Palette.h"
Palette palette;

CRGB leds[NUM_LEDS];
uint8_t brightness[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_MAX);
}

void loop() {
  FastLED.clear();
  palette.cycle();

  setTwinkles();

  for (int i = 0; i < NUM_LEDS; i++) {
    CRGB color = palette.mapToColor(i, 0, NUM_LEDS);
    leds[i] = color.nscale8(brightness[i]);
  }

  FastLED.setBrightness(BRIGHTNESS_MAX);
  FastLED.show();
}
