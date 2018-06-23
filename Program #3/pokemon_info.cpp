/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * 2/20/2017
 *
 * This file, pokemon_info.cpp, will hold all of the functions for the classes in file pokemon_info.h 
 */

#include "pokemon_info.h"

using namespace std;
//constructor 
pokemon::pokemon()
{
    background_info = NULL; //set char pointer background_info to NULL
    evolution = NULL; //set char pointer evolution to NULL
    candy = 0; //set int candy to zero
    color = NULL; //set char pointer color to NUL
}
//Destructor
pokemon::~pokemon()
{
    if(background_info) //if char pointer background_info exist  
    {
        delete [] background_info; //delete it
    }
    if(evolution) //if char pointer evolution exist
    {
        delete [] evolution; //delete it
    }
    if(color) //if char pointer colour exist 
    {
        delete [] color; //delete it 
    }
    candy = 0; //set int candy to zero
}
//This function takes in the char * background_in, char * evolution_in, int candy_in and char * color_in entered by the user, dynamically allocates them,
//and then stores them in the appropriate variables in the class
int pokemon::create(char * background_in, char * evolution_in, int candy_in, char * color_in)
{ 
	//Dynamically allocates and copies the background_in entered by the user into the background_info
	//variable in the class.
    background_info = new char[strlen(background_in) + 1]; 
    strcpy(background_info, background_in);
	//Dynamically allocates and copies the evolution_in entered by the user into the evolution variable in the class
    evolution = new char[strlen(evolution_in) + 1];
    strcpy(evolution, evolution_in);
	//Dynamically allocates and copies the colour_in entered by the user into the color varaible in the class
    color = new char[strlen(color_in) + 1];
    strcpy(color, color_in);
    candy = candy_in; //set candy to candy_in entered by the user
    return 1;
}
//This function perform a deep copy on object of pokemon * poke_in passed in
int pokemon::copy(pokemon * poke_in)
{
	//calls the create function and passes in call the data members of the pokemon class  
    if(create(poke_in->background_info, poke_in->evolution, poke_in->candy, poke_in->color))
    {
        return 1; 
    }
    else //otherwise return 0
    {
        return 0;
    }
}
//Display all the data members of the pokemon class
int pokemon::display()
{
    int return_val = 0; //Holds the return value
    if(background_info || evolution || color || candy != 0) //  the data members are not 0
    {
        return_val = 1; //return 1
    }
    if(background_info)
    {
        cout << "Background information: \n\n\t" << background_info << endl << endl; //print the background information of the pokemon
    }
    if(evolution)
    {
        cout << "Evolves into: " << evolution << endl; //display evolution information of the pokemon
    }
    if(color)
    {
        cout << "Color is: " << color << endl; //display the color of the pokemon
    }
    if(candy != 0) //if the candy is not equal to 0
    {
        cout << "Candies required for evolution: " << candy << endl; //print this error message
    }
    return return_val; //return 0 or 1
}
//constructor which declares all the data members
region::region()
{
    pokemon_in_area = NULL; //set the char pointer pokemon in area to NULL
    number_of_types = 0; //set the integer number_of_types to 0
}
//Deallocate the memory 
region::~region()
{
    if(pokemon_in_area) //if char * pokemon in the area exist 
    { 
        delete [] pokemon_in_area; //delete the pokemon in the array char pointer
    }

    number_of_types = 0; //set the integer number of integer to 0
}
//This function takes in char * area_in and integer types_in and dynamically allocates them,
//and then stores them in the appropriate variables in the class
int region::create(char * area_in, int types_in)
{   //Dynamically allocates and copies the area_in entered by the user into the pokemon_in_area
	//variable in the class.
    pokemon_in_area = new char[strlen(area_in) + 1];
    strcpy(pokemon_in_area, area_in);
	//set number_of_types to the types_in entered by the user
    number_of_types = types_in;
    return 1;
}
//Perform a deep copy on the region pointer.
int region::copy(region * region_in)
{ //calls the create function and passes in call the data members of the region class
    if(create(region_in->pokemon_in_area, region_in->number_of_types))
    {
        return 1; //return 1
    }
    else //otherwise return 0
    {
        return 0;
    }
}
//Display all the data members of region class if it exist
int region::display()
{
    int return_val = 0;
    if(pokemon_in_area || number_of_types != 0) //if the value of the data member is not 0 set the return value to 1
    {
        return_val = 1;
    }
    if(pokemon_in_area)
    {
        cout << "The types of pokemon in this area are:\n\n\t" << pokemon_in_area << endl << endl; //Print pokemon in the area 
    }
    if(number_of_types != 0)
    {
        cout << "The number of pokemon types in this area are: " << number_of_types << endl; //print how many types of poekemons exist
    }
    return return_val; //return 1 or 0 
}
//Constructor to set the data member to 0 ot NULL
general::general()
{
    information = NULL; //set the char pointer information to NULL
}
//Delete all the dynamic memory 
general::~general()
{
    if(information) //if the char pointer information is not NULL
    {
        delete [] information; //delete the char pointer information 
    }
}
//This function takes in char * information_in and dynamically allocates them,
//and then stores them in the appropriate variables in the class
int general::create(char * information_in)
{ //Dynamically allocates and copies the information_in entered by the user into the information
    information = new char[strlen(information_in) + 1];
    strcpy(information, information_in);
    return 1;
}
//Perform a deep copy on the general pointer.
int general::copy(general * general_in)
{ //calls the create function and passes in call the data members of the general class
    if(create(general_in->information))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//Display all the data member of general class
int general::display()
{
    int return_val = 0;
    if(information) //If char pointer information exist 
    {
        return_val = 1; //Set the return value to 1
        cout << "General information about this term: \n\n\t" << information << endl; //Print the char pointer information
    }
    return return_val; //Return 1 or 0
}
