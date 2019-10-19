/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    //maybe...
    temp->height = updateHeight(temp);
    t->height = updateHeight(t);
    t = temp;


}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    //maybe...
    temp->height = updateHeight(temp);
    t->height = updateHeight(t);
    t = temp;


}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}
template <class K, class V>
int AVLTree<K, V>::updateHeight( Node*& subtree) {
	// subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
  if(!subtree){
      return -1;
    }
    if(updateHeight(subtree->left) < updateHeight(subtree->right)){
      return 1 + updateHeight(subtree->right);
    }
    else{
      return 1 + updateHeight(subtree->left);
    }
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(!subtree){
      // subtree->height = updateHeight(subtree);
      return;
    }

    else{
      int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
      if(balance == 2){
        int balanceRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(balanceRight == 1){
          rotateLeft(subtree);
        }
        else if(balanceRight == -1){
          rotateRightLeft(subtree);
        }
      }
      else if(balance == -2){
        int balanceLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(balanceLeft == -1){
          rotateRight(subtree);
        }
        else if(balanceLeft == 1){
          rotateLeftRight(subtree);
        }
      }
      subtree->height = updateHeight(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(!subtree){
      subtree = new Node(key, value);
    }
    else if(key < subtree->key){
      insert(subtree->left, key, value);
      rebalance(subtree);
    }
    else if(key > subtree->key){
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while(iop->right){
              iop = iop->right;
            }
            swap(iop, subtree);
            remove(subtree->left, key);
            rebalance(iop);
        } else {
            /* one-child remove */
            // your code here
            Node* child;
            if(subtree->left){
              child = subtree->left;
            }
            else{
              child = subtree->right;
            }
            delete subtree;
            subtree = child;
        }
        // your code here
    }
    rebalance(subtree);
}
