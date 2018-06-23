/*
Kobe Davis
Prof. Fant
CS163
17 February 2017
Function file for the game and card class functions.
*/

#include "game.h"

using namespace std;

//constructor for playing_card class
playing_card::playing_card()
{
    subject = NULL;
    activity = NULL;
    hint = NULL;
    difficulty = 0;
}

//destructor for playing_card class
playing_card::~playing_card()
{
    delete [] subject;
    subject = NULL;
    delete [] activity;
    activity = NULL;
    delete [] hint;
    hint = NULL;
}

//constructor for game class
game::game()
{
    card_array = NULL;
    duplicate_check = NULL;
    array_index = 0;
}

//constructor for game class that accepts an integer argument that dictats maximum size of array
game::game(int ARRAY_SIZE)
{
    card_array = new playing_card*[ARRAY_SIZE];//dynmically allocating array according to handed in integer
    duplicate_check = new int[ARRAY_SIZE];
    array_index = 0;
}

//game class destructor
game::~game()
{
    for(int i = 0; i <= array_index; ++i)
    {
        delete card_array[i];
        card_array[i] = NULL;
    }
    delete [] card_array;
    card_array = NULL;
}

//create_card will accept as arguments three static character arrays and one integer, these data are used to
//set the new cards data and dynamically allocate where appropriate.
bool playing_card::create_card(char * user_subject, char * user_activity, char * user_hint, int user_difficulty)
{
    subject = new char[strlen(user_subject)+1];
    strcpy(subject, user_subject);
    activity = new char[strlen(user_activity)+1];
    strcpy(activity, user_activity);
    hint = new char[strlen(user_hint)+1];
    strcpy(hint, user_hint);
    difficulty = user_difficulty;
    return true;
}

//copy_card is really similar to the create_card function, although instead of taking all of the necessary
//datatypes seperately, it simply takes a card object and calls the create card function for the current card
//but with the parameters being the individual datatypes of the card that was handed in.
bool playing_card::copy_card(playing_card & source)
{
    //check to see if card has data
    if(!create_card(source.subject, source.activity, source.hint, source.difficulty))
    {
        return false;
    }
    else
    {
        return true;
    }
}

//display test function for the card class just couts all of the private data members
bool playing_card::display_test() const
{
    cout << "Subject: " << subject << endl;
    cout << "Activity: " << activity << endl;
    cout << "Hint: " << hint << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << endl;
    return true;
}

//the add card function for the game class takes a playing_card object as an argument and it adds it to the
//array defined in the private section of the game class, afterwards it will increment the array_index
//so that the next card added will not be added to the same space.
bool game::add_card( playing_card & card)
{
    card_array[array_index] = new playing_card;
    if(!card_array[array_index]->copy_card(card))//check to see if the data soon to be copied even exists
    {
        delete card_array[array_index];//if not it deletes the card it just created
        return false;
    }
    else
    {
        ++array_index;//if the add was a success, then array_index is incremented
        cout << endl;
        return true;
    }
}

//remove card function from the game class decrements the index of the array and deletes the card in that space
bool game::remove_card()
{
    if(array_index == 0)//checks if array is empty
    {
        return false;
    }
    else
    {
        --array_index;//if it isn't the index is decremented
        delete card_array[array_index];//and the card in that space is deleted
        return true;
    }
}

//display all function from game class uses a for loop and the display test function inside the cards it finds
//to display all of the cards in the initial array, this is not to be confused with the cards in the stack.
bool game::display_all() const
{
    if(array_index == 0)//check that list isn't empty
    {
        return false;
    }
    else
    {
        for(int i = 0; i < array_index; ++i)// loop and display
        {
            card_array[i]->display_test();
        }
    }
    return true;
}

//setup function from game class receives argument as a stack object, this function shuffles the cards previously
//placed into the array residing in the game class into the stack. it does so randomly and makes checks to ensure
//the same card is not placed twice
bool game::setup(stack & my_stack)
{ 
    if(!array_index)//check for empty array
    {
        return false;
    }

    while(my_stack.pop()){}//ensures the stack is empty before adding

    srand(time(0));//creating seed for rand()
    int random = 0;//integer variable used for holding random return value 
    int count = 0;//count is used to track how many loops have been made while shuffling 
    while(count < array_index)
    {
        random = rand() % array_index;//this is how we get a random index 
        if(duplicate_check[random] != 1)//here we are checking if card has already been added, 0 = no 1 = yes
        {
            ++count;//card is added
            duplicate_check[random] = 1;//this is so the card added in this loop won't be added again
            if(!my_stack.push(card_array[random]))//pushing selected card onto the stack
            {
                cout << "push failed" << endl;
            }
        }
    }
    for(int i = 0; i < array_index; ++i)
    {
        duplicate_check[i] = 0;//reseting array for checking card duplicates so next shuffle isn't ruined
    }
    return true;
}

//the play function from the game class receives a stack object, whenever this function is called, the user
//will be choosing the draw option given in main. to draw this function uses the peek function to return the
//top card through argument, the pop function to remove that top card, and the display test function on the
//card retrieved from main
bool game::play(stack & my_stack)
{
    playing_card top_card;//intialize card which will by used by main and used to display to the user
    if(!my_stack.peek(top_card))//calls peek
    {
        return false;
    }
    if(!my_stack.pop())//calls pop
    {
        return false;
    }
    cout << endl;
    if(!top_card.display_test())//calls display function that is part of playing_card class
    {
        return false;
    }
    return true;
}












