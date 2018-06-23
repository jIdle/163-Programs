/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Program #5
 * 3/15/2017
 *
 * This file (main.cpp) will act as the client side for this program.
 */

#include "graph_header.h"

using namespace std;

//constructor for table class, the argument it takes it used for setting the size of the vertex array
table::table(int size)
{
    list_size = size;//storing size of array

    //dynamically allocating memory for an integer array that will be the same size as the vertex array
    //is used later for keeping track of which nodes have been visited during the DFS
    visited = new int[list_size];
    display_visited = new int [list_size];
    
    //setting the array slots to zero
    for(int i = 0; i < list_size; ++i)
    {
        visited[i] = 0;
        display_visited[i] = 0;
    }

    //dynamically allocating memory for the vertex array used to create the graph
    adjacency_list = new vertex[list_size];

    //setting data inside vertices to NULL
    for(int i = 0; i < list_size; ++i)
    {
        adjacency_list[i].head = NULL;
        adjacency_list[i].name = NULL;
    }
}

//removing all vertices and edges in the graph
table::~table()
{
   remove_all(); 
}

//insert_vertex function dynamically allocates memory for the given name of the vertex
//to do this it searches the existing array for the first open spot
int table::insert_vertex(char * name)
{
    for(int i = 0; i < list_size; ++i)
    {
        if(!adjacency_list[i].name)//check for first free slot in array
        {
            adjacency_list[i].name = new char[strlen(name) + 1];//allocate memory for vertex name
            strcpy(adjacency_list[i].name, name);//copy given name into vertex
            return 1;
        }
    }
    return 0;
}

//insert_edge function takes two character pointers from the client, with those two names
//it will determine if they exist by finding the index. once the index of the two vertices
//have been found, they are linked up a newly created edge. the first vertex's node pointer
//will be set to the edge, and the edges vertex pointer is set to the second node.
int table::insert_edge(char * current_vertex, char * to_attach)
{
    int edge_from = find_location(current_vertex);//finding index of the first vertex
    int edge_to = find_location(to_attach);//finding index of the second vertex

    if(edge_from != -1 && edge_to != -1)//creation of edge will go through as long as both vertices exist
    {
        if(!adjacency_list[edge_from].head)//first case: first vertex currently does not have any connections
        {
            node * new_edge = new node;//create the edge
            new_edge->next = adjacency_list[edge_from].head;//set edge's next pointer to NULL
            adjacency_list[edge_from].head = new_edge;//set first vertex's node pointer to the new edge
            new_edge->adjacent = &adjacency_list[edge_to];//set edge's vertex pointer to the second vertex
            return 1;
        }
        node * new_edge = new node;//second case: first vertex does already have connections
        new_edge->next = adjacency_list[edge_from].head;//connect edge's node pointer up with other edges
        adjacency_list[edge_from].head = new_edge;//first vertex to edge
        new_edge->adjacent = &adjacency_list[edge_to];//edge to second vertex
        return 1;
    }
    return 0;
}


//find_location function is used to find the index of the specified vertex. the function
//accomplishes this by using a for loop to check every index for a matching char array
int table::find_location(char * key_value)
{
    for(int i = 0; i < list_size; ++i)//check every index
    {
        if(adjacency_list[i].name)//is there even a vertex in that slot
        {
            if(!strcmp(adjacency_list[i].name, key_value))//compare the handed string and the found string
            {
                return i;//return the index
            }
        }
    }
    return -1;//no match found
}

//this function takes a character array and uses a for loop to check for a match in the vertex array.
//if a match is found the function will iterate through the LLL of edges from the found vertex.
int table::display_adjacent(char * key_value)
{
    for(int i = 0; i < list_size; ++i)//check every index for the specified vertex
    {
        //are there any edges in the first place? and also have we found the correct vertex?
        if(adjacency_list[i].head && !strcmp(adjacency_list[i].name, key_value))
        {
            node * current = adjacency_list[i].head;//set current to the front of the edge LL
            int count = 1;//setting some arbitrary number to label the relationships

            while(current)//traverse through the LL of edges
            {
                //displaying edges
                cout << "Relationship #" << count << ": " << current->adjacent->name << endl << endl;
                ++count;
                current = current->next;//traversal
            }
            return 1;
        }
    }
    return 0;
}

//this is a wrapper function for the recursive function display_longest
//this will take a specified name from the user to find and place it's
//associated vertex into the recursive function
int table::longest_path(char * key_value)
{
    for(int i = 0; i < list_size; ++i)//check to see if specified vertex exists
    {
        //does this index contain a vertex and also if it does, do the names match?
        if(adjacency_list[i].name && !strcmp(adjacency_list[i].name, key_value))
        {
            return display_longest(&adjacency_list[i]);//call recursive function
        }
    }
    return 0;//match not found
}

