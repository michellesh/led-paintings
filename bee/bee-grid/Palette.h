#define MAX_PALETTE_INDEX 240
#define SECONDS_PER_PALETTE 20

class Palette {
private:
  CRGBPalette16 _currentPalette = *(activePalettes[0]);
  CRGBPalette16 _targetPalette = *(activePalettes[0]);

  void _setNextColorPalette() {
    const uint8_t numberOfPalettes =
        sizeof(activePalettes) / sizeof(activePalettes[0]);
    static uint8_t whichPalette = -1;
    whichPalette = addmod8(whichPalette, 1, numberOfPalettes);

    _targetPalette = *(activePalettes[whichPalette]);
  }

public:
  void cycle() {
    EVERY_N_SECONDS(SECONDS_PER_PALETTE) { _setNextColorPalette(); }

    EVERY_N_MILLISECONDS(10) {
      nblendPaletteTowardPalette(_currentPalette, _targetPalette, 12);
    }
  }

  CRGB mapToColor(int value, int fromLow, int fromHigh) {
    uint8_t paletteIndex = map(value, fromLow, fromHigh, 0, MAX_PALETTE_INDEX);
    return ColorFromPalette(_currentPalette, paletteIndex);
  }

  CRGB indexToColor(uint8_t i = 0) {
    uint8_t paletteIndex = map(i, 0, NUM_LEDS - 1, 0, MAX_PALETTE_INDEX);
    return ColorFromPalette(_currentPalette, paletteIndex);
  }
};
