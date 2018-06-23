/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * 2/20/2017
 *
 * This file, pokemon_info.h, will hold the classes for the different types of pokemon data
 * being pokemon related data, region related data, and genereal related data.
 */
// header files 
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <fstream>

//Class which holds specific information about the pokemon
class pokemon
{
    public:
        pokemon(); //constructor 
		~pokemon(); //destructor 
        int create(char *, char *, int, char *); //This function set data with what's passed in into the function
												//return value is int, it's taking in three character pointers and an integer  
        int copy(pokemon *); //This function is a copy function that takes in pokemon pointer and perform a deep copy
								//returns an int
        int display(); //This function will display all the pokemons information. returns an int 

    private:
        char * background_info; //Hold's background information 
        char * evolution; //hold's evolution information
        int candy; //Hold's how many candy it needs to evolve the pokemon
        char * color; //Hold's the colour of the pokemon 
};
//This class holds region information about the pokemon
class region
{
    public:
        region(); //constructor
        ~region(); //destructor
        int create(char *, int); //This function set data with what's passed in into the function
									//return value is int, it's taking in one character pointer and an integer
        int copy(region *); //This function is a copy function that takes in region pointer and perform a deep copy
        int display(); //This function will display all the pokemons information. returns an int

    private:
        char * pokemon_in_area; //Holds all of the pokemon's in that region  
        int number_of_types;  //Hold's how many type of pokemon's are in that region
};
//This class holds general information about the pokemon
class general
{
    public:
        general(); //constructor
        ~general(); //destructor
        int create(char *);//This function set data with what's passed in into the function
							//return value is int, it's taking in one character pointer
        int copy(general *); //This function is a copy function that takes in general pointer and perform a deep copy. 
        int display(); //This function will display all the pokemon's
    private:
        char * information; //Hold's information about the term 
};
