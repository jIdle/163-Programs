/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Assignment #4
 *
 * This file (BST_header.h) will hold the BST class and node struct. 
 */

#include "cs_term.h"

//node struct which contains a left child, a right child, and an info object which contains info on a CS term
struct node
{
    info cs_term;//info datatype
    node * left;//node datatype
    node * right;//node datatype
};

//tree class which makes up the BST data structure contains functions to: insert new data,
//remove data already existing in tree, search for pre-existing data, find the height of the tree,
//determine whether the tree is considered balanced, display all data in alphabetical order, display 
//data ranging from some given value to another given value, and finally a load function to receive 
//data from an external file and insert it into the BST.
class tree
{
    public:
        tree();//constructor
        ~tree();//destructor
        int insert(info to_add);//returns an integer and takes an info object as an argument, insert function will insert the given data into the BST
        int remove(info match);//returns an integer and takes an info object as an argument, remove function will search for the requested data and if found, will delete
        int retrieve(info & match);//returns an int and takes an info object by reference as an argument, the retrieve function will search for the requested term and place the data found into the handed info object
        int get_height();//returns an integer and takes no argument, get_height function makes use of the max() function in the cstdlib library to return the highest value from each path search. through searching each path the height will be found.
        bool is_efficient();//returns a boolean value and takes no argument, does something similar to the get_height fuction by searching each path, on return(after hitting void) is_efficient will compare the heights of subtrees to determine if tree is unbalanced 
        int display_all();//returns an integer and takes no arguments display all goes left to right displaying all data
        int display_range(char lower, char upper);//returns an integer and takes to characters as arguments, the function will use the two characters as upper and lower bounds for what it should be allowed to display
        int load();//returns an integer and takes no arguments, load function takes data from the CS_term.txt external file and uses the insert function to place it in the BST
    private:
        node * root;
        int insert(node *& root, info to_add);//recursive portion of insert, returns integer and takes a node poitner and info object as argument
        int remove(node *& root, info match);//recursive portion of remove, returns an integer and takes a node pointer and info object as argument
        node * inorder_successor(node *& root);//returns a pointer to a node and takes a node pointer as an argument, this function will find the inorder successor of the data soon to be deleted
        int retrieve(node *& root, info &match);// returns and integer and takes a node pointer and info object as arguments, this is the recursive portion of retrieve
        int get_height(node * root);//recursive portion of get height function, returns and int and takes a node pointer as an argument
        int is_efficient(node * root, int &efficient);//recursive portion of is_efficient, returns an int, and takes a node pointer and integer as arguments
        int display_all(node * root);//recursive portion of display_all, returns an int and takes a node pointer as an argument
        int display_range(node * root, char lower, char upper);//recursive portion of display_range, returns an int and takes a node pointer and two characters as arguments
        int remove_all(node *& root);//recursive function called from the destructor to remove all nodes in the BST when it goes out of scope, returns an int and takes a node pointer as an argument.

};
