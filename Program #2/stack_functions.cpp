/*
Kobe Davis
Prof. Fant
CS163
17 February 2017
Function file for the stack class
*/

#include "game.h"

using namespace std;

//constructor for stack class
stack::stack()
{
    head = NULL;
}

//constructor for stack class that accepts an argument to specify the
//size of the array in each node
stack::stack(int LLL_ARRAY_SIZE)
{
    head = NULL;
    SIZE = LLL_ARRAY_SIZE;
}

//destructor for stack class, deallocates linked list and dynamically allocated arrays inside
stack::~stack()
{
    while(head)
    {
        node * temp = head->next;
        for(int i = 0; i < SIZE; ++i)
        {
            delete head->array[i];
        }
        delete [] head->array; 
        delete head;
        head = temp;
    }
    head = NULL;
}

//push function returns a boolean and receives a card pointer. the function handles three different base cases.
//first node has not been created yet, the array inside the node is full, the array inside the node isn't
//full yet
bool stack::push(playing_card *& card)
{
    //in this case a new node is made and a card is added to the array
    if(!head)
    {
        top_index = 0;
        head = new node;
        head->next = NULL;
        head->array = new playing_card*[SIZE];
        head->array[top_index] = new playing_card;
        head->array[top_index]->copy_card(*card);
        ++top_index;
        return true;
    }
    //in this case the array is full so a new node is needed to be made and and a card added to the new array
    else if(top_index == SIZE)
    {
        top_index = 0;
        node * temp = new node;
        temp->array = new playing_card*[SIZE];
        temp->array[top_index] = new playing_card;
        temp->array[top_index]->copy_card(*card);
        temp->next = head;
        head = temp;
        ++top_index;
        return true;
    }
    //in this case the array in the head node hasn't been filled yet so all that needs to happen
    //is for a new card to be added and the index to be incremented
    else
    {
        head->array[top_index] = new playing_card;
        head->array[top_index]->copy_card(*card);
        ++top_index;
    } 
    return true;
}

//pop function returns a boolean and receives no arguments. the function handles three caases, the first 
//being no list exists so nothing can be removed, the second is that taking a card out would leave an empty
//node so the node must also be removed, and the third case where removing a card wouldn't leave an empty
//node so all that needs to be done is to decrement the index and delete the card.
bool stack::pop()
{
    //case for if there isn't a list
    if(!head)
    {
        return false;
    }
    //case for if removing a card leaves an empty node
    if(top_index == 1)
    {
        top_index = SIZE;
        delete head->array[0];
        head->array[0] = NULL;
        node * temp = head->next;
        delete [] head->array;
        head->array = NULL;
        head = temp;
        return true;
    }
    //standard removal case
    else
    {
        --top_index;
        delete head->array[top_index];
        head->array[top_index] = NULL; 
    }
    return true;
}
//peek function returns boolean and receives a card object as an argument. if there isn't a list peek function
//will not follow through, but if there is a list, peek function will call the copy function of the card
//that was handed in on the top most card of the stack.
bool stack::peek(playing_card & card)
{
    if(!head)//base case
    {
        return false;
    }
    if(!card.copy_card(*(head->array[top_index-1])))//copy function called, handed in top most card in stack
    {
        return false;
    }
    return true;
}

//display all function returns a boolean and receives no arguments. this function traverses and decrements index
//all the way to the end of the list displaying each piece of data along the way.
bool stack::display_all() const
{
    if(!head)//base case
    {
        return false;
    }
    node * current = head;
    
    int count = top_index-1;//keeps track of index

    while(current)//loops until list ends
    {
        while(count >= 0)
        {
            current->array[count]->display_test();//displays the data of each card reach
            --count;
        }
        current = current->next;
        count = SIZE-1;
    }
    return true;
}
