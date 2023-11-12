/*
PImage img;

int mmWidth = 160;
int mmHeight = 160;
float drillBitDiameter = 1.0;
float padding = 0.75;

int mmStep = ceil(drillBitDiameter + padding);

int cols = mmWidth / mmStep;

int imgWidth = 800;
int imgHeight = 508;

int imgStep = imgWidth / cols;
int scale = imgStep / mmStep;

void settings() { size(imgWidth, imgHeight); }

void setup() {
  img = loadImage("bee-image-bw.jpg");
  colorMode(HSB, 255);
  noLoop();
}

void draw() {
  String csvString = "";
  int numDots = 0;
  img.loadPixels();
  for (int x = 0; x < width; x += imgStep) {
    for (int y = 0; y < height; y += imgStep) {
      int loc = x + y * width;
      float b = brightness(img.pixels[loc]);
      if (b < 200) {
        float radius = drillBitDiameter * scale;
        fill(0);
        ellipse(x, y, radius, radius);
        numDots++;
        csvString += x + "," + y + "\n";
      }
    }
  }

  String[] csvList = split(csvString, '\n');
  saveStrings("bee-vertices.csv", csvList);
}
*/

PImage img;

void setup() {
  size(800, 508);
  img = loadImage("bee-image-bw.jpg");
  colorMode(HSB, 255);
}

void draw() {
  img.loadPixels();
  for (int x = 0; x < width; x+=4) {
    for (int y = 0; y < height; y+=4) {
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
