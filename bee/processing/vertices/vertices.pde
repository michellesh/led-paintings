PImage img;

int[] bRange = {180, 240};

void setup() {
  size(800, 508);
  img = loadImage("/Users/michelle/dev/led-paintings/bee/bee-image-bw-blur.jpg");
  colorMode(HSB, 255);
}

void draw() {
  background(img);

  String csvString = "";
  img.loadPixels();
  for (int x = 0; x < width; x += 4) {
    for (int y = 0; y < height; y += 4) {
      int loc = x + y * width;
      float b = brightness(img.pixels[loc]);
      if (b > bRange[0] && b < bRange[1]) {
        float radius = 0.5;
        fill(0);
        ellipse(x, y, radius, radius);
        csvString += x + "," + y + "\n";
      }
    }
  }

  String[] csvList = split(csvString, '\n');
  saveStrings("vertices.csv", csvList);
}
