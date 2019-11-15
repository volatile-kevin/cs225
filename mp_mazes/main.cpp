#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
        PNG* myImage = maze.drawCreativeMaze(300, 200);
        myImage->writeToFile("myImage.png");
        return 0;
}
