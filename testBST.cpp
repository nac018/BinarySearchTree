#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2017
 * Based on code by Christine Alvarado
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);

    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    
    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;      
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }

    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.
    // there are originally 5 numbers in the tree:  3, 4, 1, 100, -33

    cout << "\n*****Test added by students*****\n";

    // Testing on inserting the same number again
    cout << "Testing size and height method...\n"<< 
            "inserting same element 100(change neither height nor size)..." 
            << endl;
    unsigned int theight = btemp.height();
    unsigned int tsize = btemp.size();
    btemp.insert(100);
    if (btemp.height() != theight || btemp.size() != tsize){
      cout << "Error occurs when inserting same element again.\n";
      if(btemp.size() != tsize)
      cout << "size should be: " << tsize << ", but it returns " << btemp.size()
        << endl;
      if(btemp.height() != theight)
      cout << "height should be: " << theight << ", but it returns " << 
        btemp.height() << endl;
      return -1;
    }
    
    // Testing on inserting new number without changing the height
    cout << "inserting new element 2 (change size, not height)..." << endl;
    btemp.insert(2);
    if (btemp.height() != theight || btemp.size() != (tsize+1)){
      cout << "Error occurs when inserting new element.\n";
      if(btemp.size() != (tsize+1))
      cout << "size should be: " << (tsize+1) << ", but it returns " <<
        btemp.size() << endl;
      if(btemp.height() != theight)
      cout << "height should be: " << theight << ", but it returns " << 
        btemp.height() << endl;
       return -1;
    }

    // Testing on inserting new number changing both size and height
    cout << "inserting new element -35 (change size and height)..." << endl;
    btemp.insert(-35);
    if (btemp.height() != (theight+1) || btemp.size() != (tsize+2)){
      cout << "Error occurs when inserting new element.\n";
      if(btemp.size() != (tsize+2))
      cout << "size should be: " << (tsize+2) << ", but it returns " <<
        btemp.size() << endl;
      if(btemp.height() != (theight+1))
      cout << "height should be: " << (theight+1) << ", but it returns " << 
        btemp.height() << endl;
       return -1;
    }



    cout << "success!" << endl;
    
    cout << "Create a new tree containning strings on the heap" << endl;

    // create a new tree
    BST<string>* bs = new BST<string>;
    
    //Testing on empty function
    cout << "testing empty funcion..." << endl;
    if (bs->empty() != true){
      cout << "Incorrect empty function, answer should be true." << endl;
      return -1;
    }

    // insert something to make it no empty
    bs->insert("CSE100FA17");

    if (bs->empty() == true){
      cout << "Incorrect empty function, answer should be false." << endl;
      return -1;
    }

    cout << "success!" << endl;

    //deallocate the tree
    cout<< "Deallocate the tree, use Valgrind to check for the memory leak\n";
    delete bs;

    cout << "All tests passed!" << endl;
    return 0;
}
