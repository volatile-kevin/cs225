#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  // currentPos_ = Point(0, 0);
  traversal_ = NULL;
  tolerance_ = 0;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start, double tolerance){
  currentPos_ = start;
  traversal_ = traversal;
  tolerance_ = tolerance;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traversal_ != NULL && traversal_->empty() == false){
    currentPos_ = traversal_->pop();
    traversal_->vectorVisited[currentPos_.x][currentPos_.y] = true;

    Point neighborRight = Point(currentPos_.x + 1, currentPos_.y);
    Point neighborDown = Point(currentPos_.x, currentPos_.y + 1);
    Point neighborLeft = Point(currentPos_.x - 1, currentPos_.y);
    Point neighborUp = Point(currentPos_.x, currentPos_.y - 1);

    traversal_->add(neighborRight);
    traversal_->add(neighborDown);
    traversal_->add(neighborLeft);
    traversal_->add(neighborUp);

    if(traversal_->empty() == true){
      return *this;
    }

    currentPos_ = traversal_->peek();

    while((traversal_->empty() == false) && traversal_->vectorVisited[currentPos_.x][currentPos_.y] == true){
      traversal_->pop();
      currentPos_ = traversal_->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currentPos_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(traversal_->empty()){
    return false;
  }
  return true;
}
