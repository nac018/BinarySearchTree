/* File Name: BSTIterator.hpp
 * Overview:  This file contains the definition of the object BSTIterator, the 
 *            constructor and some other realting methods.
 * Author Name: Hantang Zhou (cs100fji) & Nang Chen (cs100fao)
 * Assignment: PA1
 * Date: Oct 4th, 2017
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>


// Notice this class extends the std::iterator class.
template<typename Data>
class BSTIterator : public std::iterator<std::input_iterator_tag,Data> {

private:

  BSTNode<Data>* curr;

public:

  /** Constructor.  Use the argument to initialize the current BSTNode
   *  in this BSTIterator.
   */ 
  BSTIterator(BSTNode<Data>* curr);

  /** Dereference operator. */
  Data operator*() const;
  
  /** Pre-increment operator. */
  BSTIterator<Data>& operator++();

  /** Post-increment operator. */
  BSTIterator<Data> operator++(int);

  /** Equality test operator. */
  bool operator==(BSTIterator<Data> const & other) const;

  /** Inequality test operator. */ 
  bool operator!=(BSTIterator<Data> const & other) const;

};

  /** Constructor.  Use the argument to initialize the current BSTNode
   *  in this BSTIterator.
   */ 
/* Function Name: BSTIterator<Data>::BSTIterator
 * Input: BSTIterator<Data>* - the Node that the iterator is currently on
 * Description: Create a BSTIterator object
 * Output: N/A
 */
template<typename Data>
BSTIterator<Data>::BSTIterator(BSTNode<Data>* curr) {
  // Remember the keyword "this" which stores a pointer to the calling object.
  // It will be helpful to distinguish between the parameter "curr" and the 
  // member variable "curr"
  this->curr=curr;
}

/** Dereference operator. */
template<typename Data>
Data BSTIterator<Data>::operator*() const {
  return curr->data;
}
  
/** Pre-increment operator. */
template<typename Data>
BSTIterator<Data>& BSTIterator<Data>::operator++() {
  // Call the successor method of the BSTNode pointed to by curr.
  curr = curr->successor();
  return *this;
}

/** Post-increment operator. */
template<typename Data>
BSTIterator<Data> BSTIterator<Data>::operator++(int) {
  BSTIterator before = BSTIterator(curr);
  ++(*this);
  return before;
}

/** Equality test operator. */
/* Function Name: BSTIterator<Data>::operator==
 * Input: BSTIterator<Data> const & - the one we are comparing to the object
 * Description: Check if the two is pointing to the same BSTNode in the same BST
 * Output:  Return true if other is equal to the calling object and return 
 *          false otherwise
 */
template<typename Data>
bool BSTIterator<Data>::operator==(BSTIterator<Data> const & other) const {
  return this->curr == other.curr ? true : false; 
  // Notice that other is a reference and not a pointer, thus it cannot be null
  // Return true if other is equal to the calling object
  // Two iterators are equal if they point to the same BSTNode in the same BST
}

/** Inequality test operator. */ 
/* Function Name: BSTIterator<Data>::operator!=
 * Input: BSTIterator<Data> const & - the one we are comparing to the object
 * Description: Check if the two is pointing to the same BSTNode in the same BST
 * Output:  Return true if other is not equal to the calling object and return 
 *          false otherwise
 */
template<typename Data>
bool BSTIterator<Data>::operator!=(BSTIterator<Data> const & other) const {
  return this->curr != other.curr ? true : false; 
  // Notice that other is a reference and not a pointer, thus it cannot be null
  // Return true if other is NOT equal to the calling object
  // Two iterators are equal if they point to the same BSTNode in the same BST
}


#endif //BSTITERATOR_HPP
