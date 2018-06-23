/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * 2/20/2017
 *
 * This file, table.cpp, will be for the functions found in table.h
 */

#include "table.h"

using namespace std;
//Constructor for the node struct. Declare all the data members of the struct to NULL or 0
node::node()
{
    keyword = NULL; //set the char pointer keyword to NULL
    poke_info = NULL; //set the pokemon pointer to NULL
    reg_info = NULL; //set the region pointer to NULL
    gen_info = NULL; //set the general pointer to NULL
    next = NULL; //set the node pointer next to NULL
}
//Destructor for the node struct. Delete all the dynamic memory in the struct 
node::~node()
{
    if(keyword) //if keyword exist 
    {
        delete [] keyword; //delete keyword
        keyword = NULL; //set it to NULL
    }

    if(poke_info) //if pokemon info pointer exist
    {
        delete poke_info; //Delete pokemon info
        poke_info = NULL; //Set pokemon info to NULL 
    }
    if(reg_info) //if region info exist 
    {
        delete reg_info; //delete region info
        reg_info = NULL; //set it to NULL
    }
    if(gen_info) //if general info exist
    {
        delete gen_info; //delete general info 
        gen_info = NULL;//set it to NULL
    }
}
//Constructor to declare all  the data members of the table class
table::table()
{
    SIZE = 23; //set the SIZE to 23
    hash_table = new node*[SIZE]; //Dynamically allocate the the hash table(array of node pointer) to size
    for(int i = 0; i < SIZE; ++i)//loop through and set all the array index to NULL
    {
        hash_table[i] = NULL;//set it to NULL 
    }
}
//Destructor to delete all the dynamic memory 
table::~table()
{ //loop through and delete nodes in each index
    for(int i = 0; i < SIZE; ++i)
    {
        if(hash_table[i])
        {
            clear(hash_table[i]); //call clear to delete the nodes of the LLL
        }
    }
    SIZE = 0; //set the size 0
}
//this function delete's all the nodes in the LLL
int table::clear(node *& head)
{
    if(!head) //if head doesn't exist 
    {
        return 1; //return 1
    }
    
    int x = clear(head->next); //do the recursive call 

    delete head; //delete head 
    head = NULL;//set head to NULL
    return x;//return the function call
}

//This function will load data from the three external data files listed below. the function will return a integer value
//and takes no arguments. first the pokemon data file will be opened and looped through, then the region data file will
//be opened and looped through, finally the general data file will be opened and looped through. each loop will take the
//data of the chosen line and store it in the hash table. data is stored in the hash table by calling the appropriate insert functions.
int table::load()
{
    //loading external files
    ifstream poke_in; poke_in.open("CS163_pokemon.txt");
    ifstream gen_in; gen_in.open("CS163_general.txt");
    ifstream reg_in; reg_in.open("CS163_region.txt");
    
    //creating temporary variables to receive data from the external file
    char temp_keyword[100]; char temp_background[1000];
    char temp_evolution[100]; int temp_candies = 0;
    char temp_color[100]; char temp_PIA[1000];
    int temp_TIA = 0; char temp_information[5000];
    int return_val = 0;// this is a temporary int to hold a value to be returned at the end of the function

    while(!poke_in.eof())//while loop to continuously store and insert data from the external file, into the hash table, until end of file.
    {
        poke_in.get(temp_keyword, 100, ':');//storing the keyword associated with this data.
        poke_in.ignore(100, ':'); 
        poke_in.get(temp_background, 1000, ':');//storing background information
        poke_in.ignore(100, ':'); 
        poke_in.get(temp_evolution, 100, ':');//storing the pokemon evolution
        poke_in.ignore(100, ':'); 
        poke_in >> temp_candies;//storing number of candies needed for evolution
        poke_in.ignore(100, ':');
        poke_in.get(temp_color, 100, '\n');//storing color of pokemon
        poke_in.ignore(100, '\n');
        if(poke_insert(temp_keyword, temp_background, temp_evolution, temp_candies, temp_color))//inserting all of the data gathered above into the hash table
        {
            return_val = 1;//if the insert succeeds, then the return value is changed to 1
        }
    }
    while(!reg_in.eof())//while loop to continuously store and insert data from the external file, into the hash table, until end of file.
    {
        reg_in.get(temp_keyword, 100, ':');//storing the keyword associated with this data
        reg_in.ignore(100, ':');
        reg_in.get(temp_PIA, 1000, ':');//storing the names of the pokemon found in it's associated region
        reg_in.ignore(100, ':');
        reg_in >> temp_TIA;//storing the number of pokemon found in this area
        reg_in.ignore(100, '\n');
        if(reg_insert(temp_keyword, temp_PIA, temp_TIA))//inserting all of the data gathered above into the hash table
        {
            return_val = 1;//if the insert was successful then the return value will be changed to 1
        }
    }
    while(!gen_in.eof())//while loop to continuously store and insert data from the external file, into the hash table, until end of file.
    {
       gen_in.get(temp_keyword, 100, ':');//storing the keyword associated with this data
       gen_in.ignore(100, ':');
       gen_in.get(temp_information, 5000, '\n');//storing general information about the keyword
       gen_in.ignore(100, '\n');
       if(gen_insert(temp_keyword, temp_information))//inserting the data gathered above into the hash table
       {
           return_val = 1;//if insert was successful then the return value will be changed to 1
       }
    }
    return return_val;//return whatever return_val is set to
}

