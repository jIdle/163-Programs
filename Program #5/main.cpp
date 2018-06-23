/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Program #5
 * 3/15/2017
 *
 * This file (main.cpp) will act as the client side for this program.
 *
 * The purpose of this program is to get experience using the graph ADT in our program and
 * gain a better understanding of the Depth First Search taught in lecture and in the Carrano textbook.
 * The graph class created in this program is expected to be able to insert edges, insert vertices,
 * display adjacent vertices of a specified vertex, and display the longest path from a specified vertex.
 */

#include "graph_header.h"

using namespace std;

int main()
{
    int temp_size = 0;//temporary integer variable used to store user input concerning size of the vertex array
    cout << "\nDeclare size of vertex array: ";
    cin >> temp_size; cin.ignore(100,'\n'); cout << endl;

    table graph(temp_size);//declaring the graph object and giving it the size specified by the user to set the size of the vertex area by constructor
    int user_option = 0;//integer variable used to allow user to choose options in menu
    char name1[100];//temp char array to hand variables into functions
    char name2[100];//temp char array to hand variables into functions
 
    while(user_option != 5)
    {
        //menu for user
        cout << "1. Insert Vertex\n2. Insert Edge\n3. Display Adjacent Vertices\n4. Display Longest Path\n5. Exit\n" << endl;
        cout << "Enter the number associated with the option you would like to choose: ";
        cin >> user_option; cin.ignore(100,'\n'); cout << endl;

        if(user_option == 1)//if user chooses insert vertex as option
        {
            cout << "Enter the name of the vertex you would like to enter: ";//user entering name of vertex
            cin.get(name1, 100, '\n'); cin.ignore(100, '\n'); cout << endl;

            if(!graph.insert_vertex(name1))//check if function succceeds
            {
                cout << "Failed to insert vertex.\n" << endl;
            }
        }
        else if(user_option == 2)//if user chooses insert edge as option
        {
            cout << "Enter the name of the vertex you would like to make a connection FROM (outgoing): ";//user entering names of vertices they want to connect with an edge
            cin.get(name1, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            cout << "Enter the name of the vertex you would like to make a connection TO (incoming): ";
            cin.get(name2, 100, '\n'); cin.ignore(100, '\n'); cout << endl;

            if(!graph.insert_edge(name1, name2))//check if function succeeds
            {
                cout << "Failed to insert edge.\n" << endl;
            }
        }
        else if(user_option == 3)//if user chooses display adjacent vertices as option
        {
            cout << "Enter the name of the vertex you would like to see adjacents of: ";//user entering name of vertex that adjacents of should be displayed
            cin.get(name1, 100, '\n'); cin.ignore(100, '\n'); cout << endl;

            if(!graph.display_adjacent(name1))//check if function succeeds
            {
                cout << "Failed to display adjacent vertices.\n" << endl;
            }
        }
        else if(user_option == 4)//if user chooses display longest path 
        {
            cout << "Enter the name of a vertex, the longest path from this vertex will be displayed: ";//user entering name of vertex that longest path from should be displayed
            cin.get(name1, 100, '\n'); cin.ignore(100, '\n'); cout << endl;
            
            int path_count = graph.longest_path(name1);//catching return value from this function, which should how long the longest path is, in terms of vertices
            
            cout << "\nLength of longest path is: " << path_count << " vertices long" <<  endl;//outputs length of path
            cout << "Appropriately read from bottom to top." << endl;
            graph.reset();
        }
        else if(user_option == 5)//user chooses to exit the program
        {
            cout << "Program will now exit." << endl;
        }
        else//user entered a number that was not given as an option in the menu
        {
            cout << "Invalid entry. Please choose from the displayed option.\n" << endl;
        }
    }

    return 0;
}
