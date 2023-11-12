PImage img;

void setup() {
  size(800, 508);
  img = loadImage("/Users/michelle/dev/led-paintings/bee/bee-image-bw.jpg");
  colorMode(HSB, 255);
}

void draw() {
  img.loadPixels();
  for (int x = 0; x < width; x += 4) {
    for (int y = 0; y < height; y += 4) {
      int loc = x + y * width;
      float b = brightness(img.pixels[loc]);
      if (b < 100) {
        float radius = 2;
        fill(0);
        ellipse(x, y, radius, radius);
      }
    }
  }
}
