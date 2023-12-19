DEFINE_GRADIENT_PALETTE(_bluePalette){0,   0, 0, 255,
                                      255, 0, 0, 255};
CRGBPalette16 bluePalette = _bluePalette;

DEFINE_GRADIENT_PALETTE(_cyanPalette){0,   0, 100, 255,
                                      255, 0, 100, 255};
CRGBPalette16 cyanPalette = _cyanPalette;

DEFINE_GRADIENT_PALETTE(_greenPalette){0,   0, 255, 0,
                                       255, 0, 255, 0};
CRGBPalette16 greenPalette = _greenPalette;

DEFINE_GRADIENT_PALETTE(_redPalette){0,   255, 0, 0,
                                     255, 255, 0, 0};
CRGBPalette16 redPalette = _redPalette;

// clang-format off
CRGBPalette16* activePalettes[] = {
  &cyanPalette,
  &greenPalette,
  &redPalette
};
// clang-format on
