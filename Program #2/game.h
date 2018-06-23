/*
Kobe Davis
Prof. Fant
CS163
17 February 2017
This file contains the game, card, and stack class.
*/

#include <iostream>
#include <sys/time.h>
#include <string.h>
#include <cstdlib>

//manages the data for the cards the user will create and use
class playing_card
{
    public:
        playing_card();//constructor
        ~playing_card();//destructor
        //create card function returns a boolean datatype and receives 3 static character arrays and
        //1 integer. the function will set the the private data members of the card that called it
        bool create_card(char * user_subject, char * user_activity, char * user_hint, int user_difficulty);
        //copy card function returns a boolean and receives a card object as an argument.
        //the function copy card will set the current card's private data members to be the same
        //as the card taken as an argument
        bool copy_card(playing_card & source); 
        //display test function returns a boolean and takes no argument
        //this function will display all of the private data members
        bool display_test(void) const;
    private:
        char * subject;//subject of card, character pointer
        char * activity;//question or activity on card, character pointer
        int difficulty;//difficulty of question or activity, integer data type
        char * hint;// hint for question, character pointer
};
  
struct node
{
    node * next;
    playing_card ** array;//array of card pointers
};

//manages shuffled cards
class stack
{
    public:
        stack();//constructor
        stack(int LLL_ARRAY_SIZE);//constructor that takes size of array as argument
        ~stack();//destructor
        //push function returns a boolean and receives a card pointer
        //essentially takes data in the form of cards and pushes it onto the stack
        bool push(playing_card *& card);
        //pop function returns a boolean andtakes no arguments. removes top card in stack
        bool pop(void);
        //peek function returns a boolean and receives a card object as an argument.
        //the card handed into it will use the copy function on the top card to bring back and
        //display to the user.
        bool peek(playing_card & card);
        //display_all function returns a boolean and takes in no arguments. traverses stack displaying 
        //every data until list ends.
        bool display_all(void) const;
    private:
        int SIZE;//int variable used to keep track of the size of the arrays in each node
        int top_index;//int variable used to keep track of the top card in the array in the top node
        node * head;

};

//manages array used to keep track of cards added and removed pre-shuffle and pre-play
class game
{
    public:
        game();//constructor
        game(int ARRAY_SIZE);//constructor with integer argument that sets the maximum number of cards added
        ~game();//destructor 
        //add card function returns a boolean and takes a card object as an argument. the function adds the
        //card handed to it to an array to be shuffled later
        bool add_card(playing_card & card);
        //remove card function returns a boolean and takes no arguments. this function will remove the most
        //recently added card from the array of cards
        bool remove_card(void);
        //display all function returns a boolean and takes no arguments, it will display all cards in the
        //initial array with a for loop
        bool display_all(void) const;
        //setup function returns a boolean and receives a stack object as an argument. setup will randomly
        //choose indexes within the range of the initial array and put those cards into the stack
        bool setup(stack & my_stack);
        //play function returns a boolean and takes a stack object as an argument. the play function uses
        //a combination of peek and pop along with the top card's display function to allow the user to draw
        //cards and play the game
        bool play(stack & my_stack);
    private:
        int array_index;//integer variable, keeps track of the total number of cards in inital array
        int * duplicate_check;//duplicate check is an integer pointer that is set to an integer array 
                              //that is used to check if a card from a certain index has already been added
                              //to the stack
        playing_card ** card_array;//array of card pointers used to manage cards before they are shuffled
                                   //and placed into the stack
};
