/* Your code here! */
#include "maze.h"

#include <iostream>
#include <sys/time.h>
#include <vector>
#include <queue>

using namespace std;

SquareMaze::SquareMaze(){
  //empty?
}




void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;

  int size = width * height;
  mazeSets.addelements(size);
  int i = 0;
  while(i < size){
    rightWalls.push_back(true);
    downWalls.push_back(true);
    i++;
  }

  // rand time
  int x;
  int y;
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(time.tv_usec);

  while(mazeSets.size(0) < size){

    x = rand() % width_;
    y = rand() % height_;
    int pos = y * width_ + x;
    if(rand() % 2 != 1){
      if(y != height_ - 1){
        if(mazeSets.find(pos) != mazeSets.find(pos + width_)){
          setWall(x, y, 1, false);
          mazeSets.setunion(pos, pos + width_);
        }
      }
    }
    else{
      if(x != width_ - 1){
        if(mazeSets.find(pos) != mazeSets.find(pos + 1)){
          rightWalls[y * width_ + x] = false;
          mazeSets.setunion(pos, pos + 1);
        }
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  int pos = y * width_ + x;
  if(dir < 0 || dir > 3 || x < 0 || y < 0){
    return false;
  }
  if(dir == 0){
    return rightWalls[pos] == false;
  }
  else if(dir == 1){
    return downWalls[pos] == false;
  }
  else if(dir == 2){
    return (x != 0) && (rightWalls[pos - 1] == false);
  }
  else{
    return (y != 0) && (downWalls[pos - width_] == false);
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int pos = y * width_ + x;
  if(dir != 0 && dir != 1){
    return;
  }
  if(dir == 1){
    downWalls[pos] = exists;
  }
  else{
    rightWalls[pos] = exists;
  }
}

vector<int> SquareMaze::solveMaze(){
  int x;
  int y;
  int curr;
  int size;
  int maxDist;
  vector<int> previous;
  vector<int> dist;

  size = width_ * height_;


  previous.push_back(0);
  dist.push_back(0);

  for(int i = 1; i < size; i++){

    previous.push_back(-1);
    dist.push_back(0);
  }

  queue<int> BFS;
  BFS.push(0);

  while(BFS.empty() == false){
    curr = BFS.front();
    x = curr % width_;
    y = curr / width_;
    BFS.pop();
    if(canTravel(x, y, 0)){
      if(previous[curr + 1] == -1){
        BFS.push(curr + 1);
        previous[curr + 1] = curr;
        dist[curr + 1] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 1)){
      if(previous[curr + width_] == -1){
        BFS.push(curr + width_);
        previous[curr + width_] = curr;
        dist[curr + width_] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 2)){
      if(previous[curr - 1] == -1){
        BFS.push(curr - 1);
        previous[curr - 1] = curr;
        dist[curr - 1] = dist[curr] + 1;
      }
    }
    if(canTravel(x, y, 3)){
      if(previous[curr - width_] == -1){
        BFS.push(curr - width_);
        previous[curr - width_] = curr;
        dist[curr - width_] = dist[curr] + 1;
      }
    }
  }
  maxDist = width_ * (height_ - 1);

  for(int j = 0; j < width_; j++){
    if(dist[((height_ - 1) * width_) + j] > dist[maxDist]){
      maxDist = width_ * (height_ - 1) + j;
    }
  }

  destination = maxDist;
  vector<int> soln;
  curr = destination;
  while(curr != 0){
    if(previous[curr] == curr - 1){
      soln.push_back(0);
    }
    if(previous[curr] == curr - width_){
      soln.push_back(1);
    }
    if(previous[curr] == curr + 1){
      soln.push_back(2);
    }
    if(previous[curr] == curr + width_){
      soln.push_back(3);
    }
    curr = previous[curr];
  }
  reverse(soln.begin(), soln.end());
  return soln;
}

PNG* SquareMaze::drawMaze() const{
   int w = width_ * 10 + 1;
   int h = height_ * 10 + 1;
   PNG* canvas = new PNG(w, h);

   for(int x = 10; x < w; x++){
     HSLAPixel& p = canvas->getPixel(x, 0);
     p.h = 0;
     p.s = 0;
     p.l = 0;
     p.a = 1;   }
   for(int y = 0; y < h; y++){
     HSLAPixel& p = canvas->getPixel(0, y);
     p.h = 0;
     p.s = 0;
     p.l = 0;
     p.a = 1;   }


   for(int x = 0; x < width_; x++){
     for(int y = 0; y < height_; y++){
       int pos = y * width_ + x;
       if(rightWalls[pos]){
         for(int k = 0; k < 11; k++){
           HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
           p.h = 0;
           p.s = 0;
           p.l = 0;
           p.a = 1;
         }
       }
       if(downWalls[pos]){
         for(int k = 0; k < 11; k++){
           HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
           p.h = 0;
           p.s = 0;
           p.l = 0;
           p.a = 1;
         }
       }
     }
   }
   return canvas;

 }

PNG* SquareMaze::drawMazeWithSolution(){
  PNG* canvas = drawMaze();
  vector<int> soln = solveMaze();
  int i = 5;
  int j = 5;

  int destI = destination % width_;
  int destJ = destination / height_;
  for(int idx = 1; idx < 10; idx++){
    HSLAPixel &p = canvas->getPixel(destI * 10 + idx, (destJ + 1) * 10);
    p.l = 1;
  }
  for(size_t idx2 = 0; idx2 < soln.size(); idx2++){
    if(soln[idx2] == 0){
      for(int idx3 = 0; idx3 < 11; idx3++){
        HSLAPixel &p = canvas->getPixel(i + idx3, j);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      i += 10;
    }
    else if(soln[idx2] == 1){
      for(int idx3 = 0; idx3 < 11; idx3++){
        HSLAPixel &p = canvas->getPixel(i, j + idx3);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      j += 10;
    }
    else if(soln[idx2] == 2){
      for(int idx3 = 0; idx3 < 11; idx3++){
        HSLAPixel &p = canvas->getPixel(i - idx3, j);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      i -= 10;
    }
    else{
      for(int idx3 = 0; idx3 < 11; idx3++){
        HSLAPixel &p = canvas->getPixel(i, j - idx3);
        p.h = 0;
        p.s = 1;
        p.l = 0.5;
        p.a = 1;
      }
      j -= 10;
    }
  }
  return canvas;
}

PNG* SquareMaze::drawCreativeMaze(int width, int height){
  // srand(10);
  // makeMaze(width, height);
  // PNG* result = new PNG(width*10 + 1, height*10 + 1);
  // pngH = result->height();
  // pngW = result->width();
  // for(unsigned x = 0; x < pngW; x++){
  //
  // }
  std::srand(42);
	makeMaze(width, height);
	PNG* result = new PNG(width*10 + 1, height*10 + 1);
	//left most column
	for (unsigned int y = 0; y < result->height(); y++) {
		result->getPixel(0, y).l = 0;
	}

	//top most row
	for (unsigned int x = 0; x < result->width(); x++) {
		if (x > 9 || x < 1) {
			result->getPixel(x, 0).l = 0;
		}
	}

	//for each square in the maze,
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (rightWalls[(y * width) + x]) {
				//if the right wall exists, blacken ((x+1)*10, y*10 + k) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					result->getPixel((x+1) * 10, y * 10 + k).l = 0;
				}
			}

			if (downWalls[(y * width) + x]) {
				//if the down wall exists, blacken ((x*10 + k, (y+1)*10) from k = 0 to 10
				for (int k = 0; k < 11; k++) {
					result->getPixel(x*10 + k, (y+1)*10).l = 0;
				}
			}
		}
	}

  for (unsigned int x = 0; x < result->width(); x++) {
  		for (unsigned int y = 0; y < result->height(); y++) {


  				if (x >= 1000 && x <= 2200) {
  					if (y <= 400 && y >= 0) {
  						result->getPixel(x, y).l = 0.5;
  						result->getPixel(x, y).h = 11;
  						result->getPixel(x, y).s = 0.7;
  					}
  				}

  				if (x >= (1000+350) && x <= (2200-350)) {
  					if(y > 400 && y <= 1200) {
  						result->getPixel(x,y).l = 0.5;
  						result->getPixel(x,y).h = 11;
  						result->getPixel(x, y).s = 0.7;
  					}
  				}

  				if (x >= 1000 && x <= 2200) {
  					if (y <= 1600 && y >= 1200) {
  						result->getPixel(x,y).l = 0.5;
  						result->getPixel(x,y).h = 11;
  						result->getPixel(x, y).s = 0.7;
  					}
  				}

  		}
  	}

	std::vector<int> solVec = solveMaze();

	int poox = 5;
	int pooy = 5;
	for (int direction : solVec) {
		int incX = 0;
		int incY = 0;
		if (direction == 0) {
			incX = 1;
		}
		else if (direction == 1) {
			incY = 1;
		}
		else if (direction == 2) {
			incX = -1;
		}
		else if (direction == 3) {
			incY = -1;
		}

		for (int i = 0; i <= 10; i++) {
			HSLAPixel & pp = result->getPixel(poox, pooy);
			pp.h = 0;
			pp.s = 1;
			pp.l = 0.5;
			pp.a = 1;

			poox += incX;
			pooy += incY;
		}

		poox -= incX;
		pooy -= incY;
	}

	for (int k = 1; k <= 9; k++) {
		result->getPixel((poox/10)*10 + k, ((pooy/10)+1)*10).l = 1;
	}

	return result;
}
