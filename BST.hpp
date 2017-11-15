/* File Name: BST.hpp
 * Overview:  This file contains the definition of the object BST, the 
 *            constructor and some other realting methods.
 * Author Name: Hantang Zhou (cs100fji) & Nang Chen (cs100fao)
 * Assignment: PA1
 * Date: Oct 4th, 2017
 */
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

  public:

    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
      */
    BST() : root(nullptr), isize(0) {}


    /** Default destructor.
      Delete every node in this BST.
      */
    ~BST();

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return a pair where the first element is an iterator 
     *  pointing to either the newly inserted element or the element 
     *  that was already in the BST, and the second element is true if the 
     *  element was newly inserted or false if it was already in the BST.
     * 
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  
     */
    std::pair<iterator, bool> insert(const Data& item);


    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    iterator find(const Data& item) const;


    /** Return the number of items currently in the BST.
    */ 
    unsigned int size() const;

    /** Return the height of the BST.
      height of a tree starts with root at height 0
      */ 
    unsigned int height() const;


    /** Return true if the BST is empty, else false.
    */
    bool empty() const;

    /** Return an iterator pointing to the first (smallest) item in the BST.
    */ 
    iterator begin() const;

    /** Return an iterator pointing past the last item in the BST.
    */
    iterator end() const;

    /***** student debug helper *******/
    void print();

    void printHelper(BSTNode<Data>* node);

  private:

    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data>* root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Find the first element of the BST
     * Helper function for the begin method above.
     */ 
    static BSTNode<Data>* first(BSTNode<Data>* root);

    /** do a postorder traversal, deleting nodes
    */
    static void deleteAll(BSTNode<Data>* n);

    /******************** student added helper method ****************/
    /** find the height of a certain BSTNode
    */
    unsigned int heightHelper(BSTNode<Data>* node) const;
};


// ********** Function definitions ****************


/** Default destructor.
  Delete every node in this BST.
  */
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}

/* Function Name: insert
 * Input: constant Data& - the data that we are going to insert
 * Description: Given a reference to a Data item, insert a copy of it in BST.
 * Output:  Return a pair where the first element is an iterator pointing to 
 *          either the newly inserted element or the element that was already 
 *          in the BST, and the second element is true if the element was newly
 *          inserted or false if it was already in the BST.
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  BSTNode<Data>* current = nullptr; //the Node we are checking
  Data itemRef =Data(item); //make a copy of item
  if (this->empty() == true){//if there is nothing in the tree, then it is root
    root = new BSTNode<Data>(itemRef);
    isize++;
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);
  }
  else{
    current = root; // if there has a root, then start with the root
    while(1){
      if(current->data < item){ // if less than the current node
        if(current->right != 0){ // if there is a right, compare them
          current = current-> right;
          continue;
        }
        else{ //if there is no right, return an iterator containing current
          current->right = new BSTNode<Data>(itemRef); //insert a new Node
          current->right->parent = current; // initialize the parent node
          isize++; //increase the size
          return std::pair<BSTIterator<Data>, bool>
                      (BSTIterator<Data>(current->right), true);
        }
      }
      else if(item < current->data){ // if larger than the current node
        if (current->left != 0){ // if there is a left, compare them
          current = current-> left;
          continue;
        }
        else //if there is no left, return an iterator containing current
          current->left = new BSTNode<Data>(itemRef); //insert a new Node
          current->left->parent = current; // initialize the parent node
          isize++; //increase the size
          return std::pair<BSTIterator<Data>, bool>
                      (BSTIterator<Data>(current->left), true);
      }
      else // if we found, return an iterator containing the current
        return std::pair<BSTIterator<Data>, bool>(current, false);
    }
  }
}


/* Function Name: find
 * Input: constant Data& - the data that we are going to find
 * Description: Find a Data item in the BST.
 * Output: Return an iterator pointing to the item, or pointing past
 *         the last node in the BST if not found.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  BSTNode<Data>* current = nullptr; //the Node we are checking
  if (this->empty() == true) // if there is nothing in the tree
    return BSTIterator<Data>(nullptr);
  current = root; // start with the root
  while(1){
    if(current->data < item){ // if less than the current node
      if(current->right != 0){ // if there is a right, compare them
        current = current-> right;
        continue;
      }
      else //if there is no right, return an iterator containing current
        return BSTIterator<Data>(nullptr);
    }
    else if(item < current->data){ // if larger than the current node
      if (current->left != 0){ // if there is a left, compare them
        current = current-> left;
        continue;
      }
      else //if there is no left, return an iterator containing current
        return BSTIterator<Data>(nullptr);
    }
    else // if we found, return an iterator containing the current
      return BSTIterator<Data>(current);
  }
}


/** Return the number of items currently in the BST.
*/ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/* Function: heightHelper
 * Input: BSTNode<Data>* node - the node of which we want to find the height
 * Description: recursively finding the height of the node out
 * Output: unsigned int - the height of the node
 */
