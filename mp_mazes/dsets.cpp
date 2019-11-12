/* Your code here! */
#include "dsets.h"
using namespace std;

void DisjointSets::addelements(int num){
  int i = 1;
  for(; i <= num; i++){
    elements.push_back(-1);
  }
  return;
}

int DisjointSets::find(int elem){
  if(elements[elem] >= 0){
    elements[elem] = find(elements[elem]);

    return elements[elem];
  }
  else{
    return elem;
  }
}

void DisjointSets::setunion(int a, int b){
  int tempA = find(a);
  int tempB = find(b);
  int size = elements[tempA] + elements[tempB];
  if(tempA == tempB){
    return;
  }
  if(tempA < tempB){
    elements[tempB] = tempA;
    elements[tempA] = size;
  }
  else{
    elements[tempA] = tempB;
    elements[tempB] = size;
  }
}

int DisjointSets::size(int elem){
  return elements[find(elem)] * -1;
}
