/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode * curr = head_;
  ListNode * temp;

  while(curr != NULL){
    temp = curr->next;
    delete curr;
    curr = temp;
  }
  /// @todo Graded in MP3.1
  return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if(tail_ != NULL){
    tail_->next = newNode;
  }
  if(head_ == NULL){
    head_ = newNode;
  }

  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(splitPoint == 0){
    return start;
  }

  ListNode * curr = start;

  for (int i = 0; curr != NULL && i < splitPoint; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  length_ -= splitPoint;

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * temp;

  if(curr == NULL){
    return;
  }
  int count = 0;
  while(curr != tail_ && curr != NULL){
    if(count % 2 == 1){
      //remove element
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      temp = curr;
      curr = curr->next;
      temp->next = NULL;

      //append to back
      tail_->next = temp;
      temp->prev = tail_;
      tail_ = temp;
    }
    else{
      curr = curr->next;
    }
    count++;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint == NULL || startPoint->next == NULL || startPoint == endPoint){
    return;
  }
  /// @todo Graded in MP3.2
  ListNode * temp;
  ListNode * curr = startPoint;
  ListNode * saveEnd2 = endPoint;
  ListNode * saveStart2 = startPoint;
  ListNode * saveStart = startPoint->prev;
  ListNode * saveEnd = endPoint->next;


  while (curr != saveEnd2)
  {
      temp = curr->prev;
      curr->prev = curr->next;
      curr->next = temp;
      curr = curr->prev;
  }
  curr->next = curr->prev;
  curr->prev = saveStart;
  startPoint->next = saveEnd;
  if(saveEnd != NULL){
    saveEnd->prev = startPoint;
  }
  else{
    tail_ = startPoint;
  }
  if(saveStart != NULL){
    saveStart->next = endPoint;
  }
  else{
    head_ = endPoint;
  }

  startPoint = saveEnd2;
  endPoint = saveStart2;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  if(head_ == NULL || n <= 1){
    return;
  }
  ListNode * start = head_;
  ListNode * curr = head_;

  while(start != NULL){
    curr = start;
    int count = 1;
    while(count < n){
      if(curr->next != NULL){
        curr = curr->next;
      }
      count++;
    }
    reverse(start, curr);
    start = curr->next;
  }

  return;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  ListNode* tempA = NULL;
  ListNode* tempB = NULL;
  ListNode* merge = NULL;
  ListNode* temp = NULL;

  if (first->data < second->data)
  {
      merge = first;
      tempB = second;
      tempA = first;
  }
  else
  {
      merge = second;
      tempB = first;
      tempA = second;
  }

  while (tempA->next != NULL)
  {
      if (!(tempA->next->data < tempB->data || tempA->next->data == tempB->data))
      {
          temp = tempA->next;
          tempA->next = tempB;
          tempA = tempB;
          tempB->prev = tempA;
          tempA = tempB;
          tempB = temp;
      }
      else
      {
          tempA = tempA->next;
      }
  }

  tempA->next = tempB;
  return merge;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){
    return start;
  }
  int newLength = chainLength/2;
  ListNode * secondHead;
  secondHead = split(start, newLength);
  start = mergesort(start, newLength);
  secondHead = mergesort(secondHead, chainLength - newLength);

  ListNode * newHead =  merge(start, secondHead);

  return newHead;
}
