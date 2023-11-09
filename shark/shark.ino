#include "mickymath.h"
#include <FastLED.h>

#define DATA_PIN 13
#define LED_TYPE NEOPIXEL
#define NUM_LEDS 53
#define BRIGHTNESS 255

#define TWINKLE_SPEED 3
#define TWINKLE_DENSITY 4
#define MIN_BRIGHTNESS 90

CRGB leds[NUM_LEDS];
CRGB colors[NUM_LEDS];
uint8_t brightness[NUM_LEDS];

/* clang-format off */
float x[] = {15.6, 18.6, 24.4, 34.1, 41.4, 46.2, 49.2, 56.9, 63.8, 69.0,
             68.6, 58.7, 50.5, 50.6, 49.8, 46.7, 42.7, 40.0, 40.6, 33.2,
             27.0, 24.2, 23.3, 24.1, 27.0, 31.6, 38.9, 30.2, 23.3, 18.2,
             15.3, 14.4, 15.3, 16.7, 13.0, 19.4, 21.5, 20.6, 18.9, 16.4,
             11.6,  3.4,  0.0,  4.5,  9.9, 14.8, 33.2, 34.7, 35.2, 34.4,
             32.3, 29.6, 26.0};

float y[] = { 15.8,   6.7,   0.0,   0.8,   7.2,  14.6,  22.3,  27.9,  34.2,  41.1,
              49.9,  49.0,  32.1,  40.1,  48.2,  57.8,  66.3,  75.4,  84.3,  88.2,
              96.2, 104.4, 113.2, 122.3, 130.4, 139.2, 150.2, 145.8, 137.3, 128.6,
             118.3, 107.7,  96.8,  85.8,  77.0,  71.0,  61.4,  52.1,  44.4,  36.3,
              53.5,  55.4,  47.2,  39.4,  32.6,  25.7,  25.5,  35.2,  45.1,  55.1,
              63.2,  71.0,  79.7};
/* clang-format on */

float xMax = 69.0;
float yMax = 150.2;

struct Cell {
  float x0;
  float y0;
  float r;
  float angle;
  float x;
  float y;

  void update() {
    x = pointXOnCircumference(r, x0, y0, angle);
    y = pointYOnCircumference(r, x0, y0, angle);
    angle += 16;
    if (angle > 360) {
      angle -= 360;
    }
  }
};

#define RADIUS 4
#define ROWS 20
#define COLS 10
#define WIDTH COLS *RADIUS * 2
#define HEIGHT ROWS *RADIUS * 2

Cell grid[ROWS][COLS];

void setup() {
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  setupWave();
}

void loop() {
  FastLED.clear();
  fade();

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

  updateWave();
  setWaveBrightness();

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

void setupWave() {
  int rowSize = HEIGHT / ROWS;
  int colSize = WIDTH / COLS;
  int loc = 100;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      Cell c = {colSize / 2 + i * colSize, rowSize / 2 + j * rowSize,
                rowSize / 2, i * loc + j * loc};
      grid[i][j] = c;
    }
  }
}

void updateWave() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j].update();
      for (int k = 0; k < NUM_LEDS; k++) {
        float xCell = grid[i][j].x0 + grid[i][j].x;
        float yCell = grid[i][j].y0 + grid[i][j].y;
        float dist = distance(x[k], y[k], xCell, yCell);
        if (dist < RADIUS * 2) {
          uint8_t b = mapf(dist, 0, RADIUS * 2, 255, MIN_BRIGHTNESS);
          if (b > brightness[k]) {
            brightness[k] = b;
          }
        }
      }
    }
  }
}

void fade() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    brightness[i] = max(MIN_BRIGHTNESS, brightness[i] / 2);
  }
}

void setWaveBrightness() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(brightness[i]);
  }
}
