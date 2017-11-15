/* File Name: main.hpp
 * Overview:  This file contains the main function, which read a list of actor 
 *            name as input and prompt user to find an item
 * Author Name: Hantang Zhou (cs100fji) & Nang Chen (cs100fao)
 * Assignment: PA1
 * Date: Oct 4th, 2017
 */
#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include<fstream>
#include<string>

/**
 *  IMPORTANT!! DO NOT CHANGE THE LINES THAT DO I/O BELOW.
 *
 *  Note that size, height, and name are local variables in main that you 
 *  should update accordingly. Also note that actor/actress names will be 
 *  in all caps, last name followed by first name 
 *  (except in odd cases, eg. "50 CENT" and "ICE-T")
 */

using namespace std;

int main(int argc, char* argv[])
{
    //Size of tree should be stored in local variable size.
    //Height of tree should be stored in local variable height.
    //Input name will be stored in a string name
    unsigned int size = 0;
    unsigned int height = 0;
    std::string name = "";
  
    //Check for Arguments
    if(argc != 2){
        cout << "Invalid number of arguments.\n" 
             << "Usage: ./main <input filename>.\n";
        return -1;
    }
  
    //Open file 
    ifstream in;
    in.open(argv[1]);

    
  
    //Check if input file was actually opened
    if(!in.is_open()) 
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
	else {
	  
        // Follow the comments below to add code:
        
        //Create a new BST here
        BST<string>* bst = new BST<string>();

        
        while (getline(in, name)) {
          //add the name string to the BST
          bst->insert(name);
            
        }

        //Get the height of the BST and store it in height
        height = bst->height();

        //Get the size of the BST and store it in size
        size = bst->size();

        // DO NOT CHANGE THE LINES BELOW
        cout << "Size of tree: " << size << endl;
        cout << "Height of tree: " << height << endl;

        // if debug, uncomment the line below to print the tree        
        //bst->print(); //student debug helper method print()
        

        char prompt = 'y';
        while (prompt != 'n') {
            cout << "Enter actor/actress name: " << endl;
            getline(cin, name);
            
            //Change the if statment to check is name is in the BST
            BSTNode<string>* nameNode = new BSTNode<string>(name);
            if (*(bst->find(name)) == name){
                cout << name << " found!" << endl;
            }
            else {
                cout << name << " NOT found" << "\n";
            }
            delete nameNode;
            cout << "Search again? (y/n)" << endl;
            cin >> prompt;  // Get the first character
            // Then ignore until newline
            cin.ignore( numeric_limits <streamsize> ::max(), '\n' );  
        }
        in.close();
        
        // deallocate memory
        delete bst;

    }
    return 0;

}
