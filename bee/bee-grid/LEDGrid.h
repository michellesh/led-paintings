class LEDGrid {

private:
  int _width;                    // number of pixels across
  int _height;                   // number of pixels high
  int _startPixel = BOTTOM_LEFT; // the first pixel on the subgrid, either
                                 // BOTTOM_LEFT or TOP_LEFT
  CRGB *_leds;                   // pointer to the LED array

  int _xyCoordsToIndex(int x, int y) {
    // convert x, y coordinates to an index on the one-dimensional array that
    // snakes back and forth on the grid

    // For odd rows, flip the x value horizontally
    if (y % 2 == 1) {
      x = _flipHorizontal(x);
    }

    // If the start pixel is at the top, flip the y value vertically
    if (_startPixel == TOP_LEFT) {
      y = _flipVertical(y);
    }

    return y * _width + x;
  }

  // Given a column, returns the opposite column horizontally
  int _flipHorizontal(int x) { return _width - x - 1; }

  // Given a row, returns the opposite row vertically
  int _flipVertical(int y) { return _height - y - 1; }

public:
  static constexpr int BOTTOM_LEFT = 0;
  static constexpr int TOP_LEFT = 1;

  // Class constructor. Sets the width, height, and start pixel. Also allocates
  // the number of bytes in the LED array that the `_leds` pointer points to.
  LEDGrid(int width, int height, int startPixel) {
    _width = width;
    _height = height;
    _startPixel = startPixel;
    _leds = new CRGB[_width * _height];
  }

  // Define the [] operator. Lets us reference the LEDGrid instance with the
  // syntax `leds[i]`, like in the `setup()` function when we need to tell
  // FastLED our LED array variable.
  struct CRGB *operator[](int i) {
    return (&_leds[i]);
  }

  // Define () operator. Lets us reference the LEDGrid instance with the syntax
  // `leds(x, y)`. Calls `xyCoordsToIndex` to convert x, y coordinates to an
  // index
  struct CRGB &operator()(int x, int y) {
    return _leds[_xyCoordsToIndex(x, y)];
  }
};
