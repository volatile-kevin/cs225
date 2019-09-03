#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cstdlib>
#include <string>
#include <cmath>

// function to rotate
void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  // find midpoint line vertical and horizontal
  // reflect across both line
  // off by one error with midpoint average?
  cs225::PNG png;
  png.readFromFile(inputFile);

  int height = png.height();
  int halfHeight = png.height()/2;
  int width = png.width();

  if(height%2 != 0) {
    for(int x = 0; x < width/2; x++) {
      int newX = width - x - 1;
      cs225::HSLAPixel & pixelFrom = png.getPixel(x, halfHeight);
      cs225::HSLAPixel & pixelTo = png.getPixel(newX, halfHeight);
      double h = pixelFrom.h;
      double s = pixelFrom.s;
      double l = pixelFrom.l;
      double a = pixelFrom.a;
      pixelFrom.h = pixelTo.h;
      pixelFrom.s = pixelTo.s;
      pixelFrom.l = pixelTo.l;
      pixelFrom.a = pixelTo.a;
      pixelTo.h = h;
      pixelTo.s = s;
      pixelTo.l = l;
      pixelTo.a = a;

    }
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < halfHeight; y++) {
      int newX = width - x - 1;
      int newY = height - y - 1;
      cs225::HSLAPixel & pixelFrom = png.getPixel(x, y);
      cs225::HSLAPixel & pixelTo = png.getPixel(newX, newY);
          double h = pixelFrom.h;
          double s = pixelFrom.s;
          double l = pixelFrom.l;
          double a = pixelFrom.a;
          pixelFrom.h = pixelTo.h;
          pixelFrom.s = pixelTo.s;
          pixelFrom.l = pixelTo.l;
          pixelFrom.a = pixelTo.a;
          pixelTo.h = h;
          pixelTo.s = s;
          pixelTo.l = l;
          pixelTo.a = a;
    }

  }
  // for (int x = 0; x < width; x++) {
  //   for (int y = 0; y < height/2; y++) {
  //     cs225::HSLAPixel & pixelFrom = png.getPixel(x, y);
  //     int vertDist = (height/2) - y;
  //     int tempY = y + 2*vertDist - 1;
  //     cs225::HSLAPixel & pixelTo = png.getPixel(x, tempY);
  //     double h = pixelFrom.h;
  //     double s = pixelFrom.s;
  //     double l = pixelFrom.l;
  //     double a = pixelFrom.a;
  //     pixelFrom.h = pixelTo.h;
  //     pixelFrom.s = pixelTo.s;
  //     pixelFrom.l = pixelTo.l;
  //     pixelFrom.a = pixelTo.a;
  //     pixelTo.h = h;
  //     pixelTo.s = s;
  //     pixelTo.l = l;
  //     pixelTo.a = a;
  //   }
  // }
  //
  // for (int x = 0; x < width/2; x++) {
  //   for (int y = 0; y < height; y++) {
  //     cs225::HSLAPixel & pixelFrom = png.getPixel(x, y);
  //     int horizDist = (width/2) - x;
  //     int tempX = x + 2*horizDist - 1;
  //     cs225::HSLAPixel & pixelTo = png.getPixel(tempX, y);
  //     double h = pixelFrom.h;
  //     double s = pixelFrom.s;
  //     double l = pixelFrom.l;
  //     double a = pixelFrom.a;
  //     pixelFrom.h = pixelTo.h;
  //     pixelFrom.s = pixelTo.s;
  //     pixelFrom.l = pixelTo.l;
  //     pixelFrom.a = pixelTo.a;
  //     pixelTo.h = h;
  //     pixelTo.s = s;
  //     pixelTo.l = l;
  //     pixelTo.a = a;
  //   }
  // }

      png.writeToFile(outputFile);
      return;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = rand() % 360;
      pixel.s = 0.75;
      pixel.l = 0.5;
      pixel.a = 0.5;

    }

  }

  return png;
}
