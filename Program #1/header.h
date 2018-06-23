/*
Kobe Davis
Prof. Fant
CS163
Jan. 28, 2017

This program organizes a list of news posts. When executed the user will be asked to enter the corresponding number
to the option they would like to choose. The ouput will depend on which option the choose. In summary, the program
will organizes and manage news posts while keeping them connected by topic and by time, ordered by title when not 
ordered by time.
*/
#include <iostream>
#include <cctype>
#include <cstring>
#include <ctime>
//nodes for making LLL
struct node
{
    //constructor desctructor
    node();
   ~node();
   //both next pointer to organize by topic and by time
    node * topic_next;
    node * time_next;
    //all the data stored in each post
    char * title;
    char * topic;
    char * description;
    char * source;
    //the timestamp for each post
    int hr;
    int min;
    int sec;
    int stars;
};
//class for managing LLL of nodes that are news posts
class news_list
{
	public:
        //constuctor & destructor
        news_list(void);
        ~news_list(void);

        //public functions for utilising/modyfing news entries
        //adds new node, parameters are all static character arrays, title, topic, description, and source of news post
        bool add_news(char s_title[], char s_topic[], char s_description[], char s_source[]);
        //updates existing post, parameters are integers hour, minute, and second of timestamp, and static character array description to be added.
        bool update_news(int user_hr, int user_min, int user_sec, char s_description[]);
        //sets topic of interest, parameter is static character array topic of interest
        void set_topic(char s_topic[]);
        //display all post, no parameters, actually a wrapper function for the recursive display all in the private section
        bool display_all(void) const;
        //displays three most recent posts, no parameters
        bool display_recent(void) const;
        //display only news posts with matching topic of interest
        bool display_topic(void) const;
        //removes nodes older than specified time, parameters are ints hour, minute, and second of timestamp
        bool remove_older_than(int user_hr, int user_min, int user_sec);
        //averages given accuracy with pre-existing accuracy rating of news post, parameters are int user rating, and ints hour, minute, second of timestamp
        int rate(int user_stars, int user_hr, int user_min, int user_sec);
        //dynamically allocates all statically allocated character arrays passed in by client
        //parameters are: the node which is being created, static character arrays title, topic, description, and source of news post
        void copy(node *&current, char s_title[], char s_topic[], char s_description[], char s_source[]);
        //sets time value for each post created, parameter is the node that is being created
        void set_time(node *&current);
        //displays the information of the node fed into it, parameter is node
        void display_once(node *&current) const;
        //this function is used to make timestamp comparisons easier, parameters are ints hour, minute, second of timestamp
        int concatenate(int user_hr, int user_min, int user_sec);
	private:
        //two head pointers, one to keep track of list by topic, the other to keep track of list by time
        node * time_head;
        node * topic_head;
        //time_t data type and pointer to tm struct timestamp to aid in
        //creation of timestamp for each news post
        time_t time_now;
        tm *timestamp; 
        //recursive function for display all, paramter should the next node in a list 
        bool display_all(node*) const;
        //soon to be dynamically allocated character array for holding the topic of interest
        char * topic_interest;
};