template <typename Data>
unsigned int BST<Data>::heightHelper(BSTNode<Data>* node) const{
  // find the height of each child node
  int leftHeight = (node->left == 0) ? -1: heightHelper(node->left); 
  int rightHeight = (node->right == 0) ? -1: heightHelper(node->right);
  // choose whichever is the larger one
  return 1 + (leftHeight > rightHeight? leftHeight: rightHeight);
}

/** Return the height of the BST.
*/
/* Function: height
 * Input: None
 * Description: finding the height of this tree
 * Output: unsigned int - the height of the tree
 */
template <typename Data> 
unsigned int BST<Data>::height() const
{
  return heightHelper(root);
}

/** Return true if the BST is empty, else false.
*/ 
/* Function Name: BST<Data>::empty const
 * Input: None
 * Description: Check if the BST is empty
 * Output:  Return true if there is no root and false otherwise
 */
template <typename Data>
bool BST<Data>::empty() const
{
  return root == 0 ? true : false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
*/ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
*/
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/* Function Name: first
 * Input: BSTNode<Data>* - the pointer to the root
 * Description: Find the first element of the BST. It is a helper function 
 *              for the begin method above.
 * Output: BSTNode<Data> - the pointer to the very first element of the BST
 */ 
  template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* leftChild = nullptr; // the left child
  if (root == 0) // if the root is nullptr
    return nullptr;
  else if (root->left == 0) //if element less than the root
    return root;
  else{ // if there is a left child, then keep finding the leftmost child
    leftChild = root->left;
    while(1){
      if(leftChild->left == 0)
        return leftChild;
      else
        leftChild = leftChild->left;
    }
  }
}

/* Function Name: deleteAll
 * Input: BSTNode<Data> - the node that we delete from
 * Description: do a postorder traversal, deleting nodes
 * Output: None
 */
  template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if (n==0) // if there is no more to delete
    return;
  deleteAll(n->right);
  deleteAll(n->left);
  delete(n);
}

/* Function Name: printHelper
 * Input: BSTNode<Data> - the node that we start printing from
 * Description: print every node that derived from the parameter recersively
 * Output: The information of the node is printed to the console
 */
template <typename Data>
void BST<Data>::printHelper(BSTNode<Data>* node){
  if(node == 0){ // if the node is nullptr, return
    return;
  }
  else{// print the information
    cerr << "The node " << node->data;
    cerr << " has a left child ";
    if(node->left == 0)
      cerr << "N/A";
    else
      cerr << node->left->data;
    cerr << ", and a right child ";
    if(node->right == 0)
      cerr << "N/A\n";
    else
      cerr << node->right->data << "\n";
  }
  // recursively print all the node derived from it
  if(node->left !=0)
    printHelper(node->left);
  if(node->right !=0)
    printHelper(node->right);
}

/* Function Name: print
 * Input: None
 * Description: print the whole tree
 * Output: The information of the node is printed to the console
 */
template <typename Data>
void BST<Data>::print(){
  printHelper(root);//print start the root
}

#endif //BST_HPP
