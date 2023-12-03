#include <FastLED.h>

#include "colors.h"
#include "LEDGrid.h"

#define LED_PIN 13
#define BRIGHTNESS_MAX 100
#define WIDTH 16
#define HEIGHT 10
#define NUM_LEDS (WIDTH * HEIGHT)
#define START_PIXEL LEDGrid::TOP_LEFT

#include "Palette.h"
Palette palette;

LEDGrid leds(WIDTH, HEIGHT, START_PIXEL);
uint8_t brightness[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds[0], NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_MAX);
}

void loop() {
  FastLED.clear();
  palette.cycle();

  setTwinkles();

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      CRGB color = palette.mapToColor(x, 0, WIDTH);
      leds(x, y) = color.nscale8(brightness[y * WIDTH + x]);
    }
  }

  FastLED.setBrightness(BRIGHTNESS_MAX);
  FastLED.show();
}
