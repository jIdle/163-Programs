/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Assignment #4
 *
 * This file (main.cpp) will act as the client in this program.
 *
 * The purpose of this program is to experience building a Binary Search Tree. This program contains 
 * functionality to insert data, remove data, load data from an external file, find the height of the BST,
 * determine whether the tree is efficient, display all data alphabetically, and display data in a range of values.
 */

#include "BST_header.h"

using namespace std;

int main()
{
    info cs_term;
    tree my_tree;
    int user_option = 0;
    char title[100];
    char definition[1000];
    int length = 0;

    while(user_option != 8)
    {
        cout << "Enter the number adjacent to the option you would like to choose:" << endl;
        cout << " 1. Insert data\n 2. Remove data\n 3. Search data\n 4. Get height of tree\n 5. Get efficiency of tree\n 6. Display all data alphabetically\n 7. Display all data through a set range\n 8. Exit\n" << endl;
        cin >> user_option; cin.ignore(100, '\n'); cout << endl;

        if(user_option == 1)
        {
            cout << "\nEnter the CS term you would like to add: ";
            cin.get(title, 100, '\n'); cin.ignore(100,'\n'); cout << endl;
            cout << "\nEnter the definition of this CS term: ";
            cin.get(definition, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            length = strlen(title);
            for(int i = 0; i < length; ++i)
            {
                title[i] = tolower(title[i]);
            }
            cs_term.create(title, definition);
            if(!my_tree.insert(cs_term))
            {
                cout << "Insert function failed.\n" << endl;
            }
            else
            {
                cout << "Term has been added.\n" << endl;
            }
            cs_term.clear();
        }
        else if(user_option == 2)
        {
            cout << "Enter the term you would like to remove: ";
            cin.get(title, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            length = strlen(title);
            for(int i = 0; i < length; ++i)
            {
                title[i] = tolower(title[i]);
            }
            cs_term.create(title, "placeholder");
            if(!my_tree.remove(cs_term))
            {
                cout << "Remove function failed.\n" << endl;
            }
            else
            {
                cout << "Data succesfully removed.\n" << endl;
            }
        }
        else if(user_option == 3)
        {
            cout << "Which term would you like to search for: ";
            cin.get(title, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            length = strlen(title);
            for(int i = 0; i < length; ++i)
            {
                title[i] = tolower(title[i]);
            }
            cs_term.create(title, "placeholder");
            if(my_tree.retrieve(cs_term))
            {
                cs_term.display(96, 123); cout << endl;
            }
            else
            {
                cout << "Specified data was not found.\n" << endl;
            }
            cs_term.clear();
        }
        else if(user_option == 4)
        {
            int height = my_tree.get_height();
            if(!height)
            {
                cout << "Get height function failed.\n" << endl;
            }
            else
            {
                cout << "Height of tree is: " << height << endl;
            }
        }
        else if(user_option == 5)
        {
            if(!my_tree.is_efficient())
            {
                cout << "Tree is not balanced.\n" << endl;
            }
            else
            {
                cout << "Tree is balanced." << endl;
            }
        }
        else if(user_option == 6)
        {
            if(!my_tree.display_all())
            {
                cout << "Display all function failed.\n" << endl;
            }
        }
        else if(user_option == 7)
        {
            char lower;
            char upper;
            cout << "Enter a range to be displayed. (Ex: L <enter> Y <enter>):" << endl;
            cin >> lower; cin.ignore(100, '\n');
            lower = tolower(lower);
            cin >> upper; cin.ignore(100, '\n');
            upper = tolower(upper);
            cout << endl;
            if(!my_tree.display_range(lower, upper))
            {
                cout << "Display range function failed.\n" << endl;
            }
        }
        else if(user_option == 8)
        {
            cout << "Program will now exit." << endl;
        }
        else
        {
            cout << "Invalid entry. Please enter a listed option number." << endl;
        }
    }
    return 0;
}
