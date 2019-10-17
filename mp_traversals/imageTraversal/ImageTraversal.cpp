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
  currentPos_ = Point(0, 0);
  traversal_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start){
  currentPos_ = start;
  traversal_ = traversal;
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

    Point neighbor1 = Point(currentPos_.x + 1, currentPos_.y);
    Point neighbor2 = Point(currentPos_.x, currentPos_.y + 1);
    Point neighbor3 = Point(currentPos_.x - 1, currentPos_.y);
    Point neighbor4 = Point(currentPos_.x, currentPos_.y - 1);

    traversal_->add(neighbor1);
    traversal_->add(neighbor2);
    traversal_->add(neighbor3);
    traversal_->add(neighbor4);

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
  bool end, otherEnd;
  if(traversal_ == NULL || (traversal_->empty() == true)){
    end = true;
  }
  else{
    end = false;
  }
  if(other.traversal_ == NULL || (other.traversal_->empty() == true)){
    otherEnd = true;
  }
  else{
    otherEnd = false;
  }
  if(end == otherEnd){
    return false;
  }
  if(currentPos_ == other.currentPos_){
    return false;
  }
  else{
    return true;
  }
}
