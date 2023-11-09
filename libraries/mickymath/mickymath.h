float mapf(float value, float inMin, float inMax, float outMin, float outMax) {
  float percentage = (value - inMin) / (inMax - inMin);
  return outMin + (outMax - outMin) * percentage;
}

float distance(float x1, float y1, float x2, float y2) {
  return (float)sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

uint8_t attackDecayWave8(uint8_t i) {
  if (i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i / 2));
  }
}

float pointXOnCircumference(float radius, float originX, float originY,
                            float d) {
  float degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  float rads = degs * PI / 180;
  return originX + radius * cos(rads);
}

float pointYOnCircumference(float radius, float originX, float originY,
                            float d) {
  float degs = (d - 90 < 0) ? (d + 270) : (d - 90);
  float rads = degs * PI / 180;
  return originY + radius * sin(rads);
}
