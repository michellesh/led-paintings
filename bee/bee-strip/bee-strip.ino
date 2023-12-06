#include <FastLED.h>

#include "colors.h"

#define LED_PIN 13
#define NUM_LEDS 31
#define BRIGHTNESS_MAX 100

#include "Palette.h"
Palette palette;

CRGB leds[NUM_LEDS];
uint8_t brightness[NUM_LEDS];
uint8_t x[] = {0, 0, 0, 0, 0, 0,
                  5, 15, 25, 35, 45, 55, 65, 75, 85, 95,
                  100, 100, 100, 100, 100, 100,
                  90, 80, 70, 60, 50, 40, 30, 20, 10};
uint8_t xMax = 100;

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
    CRGB color = palette.mapToColor(x[i], 0, xMax);
    leds[i] = color.nscale8(brightness[i]);
  }

  FastLED.setBrightness(BRIGHTNESS_MAX);
  FastLED.show();
}
