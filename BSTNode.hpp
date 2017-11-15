/* File Name: BSTNode.hpp
 * Overview:  This file contains the definition of the object BSTNode, the 
 *            constructor and some other realting methods.
 * Author Name: Hantang Zhou (cs100fji) & Nang Chen (cs100fao)
 * Assignment: PA1
 * Date: Oct 4th, 2017
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** Starter code for PA1, CSE 100 2017
 * This code is based on code by
 * Christine Alvarado and Paul Kube.
 */

template<typename Data>
class BSTNode {

  public:

    Data const data;   // the const Data in this node.
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** Constructor.  Initialize a BSTNode with the given Data item,
     *  no parent, and no children.
     */
    BSTNode(const Data & d);


    /** Return the successor of this BSTNode in a BST, or 0 if none.
     ** PRECONDITION: this BSTNode is a node in a BST.
     ** POSTCONDITION:  the BST is unchanged.
     ** RETURNS: the BSTNode that is the successor of this BSTNode,
     ** or 0 if there is none.
     */
    BSTNode<Data>* successor(); 

}; 


// Function definitions
// For a templated class it's easiest to just put them in the same file as the 
// class declaration

template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : data(d), left(0), right(0), parent(0){}

/* Name: BSTNode<Data>* BSTNode<Data>::successor()
 * Input: None
 * Description: Return a pointer to the BSTNode that contains the item that is 
 *              sequentially next in the tree
 * Output: BSTNode<Data>* -- the pointer to the successor BSTNode
 */
using namespace std;
  template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
  if(this == 0)
    return 0;
  BSTNode<Data>* child = 0; // the child
  if (right == 0){//if there is no right child
    if (parent == 0) // root case
      return 0;
    else{ //depends on whether this child is the left or the right
      if(parent->left == this)
        return parent;
      else{ // keeping finding up the tree to find the successor
        child = parent;
        while(1){
          if(child->parent == 0) //return 0 if nothing find until root
            return 0;
          else if(child == child->parent->right){
            child = child->parent;
            continue;
          }  
          else
            return child->parent;
        }
      }
    }
  }
  else{ // if there is a right child
    if (right->left == 0) // if there is no Node larger than right child
      return right;
    else{// if right child has a left child, keep finding the leftmost one
      child = right->left;
      while(1){
        if(child->left == 0)
          return child;
        else
          child = child->left;
      }
    }
  }
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
