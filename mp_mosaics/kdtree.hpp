/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] > second[curDim]){
      return false;
    }
    else if(first[curDim] < second[curDim]){
      return true;
    }
    else{
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int distance1 = 0;
     int distance2 = 0;

     for(int i = 0; i < Dim; i++){
       distance1 += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
       distance2 += (target[i] - potential[i])*(target[i] - potential[i]);
     }
     if(distance1 > distance2){
       return true;
     }
     else if(distance1 < distance2){
       return false;
     }
     else{
       return potential < currentBest;
     }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::createKD(int start, int end, int dim){

  if(start > end){
    return NULL;
  }
  else{
    int median = (start + end)/2;
    quickSelect(start, end, dim, median);
    KDTreeNode* ptr = new KDTreeNode(treeNodes[median]);

    ptr->left = createKD(start, median-1, (dim+1)%Dim);
    ptr->right = createKD(median+1, end, (dim+1)%Dim);
    return ptr;
  }

}

template <int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int dim, int k){

  if(start > end){
    return;
  }
  int mid = (start + end)/2;
  int pivot = partition(start, end, dim, mid);
  if(k > pivot){
    return quickSelect(pivot+1, end, dim, k);
  }
  else if(k < pivot){
    return quickSelect(start, pivot-1, dim, k);
  }
}

template <int Dim>
int KDTree<Dim>::partition(int start, int end, int dim, int pivotIndex){
  Point<Dim> pivot = treeNodes[pivotIndex];

  std::swap(treeNodes[pivotIndex], treeNodes[end]);
  int pI = start;
  int i;

  for(i = start; i < end; i++){
    if(smallerDimVal(treeNodes[i], pivot, dim)){
      std::swap(treeNodes[i], treeNodes[pI]);
      pI++;
    }
  }

  std::swap(treeNodes[pI], treeNodes[end]);
  return pI;

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     treeNodes = newPoints;
     if(newPoints.size() != 0){
       root = createKD(0, newPoints.size()-1, 0);
     }
     else{
       root = NULL;
       return;
     }


}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    double arr[3] = {0, 2, 9};
    // Dim = 3;
    Point<Dim> finesse = Point<Dim>(arr);

    return finesse;
}
