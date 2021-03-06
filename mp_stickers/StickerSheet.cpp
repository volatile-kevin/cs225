#include "StickerSheet.h"
#include "cs225/PNG.h"
#include <string>

using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_ = max;
    picture_ = picture;
    picturesArr_ = new Image*[max];
    coordinatesX_ = new unsigned[max];
    coordinatesY_ = new unsigned[max];
    numStickers_ = 0;
    for(unsigned i = 0; i < max; i++){
        picturesArr_[i] = NULL;
        coordinatesX_[i] = 0;
        coordinatesY_[i] = 0;
    }
}
StickerSheet::~StickerSheet(){
  // for(unsigned i = 0; i < numStickers_; i++){
  //   delete picturesArr_[i];
  //   picturesArr_[i] = NULL;
  // }
    destroy();

}
void StickerSheet::copy(const StickerSheet &other){
    this->max_ = other.max_;
    this->picture_ = other.picture_;
    this->picturesArr_ = new Image*[other.max_];
    this->coordinatesX_ = new unsigned[other.max_];
    this->coordinatesY_ = new unsigned[other.max_];
    this->numStickers_ = other.numStickers_;
    for(unsigned int i = 0; i < this->max_; i++){
        this->picturesArr_[i] = other.picturesArr_[i];
        this->coordinatesX_[i] = other.coordinatesX_[i];
        this->coordinatesY_[i] = other.coordinatesY_[i];
  }
}
void StickerSheet::destroy(){
  // for(unsigned i = 0; i < numStickers_; i++){
  //   delete picturesArr_[i];
  // }
    delete[] picturesArr_;
    delete[] coordinatesX_;
    delete[] coordinatesY_;
}
StickerSheet::StickerSheet(const StickerSheet &other){
    copy(other);
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    destroy();
    copy(other);
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned newMax){
    if(newMax == max_){
      return;
    }
    Image **tempPicturesArr = new Image*[newMax];
    unsigned *tempCoordinatesX = new unsigned[newMax];
    unsigned *tempCoordinatesY = new unsigned[newMax];
    for(unsigned i = 0; i < newMax; i++){
      tempPicturesArr[i] = NULL;
    }
    // extra stickers will get deleted
    if(newMax < numStickers_){
        for(unsigned i = 0; i < newMax; i++){
          tempPicturesArr[i] = picturesArr_[i];
          tempCoordinatesX[i] = coordinatesX_[i];
          tempCoordinatesY[i] = coordinatesY_[i];
        }
        numStickers_ = newMax;
    }
    // when newMax > numStickers_, allocate more space, preserve stickers
    else{
      for(unsigned i = 0; i < newMax; i++){
        if (i >= numStickers_){
          tempPicturesArr[i] = NULL;
          tempCoordinatesX[i] = 0;
          tempCoordinatesY[i] = 0;
          continue;
        }
        if (picturesArr_[i] != NULL)
          tempPicturesArr[i] = picturesArr_[i];
        tempCoordinatesX[i] = coordinatesX_[i];
        tempCoordinatesY[i] = coordinatesY_[i];
      }
    }
    destroy();
    picturesArr_ = tempPicturesArr;
    coordinatesX_ = tempCoordinatesX;
    coordinatesY_ = tempCoordinatesY;
    max_ = newMax;
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if(numStickers_ < max_){
      for(unsigned i = 0; i < max_; i++){

        if(picturesArr_[i] == NULL){

          picturesArr_[i] = &sticker;
          coordinatesX_[i] = x;
          coordinatesY_[i] = y;
          numStickers_ += 1;
          return numStickers_ - 1;

        }
      }
    }

    return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if(picturesArr_[index] == NULL){
    return false;
  }
  else {
    coordinatesX_[index] = x;
    coordinatesY_[index] = y;
    return true;
  }
}
void StickerSheet::removeSticker (unsigned index){
    if(numStickers_ <= index){
      return;
    }
    else {
      picturesArr_[index] = NULL;
      delete picturesArr_[index];
      for(unsigned i = index; i < numStickers_-1; i++){
        if(picturesArr_[i+1] != NULL){
          picturesArr_[i] = picturesArr_[i+1];
          coordinatesX_[i] = coordinatesX_[i+1];
          coordinatesY_[i] = coordinatesY_[i+1];
        }
        else if (picturesArr_[i+1] == NULL){
          delete picturesArr_[i+1];
        }
      }
      picturesArr_[numStickers_-1] = NULL;
      delete picturesArr_[numStickers_-1];
      numStickers_ -= 1;
      return;
    }
}
Image * StickerSheet::getSticker (unsigned index){
    if(numStickers_ > index){
      return picturesArr_[index];
    }
    else {
      return NULL;
    }
}
Image StickerSheet::render() const{
    Image outputImage;
    unsigned pictureWidth = picture_.width();
    unsigned pictureHeight = picture_.height();
    unsigned maxWidth = pictureWidth;
    unsigned maxHeight = pictureHeight;
    for(unsigned i = 0; i < numStickers_; i++){
      if(picturesArr_[i] != NULL){
         if(coordinatesX_[i] + picturesArr_[i]->width() > pictureWidth) {
           maxWidth = coordinatesX_[i] + picturesArr_[i]->width();
         }
         if(coordinatesY_[i] + picturesArr_[i]->height() > pictureHeight) {
           maxHeight = coordinatesY_[i] + picturesArr_[i]->height();
         }
      }
    }
    outputImage = picture_;
    outputImage.resize(maxWidth, maxHeight);
    outputImage.writeToFile("fuckkevinhu.png");

    for(unsigned i = 0; i < numStickers_; i++){
      if(picturesArr_[i] != NULL){
        for(unsigned x = coordinatesX_[i]; x - coordinatesX_[i] < picturesArr_[i]->width(); x++){
          for(unsigned y = coordinatesY_[i]; y - coordinatesY_[i] < picturesArr_[i]->height(); y++){
            if(picturesArr_[i]->getPixel(x - coordinatesX_[i], y - coordinatesY_[i]).a != 0){
              outputImage.getPixel(x, y) =  picturesArr_[i]->getPixel(x - coordinatesX_[i], y - coordinatesY_[i]);
            }
          }
        }
      }
    }
    return outputImage;
}
