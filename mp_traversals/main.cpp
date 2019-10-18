
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG poop;
  poop.readFromFile("poop.png");
  FloodFilledImage _myimage(poop);
  DFS dfs(poop, Point(200, 200), 0.1);
  BFS bfs(poop, Point(100, 300), 0.1);
  MyColorPicker cpMine;

  HSLAPixel blueish(200, 1, 0.3);
  SolidColorPicker poo(blueish);

  HSLAPixel redish(0, 1, 0.5);
  SolidColorPicker poo2(redish);

  _myimage.addFloodFill(dfs, cpMine);
  _myimage.addFloodFill(bfs, poo);
  _myimage.addFloodFill(bfs, poo2);

  Animation animation = _myimage.animate(450);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
