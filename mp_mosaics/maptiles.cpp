/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> tilePoints;
     MosaicCanvas *canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     int rows = (int)canvas->getRows();
     int cols = (int)canvas->getColumns();

     map<Point<3>, TileImage*> map_tiles;

     size_t i = 0;
     while(i < theTiles.size()){
       LUVAPixel p = theTiles[i].getAverageColor();

       Point<3> pTile = convertToXYZ(p);
       tilePoints.push_back(pTile);
       map_tiles[pTile] = &theTiles[i];
       i++;
     }

     KDTree<3> new_tree(tilePoints);

     for(int x = 0; x < rows; x++){
       for(int y = 0; y < cols; y++){
         int pos = x * cols + y;
         LUVAPixel source_color = theSource.getRegionColor(x, y);
         Point<3> source_point = convertToXYZ(source_color);

         Point<3> close = new_tree.findNearestNeighbor(source_point);
         canvas->setTile(x, y, map_tiles[close]);
       }
     }

    return canvas;
}
