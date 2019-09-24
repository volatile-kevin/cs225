#include "Image.h"
#include "cs225/PNG.h"
#include <string>

using namespace std;

void Image::lighten(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l < 1 && pixel.l >= 0){
        pixel.l += 0.1;
        if(pixel.l > 1){
          pixel.l = 1;
        }
      }
      else {
        pixel.l = 1;
      }
    }
  }
}
void Image::lighten(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l < 1 && pixel.l >= 0){
        pixel.l += amount;
        if(pixel.l > 1){
          pixel.l = 1;
        }
      }
      else {
        pixel.l = 1;
      }
    }
  }
}
void Image::darken(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l <= 1 && pixel.l > 0){
        pixel.l -= 0.1;
        if(pixel.l < 0){
          pixel.l = 0;
        }
      }
      else {
        pixel.l = 1;
      }
    }
  }
}
void Image::darken(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l <= 1 && pixel.l > 0){
        pixel.l -= amount;
        if(pixel.l < 0){
          pixel.l = 0;
        }
      }
      else {
        pixel.l = 1;
      }
    }
  }
}
void Image::saturate(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s <= 1 && pixel.s >= 0){
        pixel.s += 0.1;
      }
      else {
        pixel.s = 1;
      }
    }
  }
}
void Image::saturate(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s <= 1 && pixel.s >= 0){
        pixel.s += amount;
      }
      else {
        pixel.s = 1;
      }
    }
  }
}
void Image::desaturate(){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s <= 1 && pixel.s >= 0){
        pixel.s -= 0.1;
      }
      else {
        pixel.s = 1;
      }
    }
  }
}
void Image::desaturate(double amount){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s <= 1 && pixel.s >= 0){
        pixel.s -= amount;
      }
      else {
        pixel.s = 1;
      }
    }
  }
}
void Image::grayscale(){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);

      // `pixel` is a pounsigned inter to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}
void Image::rotateColor(double degrees){
  for (unsigned int i = 0; i < this->width(); i++){
    for (unsigned int j = 0; j < this->height(); j++){
      HSLAPixel & pixel = this->getPixel(i, j);
        double tempHue = pixel.h;
        tempHue += degrees;
        if(tempHue > 360) {
           tempHue -= 360;
        }
        else if(tempHue < 0) {
          tempHue += 360;
        }
        pixel.h = tempHue;
    }
  }
}
void Image::illinify(){
  for (unsigned int x = 0; x < this->width(); x++) {
    for (unsigned int y = 0; y < this->height(); y++) {
      HSLAPixel & pixel = this->getPixel(x, y);
      if(pixel.h <= 113 || pixel.h >= 293)
        pixel.h = 11;
      else
        pixel.h = 216;
    }
  }
}
void Image::scale(double factor){
  unsigned int width = (unsigned int)(this->width() * factor);
  unsigned int height = (unsigned int)(this->height() * factor);
  PNG* scaledImage = new PNG(width, height);
  for (unsigned int i = 0; i < width; i++){
    for (unsigned int j = 0; j < height; j++){
      HSLAPixel & pixel = scaledImage->getPixel(i, j);
      unsigned int correspondingI = (unsigned int) (0.5 + this->width() * i / width);
      unsigned int correspondingJ = (unsigned int) (0.5 + this->height() * j / height);
      pixel = this->getPixel(correspondingI, correspondingJ);
    }
  }

  this->resize(width, height);
  for (unsigned int i = 0; i < width; i++){
    for (unsigned int j = 0; j < height; j++){
      HSLAPixel & pixel = scaledImage->getPixel(i, j);
      HSLAPixel & tempPixel = this->getPixel(i, j);
      tempPixel = pixel;
    }
  }

  delete scaledImage;
}
void Image::scale(unsigned w, unsigned h){
  double widthFactor = w / this->width();
  double heightFactor = h / this->height();
  double minFactor = min(widthFactor, heightFactor);
  /*
  if (min(widthFactor, heightFactor) == widthFactor && widthFactor == 0){
    minFactor = heightFactor;
  }
  if (min(widthFactor, heightFactor) == heightFactor && heightFactor == 0){
    minFactor = widthFactor;
  } */
  scale(minFactor);
}
