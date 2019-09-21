#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("tests/alma.png");
  Image poop;    poop.readFromFile("poop.png");
  Image equal;    equal.readFromFile("equal.png");
  Image mycode;    mycode.readFromFile("mycode.png");


  StickerSheet outputStickerSheet(alma, 3);
  outputStickerSheet.addSticker(poop, 600, 200);
  outputStickerSheet.addSticker(equal, 400, 200);
  outputStickerSheet.addSticker(mycode, 200, 200);
  Image output = outputStickerSheet.render();

  output.writeToFile("myImage.png");

  return 0;
}
