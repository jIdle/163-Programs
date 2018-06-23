/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Program #5
 * 3/15/2017
 *
 * This file (main.cpp) will act as the client side for this program.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

//This struct will be the vertices of the graph data structure that is being created in this program.
//It contains a character pointer so it able to be recognized
//It also contains a node pointer so that it can connect to other vertices through edges
struct vertex
{
    char * name;
    struct node * head;
};

//This struct will be edges of the graph which connect the vertices together.
//It contains a vertex pointer so that it can connect the vertex it is coming from to the vertex it points to
//It als contains a node pointer called next which allows a vertex to traverse through multiple edges
struct node
{
    vertex * adjacent;
    node * next;
};

//This class will create a graph data structure.
//It's functionalities are: add vertices, add edges, find the index of a particular vertex,
//and find the longest path from a given vertex.
class table
{
    public:
        table(int size);//constructor with argument which decides size of vertex array
        ~table();//destructor

        //insert function for vertices, this function receives a char pointer from which it will name 
        //the vertex that it creates. this function returns an integer.
        int insert_vertex(char * name);

        //insert function for edges, this function receives two char pointers so that it can locate
        //and connect the two specified vertices. this function returns an integer.
        int insert_edge(char * current_vertex, char * to_attach);

        //find location function for vertices, this function receives a char pointer from which it will
        //determine the array index of the specified vertex. this function returns an int
        int find_location(char * key_value);

        //this function will display the edges of the specified vertex, it does this by using a while
        //loop to traverse through the vertex's adjacency list. this function returns an int.
        int display_adjacent(char * key_value);

        //function for determining the longest path in the graph from a specified vertex, it does this
        //by utilising the Depth First Search algorithm and only returning the largest value it receives
        //from each path. this function specifically is the wrapper function for the actual functions
        //that do the work. it will receive a character pointer from which it will specify the vertex 
        //that the recursive functions should begin from. it returns an integer
        int longest_path(char * key_value);

        //this function will reset the arrays that keep track of which vertices we have visited during
        //the DFS. if takes no arguments and returns an int.
        int reset();

        //this function returns an int and takes no arguments, it is called in the constructor to deallocate
        //all of the dynamic memory in the graph
        int remove_all();
    private:
        int list_size;//size of vertex array
        vertex * adjacency_list;//array of vertex datatypes
        int * visited;//array of ints used to keep track of which vertices have been visited
        int * display_visited;//array of ints used to keep track of which vertices have been visited

        //private function which is recursive is called by the public wrapper which is longest_path.
        //returns an int and takes a vertex pointer as an argument. this function recurses through the
        //graph and on return determines which path it returned from has the greater path length.
        //the int it returns will be the longest path length from the vertex handed into it
        int longest_path(vertex * start);

        //this function uses the above function (longest_path) to determine which path specifically is the
        //longest. before each recursive call, this function calls longest_path which will hand back
        //the value of the longest path so that this function can determine which path it should travel down.
        //this function returns an int and receives a vertex pointer as an argument for which it uses as
        //its beginning point.
        int display_longest(vertex * start);
};
