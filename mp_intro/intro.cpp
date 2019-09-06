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
  double MinRe = -2.0;
double MaxRe = 1.0;
double MinIm = -1.2;
double MaxIm = MinIm+(MaxRe-MinRe)*height/width;
double Re_factor = (MaxRe-MinRe)/(width-1);
double Im_factor = (MaxIm-MinIm)/(height-1);
unsigned MaxIterations = 100;

for(unsigned y=0; y<height; ++y)
{
    double c_im = MaxIm - y*Im_factor;
    for(unsigned x=0; x<width; ++x)
    {
        double c_re = MinRe + x*Re_factor;

        double Z_re = c_re, Z_im = c_im;
        bool isInside = true;

        for(unsigned n = 0; n<MaxIterations; ++n)
        {
            double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
            if(Z_re2 + Z_im2 > 4)
            {
                isInside = false;
                break;
            }
            Z_im = 2*Z_re*Z_im + c_im;
            Z_re = Z_re2 - Z_im2 + c_re;

        }

        if(isInside) {
          cs225::HSLAPixel & pixel = png.getPixel(x, y);
           pixel.h = 240;
           pixel.s = 1;
           pixel.l = .45;
           pixel.a = 1;
         }
        if(!isInside){
          cs225::HSLAPixel & pixel = png.getPixel(x, y);
           pixel.h = 1;
           pixel.s = 1;
           pixel.l = 1;
           pixel.a = 1;
        }

    }
}
for(unsigned a = 0; a<width-1; ++a){
  for(unsigned b = 0; b<height-1; ++b){
    cs225::HSLAPixel & pixel = png.getPixel(a, b);
    cs225::HSLAPixel & pixel1 = png.getPixel(a+1, b);
    cs225::HSLAPixel & pixel2 = png.getPixel(a, b+1);
    cs225::HSLAPixel & pixel3 = png.getPixel(a+1, b+1);
    cs225::HSLAPixel & pixel4 = png.getPixel(a-1, b);
    cs225::HSLAPixel & pixel5 = png.getPixel(a, b-1);
    cs225::HSLAPixel & pixel6 = png.getPixel(a-1, b-1);
    cs225::HSLAPixel & pixel7 = png.getPixel(a+1, b-1);
    cs225::HSLAPixel & pixel8 = png.getPixel(a-1, b+1);

    if(pixel1.l != .45 && pixel2.l != .45 && pixel3.l != .45 && pixel4.l != .45){
      pixel.l = 0;
    }



  }
}
//Code based on http://warp.povusers.org/Mandelbrot/




  return png;
}
