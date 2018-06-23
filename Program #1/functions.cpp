/*
this file will hold all of the functions that are defined in header.h and their description/instructions
*/
#include "header.h"

using namespace std;
//node constructor
node::node()
{
    topic_next = NULL;
    time_next = NULL;

    title = NULL;
    topic = NULL;
    description = NULL;
    source = NULL;

    hr = 0;
    min = 0;
    sec = 0;
    stars = 0;
}
//node destructor
node::~node()
{
    delete [] title;
    delete [] topic;
    delete [] description;
    delete [] source;

    topic_next = NULL;
    time_next = NULL;
}
//news list class constructor
news_list::news_list()
{
    time_head = NULL;
    topic_head = NULL;
    topic_interest = NULL; 
}
//news list class destructor
news_list::~news_list()
{
     delete [] topic_interest;   
}
//this function allows the input of the different values and cocatenates them
//this means the three numbers in order of input will be "attached" to each
//other as a whole number. this allows for easy comparisons of timestamps
//rather than separate comparisons
int news_list::concatenate(int user_hr, int user_min, int user_sec)
{
    int zeroes = 1;
    while(zeroes <= user_min)
    {
        zeroes *= 10;
    }
    int hr_min = (user_hr * zeroes) + user_min;
    zeroes = 1;
    while(zeroes <= user_sec)
    {
        zeroes *= 10;
    }
    return ((hr_min * zeroes) + user_sec);
}
//takes in a node and displays it's information, does not change anything
void news_list::display_once(node *&current) const
{
    cout << endl << endl;
    cout << "timestamp: " << current->hr << ":"
         << current->min  << ":"
         << current->sec << endl;
    cout << "title: " << current->title << endl;
    cout << "topic: " << current->topic << endl;
    cout << "description: " << current->description << endl;
    cout << "source: " << current->source << endl;
    cout << endl << endl;
}
//is passed a a node currently being created and uses the time_t datatype, tm struct
//and localtime function from the ctime library to set the nodes hour, minute, and second
//for tits timestamp
void news_list::set_time(node *&current)
{
    time_now = time(0);
    timestamp = localtime(&time_now); 
    current->hr = timestamp->tm_hour; 
    current->min = timestamp->tm_min;
    current->sec = timestamp->tm_sec;
}
//passed in the node currently being created along with character arrays from the user
//which will be dynamically allocated and then set as current's news post data
void news_list::copy(node *&current, char s_title[], char s_topic[], char s_description[], char s_source[])
{
    current->title = new char[strlen(s_title)+1];
    strcpy(time_head->title, s_title); 
    current->topic = new char[strlen(s_topic)+1];
    strcpy(time_head->topic, s_topic); 
    current->description = new char[strlen(s_description)+1];
    strcpy(time_head->description, s_description); 
    current->source = new char[strlen(s_source)+1];
    strcpy(time_head->source, s_source);
}
//adds a news posts to the list of already existing news posts
//this function will do this by calling the copy and set time functions
//while also cleaning up and re-directing node pointers
//the information concerning the new news posts is obtained from the client and 
//worked with here
bool news_list::add_news(char s_title[], char s_topic[], char s_description[], char s_source[])
{
    //base case: list is empty
    if(!time_head)
    {
        time_head = new node;
        topic_head = time_head;
        copy(time_head, s_title, s_topic, s_description, s_source);
        set_time(time_head);
        time_head->topic_next = NULL;
        time_head->time_next = NULL;
        return true;
    }
    //base case: news post topic is alphabetically first 
    if(strcmp(s_title, topic_head->title) < 0)
    {
        node * temp = new node;
        temp->time_next = time_head;
        time_head = temp;

        temp->topic_next = topic_head;
        topic_head = temp;

        copy(time_head, s_title, s_topic, s_description, s_source);
        set_time(time_head);
        return true;
    }
    //base case: news post topic is alphabetically
    //ANYWHERE ELSE other than the first position.
    //Meaning this accounts for last also.
    else
    {
        node * current = topic_head;
        node * previous = NULL;
    
        while(current != NULL && strcmp(s_title, current->title) > 0)
        {
            previous = current;
            current = current->topic_next;
        }

        current = new node;
        current->topic_next = previous->topic_next;
        previous->topic_next = current;

        current->time_next = time_head;
        time_head = current;

        copy(current, s_title, s_topic, s_description, s_source);
        set_time(current);

        return true;
    }
}
//takes in the hour, minute, and second from the client from a supposedly particular
//news post. it will try to find a match, if it doesn't then it will return false, if
//the list is empty it will return false, otherwise it will go ahead and dynamically 
//allocate the static char array given from the client and replace the specified news
//post's description with the supplied one
bool news_list::update_news(int user_hr, int user_min, int user_sec, char s_description[])
{
    //bas case: no list
    if(!time_head)
    {
        return false;
    }
    node * current = time_head;
    //base case: matching post timestamp
    while(current)
    {
        if(user_hr == current->hr && user_min == current->min && user_sec == current->sec)
        {
            delete [] current->description;
            current->description = new char[strlen(s_description)+1];
            strcpy(current->description, s_description);
            return true;
        }
        current = current->time_next;
    }
    //base case: match not found
    return false;
}
//sets the topic of interest for later use in the display topic function
//also dynimcally allocates it
void news_list::set_topic(char s_topic[])
{
   topic_interest = new char[strlen(s_topic)+1];
   strcpy(topic_interest, s_topic);
}
//wrapper function for a recursive display all function, also checks if list exists
bool news_list::display_all() const
{
    if(!time_head)
    {
        return false;
    }
    return display_all(time_head);//begins recursive function, function overloading
}
//recursive display all function, doesn't change anything, calls display once function
//each time it move forward
bool news_list::display_all(node *current) const
{
    if(current)
    {
        display_once(current);//display to terminal
        return display_all(current->time_next);//recursion
    }
    else
    {
        return true;
    }
}
//display last three posts to terminal, doesn't change anything
//also checks if there's even a list
bool news_list::display_recent() const
{
    if(!time_head)
    {
        return false;
    }

    node * current = time_head;
    int i = 0;

    while(current && i<3)//checks that display only happens three times
    {
        display_once(current);
        i++;
        current = current->time_next;
    }
    return true;
}
//display only news posts with the set topic of interest, doesn't change anything
//checks if list doesn't exists or if topic hasn't been set yet
//each movement forward in the list, the topic is compared to the TOI and if so displays
bool news_list::display_topic() const
{
    if(!topic_interest || !time_head)//checks if list or TOI exists
    {
        return false;
    }
    else
    {
        node * current = topic_head;
        while(current)
        {
            if(!strcmp(topic_interest, current->topic))//compares topics each time
            {
                display_once(current);
            }
            current = current->topic_next;
        }
        return true;
    }
}
//removes all nodes older than specified hour, minute, and second. time must match with pre-existing news post
//if no list the function will return false. the first thing the function does is find after which node
//all other should be deleted, then sets it's next pointer to null. this is fine b/c we still have access
//to those nodes through the topic list. the function then goes through the topic list deleting all posts
//that are of an older time than specified. the concatenate function is used throughout this function to make
//the comparison of timestamps easier while traversing
bool news_list::remove_older_than(int user_hr, int user_min, int user_sec)
{
    if(!time_head)//checks if list list even exists
    {
        return false;
    }
    
    node * current = time_head;
    node * previous = NULL;
    int combo = concatenate(user_hr, user_min, user_sec);//creating a variable for concatenated user input time
    //traversal to set oldest acceptable node's next pointer to null
    while(current)
    {
        if(combo == concatenate(current->hr, current->min, current->sec))//comparison to check if the specified
        {                                                                //post has been found
            current->time_next=NULL;
        }
        current = current->time_next;
    }
    //traversal to begin removing specific nodes without ruining topic list
    current = topic_head;
    //head removal case
    //this case exists so that if topic_head happens to be one of the posts that was older than the specified
    //time, we wont lose our list while deleting, this case allows for head to be redirected to the next node
    while(combo > concatenate(topic_head->hr, topic_head->min, topic_head->sec))//checks if topic_head qualifies
    {                                                                           //for deletion
        current = topic_head->topic_next;
        delete topic_head;
        topic_head = current;
    }
    //body and list removal case
    //this case covers everything else, any nodes along this list that are older than the specified time will
    //be deleted and linked back up from the perspective of the topic list
    while(current)
    {
        if(combo > concatenate(current->hr, current->min, current->sec))//checks if qualifies for deletion
        {
            previous->topic_next = current->topic_next;
            delete current;
            current = previous->topic_next;
        }
        else
        {
            current = current->topic_next;
        }
    }
    return true;
}
//averages the user given accuracy rating with the pre-existing accuracy rating if there is one
//also checks if there even is a list.
int news_list::rate(int user_stars, int user_hr, int user_min, int user_sec)
{
    if(!time_head)
    {
        return 0;
    }
    node * current = time_head;
    while(current)
    {
        if(user_hr == current->hr && user_min == current->min && user_sec == current->sec)
        {
            if(current->stars == 0)
            {
                current->stars = user_stars;
            }
            else
            {
                current->stars = (current->stars + user_stars)/2;
            }
            return current->stars;
        }
        current = current->time_next;
    }
    return 0;
}








