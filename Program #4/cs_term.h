/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Assignment #4
 *
 * This file (cs_term.h) will hold the info class.
 */

//Libraries included
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>

//info class will hold all of the information about each computer science term that is added to the BST
class info
{
    public:
        info();//constructor
        ~info();//destructor
        int copy(info to_copy);//takes info class as argument an returns an int, will copy the info object handed to it
        int create(char * title_to_copy, char * definition_to_copy);//takes two character pointers as argument andreturns an int, create function will dynamically allocate the title and definition handed to it and set them to the calling object's data members
        int compare(info to_compare);//takes info object as argument and returns an int, compare function will check to see if the handed info object's title is less, more, or equal to the calling info object's title
        int display(char upper, char lower);//takes two characters as arguments, returns an int, display function will simply cout both title and definition if they exist
        int clear();//clear function does pretty much the same thing as the destructor, it is used to make sure that the temporary info object used in main doesn't have data left over.
    private:
        char * title;//this is the CS term, it is a pointer to a character array 
        char * definition;//this is the explanation of the CS term, it is a pointer to a character array
};