//display_longest is a recursive function, it uses the recursive function longest path to complete its goal.
//longest path is used to determine which path-direction contains the longest path.
//each vertex that is reached, iteration will be used to call the longest_path function on every
//connecting vertex. the largest connection is always chosen to be handed to the new recursive call of
//the display_longest function. this continues until there are no more connection to be made, and then
//display_longest will display the path on the way back.
int table::display_longest(vertex * start)
{
    //does the vertex we traversed to exist? and if it does have we already visited it?
    if(!start || display_visited[find_location(start->name)] == 1)
    {
        return 0;
    }
 
    int path_length = 0;//variable to hold the length of a specified path
    int largest = 0;//variable to hold the length of only the longest path
    node * temp = start->head;//node pointer to hold onto the head of the edge list
    vertex * correct_path = NULL;//vertex pointer to hold onto the largest adjacent node
    display_visited[find_location(start->name)] = 1;//we have visited this vertex
   
    if(temp)//does the vertex we are in have any connections?
    {
        while(temp)//continue iteration until we are done looking at adjacent vertices
        {
            path_length = longest_path(temp->adjacent);//check path length of adjacent vertex
            if(path_length >= largest)//if that path length turns out to be the longest
            {
                correct_path = temp->adjacent;//remember which vertex led down the longest path
                largest = path_length;//remember how long the so-far longest path is
            }
            temp = temp->next;//traverse over adjacent vertices
        }
        visited[find_location(correct_path->name)] = 1;//tell longest_path function not to revisit vertices
        path_length = display_longest(correct_path);//recursive call down confirmed longest path
        cout << start->name << endl;//display this vertex because we know it is within the longest path
        return path_length + 1;
    }
    cout << start->name << endl;//display name of current vertex if it doesn't have any adjacent vertices
    return 1;
}

//this function will recursively find the longest path from a given vertex. it does so by recursing through
//each possible path, and when it hits the end of a path, it will increment it's return value on each return
//until the last multi-connection vertex (last vertex that had more than one choice in terms of paths. since
//the path length is returned to the last vertex with multiple path options, a comparison is done after all
//paths have been quantified to determine which path is the longest. this continuously happens on return to
//determine which path (coming back) has the greatest length.
int table::longest_path(vertex * start)
{
    //does the vertex exist? and also have we already visited this vertex?
    if(!start || visited[find_location(start->name)] == 1)
    {
        return 0;
    }

    int return_value = 0;//int var to store the return of the recursive call
    int largest = 0;//used in comparison of path lengths, will be set to the longest path after comparison
    node * temp = start->head;//beginning of edge list
    visited[find_location(start->name)] = 1;//we have visited the vertex in this frame
    while(temp)//check paths as long as paths exist
    {
        return_value = longest_path(temp->adjacent);//recursive call that leads to the smaller step
        if(return_value > largest)//check if the path length returned is longer than the previous one checked
        {
            largest = return_value;//assuming the above is true, a new largest path length is set
        }
        temp = temp->next;//traversal of edge list
    }
    visited[find_location(start->name)] = 0;//unvisit vertex so other path combinations retain all options
    return largest + 1;//return the length of the path including the vertex we are returning from
}

//function that graph will call to deallocate or dynamic memory
int table::remove_all()
{
    node * temp = NULL;
    node * current = NULL;

    for(int i = 0; i < list_size; ++i)//look at each index in the array
    {
        if(adjacency_list[i].name)//does a vertex exist in this index?
        {
            delete [] adjacency_list[i].name;//if it does, delete it's information
        }
        current = adjacency_list[i].head;//give the specified vertex's node pointer and easier name
        while(current)//while the edge list exists
        {
            temp = current;//hold onto previous node with temp pointer
            current = current->next;//have current move onto the next node, or NULL
            delete temp;//delete the previous node
            temp = NULL;//set that space to NULL so that the vertex's node pointer doesn't point to garbage
        }
    }
    delete [] adjacency_list;//after everything inside is deleted, delete the array itself
    delete [] visited;//delete the two integer arrays we used inside the DST functions
    delete [] display_visited;
    return 1;
}

//reset function is just an accessible method for clearing any previous work done on the integer arrays
int table::reset()
{
    for(int i = 0; i < list_size; ++i)//loop through all indices
    {
        visited[i] = 0;//set every slot to zero
        display_visited[i] = 0;
    }
    return 1;
}
