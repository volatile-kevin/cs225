/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include "cs225/PNG.h"
#include <string>

using namespace cs225;

class StickerSheet : public PNG{
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet &operator= (const StickerSheet &other);
    void changeMaxStickers (unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate (unsigned index, unsigned x, unsigned y);
    void removeSticker (unsigned index);
    void copy(const StickerSheet &other);
    void clear();
    Image * getSticker (unsigned index);
    Image render() const;
  private:
    unsigned max_;
    unsigned numStickers_;
    unsigned * coordinatesX_;
    unsigned * coordinatesY_;
    Image picture_;
    Image ** picturesArr_;
};