//poke_insert function is made to specifically insert a pokemon class into the hash table. poke_insert returns an int and takes as argument all private data members of pokemon class
int table::poke_insert(char * keyword, char * background, char * evolution, int candies, char * color)
{
    int index = hash_function(keyword);//getting index of keyword for hash table using the hash function
    
    if(hash_table[index] && !strcmp(keyword, hash_table[index]->keyword))//if a node exists and the keyword in that node is the same as the keyword we are inserting, delete the data to replace it
    {
        node * alt = hash_table[index]->next;
        delete hash_table[index];
        hash_table[index] = alt;
    }

    //below this is the inserting process for data into a hash table
    node * temp = new node;
    temp->poke_info = new pokemon;

    temp->keyword = new char[strlen(keyword) + 1];
    strcpy(temp->keyword, keyword);
    temp->poke_info->create(background, evolution, candies, color);//calling the create function on the pokemon pointer inside the node to add the data we've collected from the ext. file

    //below this is making sure that our newest addition is at the head of the LLL
    temp->next = hash_table[index];
    hash_table[index] = temp;
    return 1;
}

//this is the same process as with poke_insert, the data gather from the ext. file is going to be inserted into the hash table
int table::reg_insert(char * keyword, char * PIA, int TIA)
{
    int index = hash_function(keyword);
    
    if(hash_table[index] && !strcmp(keyword, hash_table[index]->keyword))
    {
        node * alt = hash_table[index]->next;
        delete hash_table[index];
        hash_table[index] = alt;
    }

    node * temp = new node;
    temp->reg_info = new region;

    temp->keyword = new char[strlen(keyword) + 1];
    strcpy(temp->keyword, keyword);
    temp->reg_info->create(PIA, TIA);

    temp->next = hash_table[index];
    hash_table[index] = temp;
    return 1;
}

//this is the same process as with poke_insert, the data gathered from the ext. file is going to be inserted into the hash table
int table::gen_insert(char * keyword, char * information)
{
    int index = hash_function(keyword);

    if(hash_table[index] && !strcmp(keyword, hash_table[index]->keyword))
    {
        node * alt = hash_table[index]->next;
        delete hash_table[index];
        hash_table[index] = alt;
    }

    node * temp = new node;
    temp->gen_info = new general;

    temp->keyword = new char[strlen(keyword) + 1];
    strcpy(temp->keyword, keyword);
    temp->gen_info->create(information);

    temp->next = hash_table[index];
    hash_table[index] = temp;
    return 1;
}

//The remove function removes data matching the keyword handed into it. afterwards it will make sure the LLL remains linked up. returns an int and takes a char * as an argument
int table::remove(char * term_to_remove)
{
    int index = hash_function(term_to_remove);//finding index of keyword
    int return_val = 0;//creating a temp var to hold on to either 1 or 0 to return success fail out of the function
    if(index == -1)//if the index doesn't exist
    {
        return return_val;
    }
    node * temp = hash_table[index];
    node * previous = NULL;
    while(temp && strcmp(term_to_remove, temp->keyword))//this while loop will continue until either a match is found, or temp traverses off the end of the LLL into NULL
    {
        previous = temp;
        temp = temp->next;//traversal
    }
    if(temp)//if this if statement is triggered, that means that temp did not reach the end of the LLL and that the strcmp found a match.
    {
        return_val = 1;//match found, remove was a success
        if(hash_table[index] == temp)//this covers the case of the match being the head of the list
        {
            hash_table[index] = temp->next;
            delete temp;
        }
        else//covers all other cases
        {
            previous->next = temp->next;
            delete temp;
        }
    }
    return return_val;
}

//this function will return an int and receive pointers to, character, pokemon, region, general datatypes.
//retrieve will use the hash function to find the index for the given keyword, it will then try to verify
//whether or not this data exists. if it does not exist, then it will return 0 and not change its arguments.
//if the data does exist then it will determine which datatype (pokemon, region, general) is NOT NULL because
//in this way it can decide which datatype needs to be copied from and to.
int table::retrieve(char * title_to_find, pokemon *& poke_main, region *& reg_main, general *& gen_main)
{
    int index = hash_function(title_to_find);//finding index of keyword
    int return_val = 0;
    if(index == -1)//checks to see if index exists
    {
        return return_val;
    }
    node * temp = hash_table[index];
    while(temp && strcmp(title_to_find, temp->keyword))//this while loop will try to match the keywords, if there is no match then temp will hit NULL and stop
    {
        temp = temp->next;
    }
    if(temp)//this will trigger if there was a keyword match found because in this case temp will not be NULL
    {
        //below three checks are made to see which datatype holds data
        if(temp->poke_info)
        {
            poke_main = new pokemon;
            poke_main->copy(temp->poke_info);
        }
        else if(temp->reg_info)
        {
            reg_main = new region;
            reg_main->copy(temp->reg_info);
        }
        else if(temp->gen_info)
        {
            gen_main = new general;
            gen_main->copy(temp->gen_info);
        }
        return_val = 1;
    }
    return return_val;
}

//this function (hash_function) returns an int and receives a character pointer which will be the term that the user enters to look for
//the point of this function is to pick a seemingly random index in the hash table based off of the ASCII values of the string given
int table::hash_function(char * key)
{
    int sum = 0;
    if(!key)//if pointer is NULL
    {
        return -1;//return an index that does not exist
    }
    int length = strlen(key);
    for(int i = 0; i < length; ++i)//add the ASCII values of the string's characters together
    {
        sum += *(key + i);
    }
    return (sum % SIZE);// mod the value received above to get a value within the range of the hash table index
}
