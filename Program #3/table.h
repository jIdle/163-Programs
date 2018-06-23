/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * 2/20/2017
 *
 * This file, table.h, will hold the table class, the node struct, and the function prototypes for this assignment
 */

#include "pokemon_info.h"

//The node struct will hold pointers to: the pokemon class, the region class, and the general. 
//Only one of them will hold information in any one node. Meaning, if an insert has been done
//and the data that has been inserted is of pokemon type, the other will be NULL. This was the
//they were made as pointers. The node will also hold a character pointer which will be used to
//match data being looked for with data that has already been inserted into the hash table. To 
//take care of the dynamic allocation that happens with pointers, a destructor and constructor
//have been included.
struct node
{
    node(); //constructor
    ~node(); //destructor
    char * keyword; //the search term the user wants to look for
    pokemon * poke_info; //pointer to a pokemon datatype, defined in pokemon_info.h
    region * reg_info; //pointer to a region datatype, defined in pokemon_info.h
    general * gen_info; //pointer to a general datatype, defined in pokemon_info.h
    node * next; //next pointer
};

//The table class will define the functionality of our ADT. It will include private data members
//such as: the array of linear linked lists that will make up our hash_table, an int that will keep
//track of how large the array is, and a hash function for finding the index of a search term.
//Along with this come the functionality to load from an external file, remove, insert, and retrieve.
class table
{
    public:
        table(); //constructor
        ~table(); //destructor
        int load(); //loads data from an external file into the hash table, returns and int, no parameter
        int remove(char *); //removes a given entry from the hash table, returns an int, char * parameter for term to remove 

        //finds and returns through argument the data associated with a given search term, returns an int, char * parameter
        //is for the search term to be compared against the keyword inside each node, pokemon, region, and general pointer
        //parameters allow the function to return data through the argument because they were passed by reference.
        int retrieve(char *, pokemon *&, region *&, general *&); 

        int poke_insert(char *, char *, char *, int, char *); //the specific insert used to handle the pokemon datatype,
                                                              //returns an int, parameters will match the data members of pokemon
        int reg_insert(char *, char *, int); //the specific insert used to handle the region datatype, returns int,
                                             //parameters will match data members of region
        int gen_insert(char *, char *); //the specific insert used to handle the general datatype, returns an int,
                                        //parameters will match data members of general
    private:
        int clear(node *& head); //used inside the destructor to clear LLL if it exists at each index in the hash table. returns int, and parameter includes a node pointer
        int hash_function(char *); //returns int and parameter consists of character pointer, takes search term and creates index based on the search term's ASCII values.
        node ** hash_table; //an array of node pointers, this is the program's hash table which is used to store pokemon, region, and general data types.
        int SIZE; //int datatype, keeps track of the size of the array of node pointers
};
