/*
Kobe Davis
Prof. Fant
CS163
17 February 2017
Main file, acts as a pretend client.

The purpose of this program is to create a card game much like pictionary and for the cards to be shuffled and
implemented with a stack abstraction and a linear linked list of arrays data structure.
*/

#include "game.h"

using namespace std;

const int SIZE = 1000;

int main()
{
    //DECK_MAX will keep the total number of cards the the user wants in their deck.
    //NODE_ARRAY_SIZE will store how large the array inside each node should be, according to the user.
    int DECK_MAX = 0;
    int NODE_ARRAY_SIZE = 0; 
   
    //Lines 23-26 will prompt the user to set DECK_MAX and NODE_ARRAY_SIZE.
    while(DECK_MAX == 0 || NODE_ARRAY_SIZE == 0)
    {
        cout << "How many cards do you want in your deck? (0 will cause reset)" << endl;
        cin >> DECK_MAX; cin.ignore(100, '\n');
        cout << "Enter the array size for the array of cards inside each node (zero will cause reset): " << endl;
        cin >> NODE_ARRAY_SIZE; cin.ignore(100, '\n');
    }
    
    //stack, game, and card objects are initialized. 
    stack my_stack(NODE_ARRAY_SIZE);
    game my_game(DECK_MAX);
    playing_card card;      //This card object in main is specifically used for adding cards.
    
    //Lines 34-37 are the data included in each card, the user will set these in Lines 59-67.
    int difficulty = 0;
    char subject[SIZE];
    char activity[SIZE];
    char hint[SIZE];
    
    //The option variable is used to allow the user to choose interface options easily.
    //The DECK_SIZE variable is used to keep track of how many cards the user has added or removed.
    //DECK_SIZE is only used in option 1 and 2, which would be Lines 58-83.
    int option = 0;
    int DECK_SIZE = 0;

    while(option != -1) //Allows user to quit game with -1 as input.
    {
        //Lines 48-56, directly below is what displays to the user his/her options when playing this game.
        cout << endl;
        cout << "Enter the number corresponding with the option you would like to choose. -1 will exit." << endl;
        cout << "1. Add Card" << endl;
        cout << "2. Remove Card" << endl;
        cout << "3. Display Cards Added" << endl;
        cout << "4. Update and Shuffle Cards" << endl;
        cout << "5. Display Shuffled Cards" << endl;
        cout << "6. Play Game" << endl;
        cin >> option; cin.ignore(100, '\n');

        if(option == 1) //If user enters a 1, add card.
        {
            while(DECK_SIZE < DECK_MAX) //Cards will continue to be added until the maximum is reached.
            {
                //Lines 63-70 the user will set the data that will be stored in a card
                cout << "Enter card difficulty (must be integer): " << endl;
                cin >> difficulty; cin.ignore(100, '\n');
                cout << "Enter subject: " << endl;
                cin.get(subject, 100, '\n'); cin.ignore(100,'\n');
                cout << "Enter activity: " << endl;
                cin.get(activity, 100, '\n'); cin.ignore(100, '\n');
                cout << "Enter hint: " << endl;
                cin.get(hint, 100, '\n'); cin.ignore(100, '\n');
                //The create card function that is a public member function of the card class is called and
                //it is given the arguments: static character arrays subject, activity, hint, and integer
                //difficulty. It will use these to set its private data.
                card.create_card(subject, activity, hint, difficulty);  
                //The add card function that is a public member function of the game class is called and
                //it is handed the recently created card to copy into an array for use later.
                my_game.add_card(card);
                ++DECK_SIZE; //DECK_SIZE is incremented to keep track of cards added.
            }
            cout << "Card(s) have been added." << endl;
        }
        else if(option == 2) //If user enters a 2, remove card.
        {
            cout << "Most recent card will be removed" << endl;
            //The remove card function is called, it is a public member function of the game class. It takes 
            //no arguments and removes the most recent card from the array that the add card function stores
            //them in.
            if(my_game.remove_card())
            {
                --DECK_SIZE; //DECK_SIZE is decremented to keep track of the cards removed.
            }
        }
        else if(option == 3) //If user enters a 3, cards added before shuffle and before game starts will be displayed
        {
            if(!my_game.display_all()) //The display all function is called, it is a public member function of
            {                          //the game class, it will display added cards in order. No arguments.
                cout << "No cards to display." << endl;
            }
        }
        //If user enters a 4, all of the cards currently added to the array will be "shuffled" or more 
        //accurately, pushed onto the stack in random order.
        else if(option == 4)
        {     
                if(!my_game.setup(my_stack))// The setup function is called, it is a public member function of
                {                           // the game class, it shuffle cards into the stack. Takes stack
                                            // object as argument.
                    cout << "No cards in deck." << endl;
                }
        }
        //If user enters a 5, all of the cards that have been shuffled into the stack will be displayed in
        //order of top to bottom in the stack.
        else if(option == 5)
        {
            if(!my_stack.display_all())//The display all function is called, it is a public member function of
            {                          //the stack object, is displays the cards in the stack. Takes no
                                       //arguments.
                cout << "You have not shuffled any cards yet!" << endl;
            }
        }
        //If user enter a 6, an interface will be activated signaling the start of the game and allows
        //the user to either draw the next card to progress the game or exit. These cards are taken off the
        //top of the stack using both the pop and peek functions.
        else if(option == 6)
        {
            int exit = 0; //int variable used to decide which option the user wants to choose.
            while(exit != 2) //if user enters a 2, loop will be exited.
            {
                cout << "\nEnter the number corresponding with your choice." << endl;
                cout << "1. Draw" << endl;
                cout << "2. Exit" << endl;
                cin >> exit; cin.ignore(100, '\n');

                if(exit == 1) //If user enters a 1 a card will be drawn.
                {
                    if(!my_game.play(my_stack))
                    {
                        cout << "No more cards. Game Over!" << endl;
                        exit = 2;
                    }
                    else
                    {
                        cout << "This is the card you drew." << endl;
                    }
                }
                else if(exit == 2) //exit play session
                {
                    cout << "\nEnding play session." << endl;
                    if(my_game.setup(my_stack))//deck gets reshuffled after play session ends
                    {
                        cout << "Deck has been re-shuffled." << endl;
                    }
                }
                else
                {
                    cout << "Please enter a valid option number." << endl;
                }
            }
        }
        else if(option != 1 && option < 1 && option > 6)//check for valid number entry
        {
            cout << "Please choose a valid option number." << endl;
        }
        else
        {
            cout << "Game will now exit." << endl;//game ends message
        }
        cout << endl;
    }

    return 0;
}
