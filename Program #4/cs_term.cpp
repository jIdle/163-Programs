/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Assignment #4
 *
 * This file (cs_term.cpp) will hold the function definitions for its header file (cs_term.h)
 */

#include "cs_term.h"

using namespace std;

info::info()
{
    title = NULL; //making sure title isn't set to garbage on creation
    definition = NULL;//making sure definition isn't set to garbage on creation
}

info::~info()
{
   // if(title)
   // {
   //     delete [] title;
   //     title = NULL;
   // }
   // if(definition)
   // {
   //     delete [] definition;
   //     definition = NULL;
   // }
}

//copy function just uses the create function but allows an object to be taken instead of the individual variables
int info::copy(info to_copy)
{
    if(create(to_copy.title, to_copy.definition))//simultaneously using the create function and checking to see if it was succesful
    {
        return 1;//it worked
    }
    return 0;//it didn't worked
}

int info::create(char * title_to_add, char * definition_to_add)//takes a CS term and a definition for it and dynamically allocates them and sets them
{
    if(title_to_add && definition_to_add)//checks to see if both handed in actually exist
    {
        title = new char[strlen(title_to_add) + 1];//allocating memory space
        strcpy(title, title_to_add);//copying it into calling object
        definition = new char[strlen(definition_to_add) + 1];//allocating memory for the definition
        strcpy(definition, definition_to_add);//copying it over to calling object
        return 1;//the copying process was successful
    }
    return 0;//copying did not succeed
}

int info::compare(info compare)//compare function checks to see if the title of the info object that was handed in is less, more, or equal to the title of the calling object
{
    if(strcmp(title, compare.title) < 0)//is the title less than
    {
        return 1;
    }
    else if(strcmp(title, compare.title) > 0)//is the title greater than
    {
        return 2;
    }
    return 0;//title matched
}

int info::display(char lower, char upper)//displays the title and definition of the calling info object for all range of ascii values
{
    if(title[0] >= lower && title[0] <= upper)//entire rannge of ascii values
    {
        cout << "Title: " << title << endl;
        cout << "Definition: " << definition << endl;
    }
    return 1;//display was succesful
}

int info::clear()//clear function literally does the same thing as the destructor, I just wasn't sure if calling the destructor was ok
{
    if(title)//check if exists
    {
        delete [] title;//if so delete and set to NULL
        title = NULL;
    }
    if(definition)
    {
        delete [] definition;
        definition = NULL;
    }
    return 1;
}
