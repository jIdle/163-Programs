/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * 2/20/2017
 *
 * This file, main.cpp, will act as the client for the table abstraction created in table.cpp and table.h
 */

/*
 * The purpose of this assignment is to create an array of linear linked lists with chaining collision resolution.
 * Each node will hold datatypes pokemon, region, and general which all hold different data about the pokemon world.
 * This will be the first Table ADT we are working with. The program will be able to insert, edit, remove, and
 * retrieve data from the hash table, alongside this, the program should be able to load data into the hash table
 * from an external data file.
 */

#include "table.h"

using namespace std;

int main()
{
    table my_table;
    pokemon * poke_main = NULL;
    region * reg_main = NULL;
    general * gen_main = NULL;

    char user_key[100]; int user_input;
    char bg[1000]; char evo[100];
    int candy; char color[100];
    char pia[1000]; int tia;
    char info[5000];

    if(!my_table.load())//checking if load from external file failed or succeeded
    {
        cout << "Load from file has failed." << endl;
    }

    while(user_input != 4)//while loop that keeps user in the interface that interacts with the hash table
    {    
        //options for the user to choose to navigate porgrsm
        cout << "\nEnter the number associated with the option you would like to choose:\n " << endl;
        cout << "1. Search for information" << endl;
        cout << "2. Add additional information" << endl;
        cout << "3. Remove information" << endl;
        cout << "4. Exit" << endl;//exit program
        cin >> user_input; cin.ignore(100, '\n');
        cout << endl;

        if(user_input == 1)//if user chooses the first option
        {
            cout << "Enter the term you would like to find information for:\n " << endl;
            cin.get(user_key, 100, '\n'); cin.ignore(100, '\n');//catch user input
            cout << endl;

            int length = strlen(user_key);//store length of input
            for(int i = 0; i < length; ++i)//make the string all lowercase
            {
                user_key[i] = tolower(user_key[i]);
            }
            //set all of the pointers to NULL so that nothing carries over from previous searches
            poke_main = NULL;
            reg_main = NULL;
            gen_main = NULL;

            if(my_table.retrieve(user_key, poke_main, reg_main, gen_main))//check if retrieve is succesful with given keyword
            {
                if(poke_main)//check if data returned from retrieve function is not NULL
                {
                    if(!poke_main->display())//display the data if it exists
                    {
                        cout << "Display was unsuccesful" << endl;
                    }
                }
                else if(reg_main)//check if data returned from retrieve function is not NULL
                {
                    if(!reg_main->display())//display data if it exists
                    {
                        cout << "Display was unsuccesful" << endl;
                    }
                }
                else if(gen_main)//check if data returned from retrieve function is not NULL
                {
                    if(!gen_main->display())//display data if it exists
                    {
                        cout << "Display was unsuccesful" << endl;
                    }
                }
            }
            else
            {
                cout << "Term was not found." << endl;
            }
        }
        else if(user_input == 2)//if user chooses the second option
        {
            cout << "\nEnter the term you would like to add information to:\n" << endl;
            cin.get(user_key, 100, '\n'); cin.ignore(100, '\n');//catch user's search term
            cout << endl;
    
            int length = strlen(user_key);//find length of search term
            for(int i = 0; i < length; ++i)//make sure search term is all lowercase
            {
                user_key[i] = tolower(user_key[i]);
            }

            cout << "\nEnter the number associated with the type of information you will add:\n" << endl;
            cout << "1. Pokemon related information\n2. Region related information\n3. General information" << endl;//user options
            cin >> user_input; cin.ignore(100, '\n');//catch user's input
            
            if(user_input == 1)//if user chooses 1st option
            {    
                //allow user to enter data for the soon to be inserted pokemon datatype
                cout << "Enter background information about pokemon:\n" << endl;
                cin.get(bg, 1000, '\n'); cin.ignore(100, '\n');
                cout << "Enter the pokemon that this one will evolve into:\n" << endl;
                cin.get(evo, 100, '\n'); cin.ignore(100, '\n');
                cout << "Enter the color of the pokemon:\n" << endl;
                cin.get(color, 100, '\n'); cin.ignore(100, '\n');
                cout << "Enter number of candies for the pokemon to evolve:\n" << endl;
                cin >> candy; cin.ignore(100, '\n');
                if(my_table.poke_insert(user_key, bg, evo, candy, color))//check if insert function was succesful
                {
                    cout << "Insert was succesful" << endl;
                }
            }
            else if(user_input == 2)//if user chooses 2nd option
            {
                //allow uuser to enter data for the soon to be inserted region datatype
                cout << "Enter pokemon found in area. Entry should be done on one line with commas separating the pokemon:\n" << endl;
                cin.get(pia, 100, '\n'); cin.ignore(100, '\n');
                cout << "Enter the number of different types of pokemon:\n" << endl;
                cin >> tia; cin.ignore(100, '\n');
                if(my_table.reg_insert(user_key, pia, tia))//check if insert function was succesful
                {
                    cout << "Insert was succesful" << endl;
                }
            }
            else if(user_input == 3)//if user chooses 3rd option
            {
                //allow user to enter data for the soon to be inserted general datatype
                cout << "Enter information about term:\n" << endl;
                cin.get(info, 100, '\n'); cin.ignore(100, '\n');
                if(my_table.gen_insert(user_key, info))//check if insert function was succesful
                {
                    cout << "Insert was succesful" << endl;
                }
            }
            else//entry was not 1 or 2 or 3
            {
                cout << "Invalid entry. Plese choose from the options listed.\n" << endl;
            }
        }
        else if(user_input == 3)//if user chooses the third option
        {
            cout << "Enter the term you world like to delete:\n" << endl;
            cin.get(user_key, 100, '\n'); cin.ignore(100, '\n');//catch search term
            if(!my_table.remove(user_key))//check to see if removal function was a success or failure
            {
                cout << "Removal unsuccesful. Make sure to spell it correctly." << endl;
            }
            else
            {
                cout << "Succesful removal." << endl;
            }
        }
        else if(user_input != 4)//if user chooses to exit the program
        {
            cout << "Invalid entry. Please choose from the options listed.\n" << endl;
        }
    }
    return 0;
}
