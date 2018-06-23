/*
this file will act the client, it supplies a sort of interface for the grader/user to work with the list organizing and managing
*/

#include "header.h"

using namespace std;

const int SIZE = 100;

int main()
{
   news_list list; 

    //variables for function testing
    char s_title[SIZE];
    char s_topic[SIZE];
    char s_description[SIZE];
    char s_source[SIZE];
    int user_hr = 0;
    int user_min = 0;
    int user_sec = 0;
    int stars = 0;

    char stop[5];

    int option_number = 0;
    while(option_number != -1){
    cout << "enter the corresponding number to the option you would like to choose: " << endl;
    cout << " 1. add news post \n 2. update news post \n 3. set the topic of interest \n 4. display all news posts \n 5. display recent news posts \n 6. dislay only topic of interest news posts \n 7. remove news posts earlier than \n 8. give a post an acuracy rating" << endl; 
    cin >> option_number;
    cin.ignore(100, '\n');
    //testing for add_news
    if(option_number == 1){
    while(strcmp(stop, "stop") != 0){
        cout << "enter title" << endl;
        cin.get(s_title, SIZE, '\n'); cin.ignore(SIZE, '\n');
        cout << "enter topic" << endl;
        cin.get(s_topic, SIZE, '\n'); cin.ignore(SIZE, '\n');
        cout << "enter description" << endl;
        cin.get(s_description, SIZE, '\n'); cin.ignore(SIZE, '\n');
        cout << "enter source" << endl;
        cin.get(s_source, SIZE, '\n'); cin.ignore(SIZE, '\n');
        if(!list.add_news(s_title, s_topic, s_description, s_source)){
            cout << "add function return false" << endl;
        }
        else
            cout << "success" << endl;
        cout << "another or stop?" << endl;
        cin.get(stop, 5, '\n'); cin.ignore(5, '\n');
    }}
    strcpy(stop, "rese");

    //testing for update_news
    if(option_number == 2){
    cout << "enter the timestamp of the entry to be edited" << endl;
    cout << "hour<enter>, minute<enter>, second<enter>" << endl;
    cin >> user_hr;
    cin >> user_min;
    cin >> user_sec;
    cin.ignore(100, '\n');
    cout << "enter your replacement description" << endl;
    cin.get(s_description, SIZE, '\n'); cin.ignore(SIZE, '\n');
    if(!list.update_news(user_hr, user_min, user_sec, s_description))
    {
        cout << "update failed" << endl;
    }}

    //testing for set_topic
    if(option_number == 3){
    cout << "enter the priority topic" << endl;
    cin.get(s_topic, SIZE,'\n'); cin.ignore(SIZE, '\n');
    list.set_topic(s_topic);
    }

    //testing for display_all
    if(option_number == 4){
    if(!list.display_all())
    {
        cout << "display failed" << endl;
    }}

    //testing for display_recent
    if(option_number == 5){
    if(!list.display_recent())
    {
        cout << "Error: No list" << endl;
    }}

    //testing for display_topic
    if(option_number == 6){
    if(!list.display_topic())
    {
        cout << "display topic failed" << endl;
    }}

    //testing for remove_older_than
    if(option_number == 7){
    cout << "enter the timestamp of a particular news entry, hour<enter>, minute<enter>, second<enter>. everything older will be deleted." << endl;
    cin >> user_hr;
    cin >> user_min;
    cin >> user_sec;
    cin.ignore(100, '\n');
    if(!list.remove_older_than(user_hr, user_min, user_sec))
    {
        cout << "removal failed" << endl;
    }}

    //testing for rate 
    if(option_number == 8){
    cout << "enter the timestamp of the entry to be rated" << endl;
    cout << "hour<enter>, minute<enter>, minute<enter>" << endl;
    cin >> user_hr;
    cin >> user_min;
    cin >> user_sec;
    cout << "enter accuracy rating of chosen entry from 1 to 5" << endl;
    cin >> stars;
    cin.ignore(100,'\n');
    int x = list.rate(stars, user_hr, user_min, user_sec);
    if(x == 0)
    {
        cout << "either no entries or timestamp was incorrect" << endl;
    }
    cout << "accuracy rating after averaging with yours: " << x << endl;
    }}
    return 0;
}
