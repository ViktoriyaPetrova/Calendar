//Viktoriya Petrova
//CS 202
//Program 2
//February 1, 2021

//This is the header file for the hierarchy. The hierarchy outlined here is a calendar_item with three
//derived children (meeting, to_do, and reminder). All functions are virtual except for one function
//located in the to_do class. Each derived class has a self similar interface and deals with different
//protected data members. The base class is an abstract base class and only serves to hold the hierarchy
//together.

#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

//The next 4 classes are part of the hierarchy. Calendar_item is the only base class in this design with
//all three other classes(meeting, reminder, and to_do) being derived from it.

//This is the base class for the hierarchy. It is also considered an abstract base class since all
//functions are pure virtual and there are no protected data members. The only function that is not
//pure virtual is the destructor. The only function that is not virtual is the constructor.
class calendar_item
{
public:
    calendar_item();				//Default constructor
    virtual ~calendar_item();       		//Destructor
    virtual int display() = 0;			//Display one item
    virtual int read() = 0;				//Read in one item
    virtual bool search(char *toCompare) = 0;	//Search for an item

protected:
    //none
};

//This is a derived class from the calendar_item class. It contains the information of a meeting
//item including meeting ID, title, and time.
class meeting: public calendar_item
{
public:
    meeting();			//Default constructor
    meeting(const meeting &copy);	//Copy constructor
    ~meeting();			//Destructor
    int  display();			//Display one meeting
    int  read();			//Read in a meeting
    bool search(char *toCompare);   //Search for a matching saved meeting

protected:
    int  meeting_ID;		//ZOOM or Google meet ID
    char *time;			//Time (ex: 12:00pm)
    char *title;			//Title of the meeting (ex: CS202)
};

//This is a derived class from the calendar_item class. It contains the information of a reminder
//including title and description.
class reminder: public calendar_item
{
public:
    reminder();			//Default constructor
    reminder(const reminder &copy); //Copy constructor
    ~reminder();			//Destructor
    int  display();			//Display a reminder
    int  read();			//Read in a reminder
    bool search(char *toCompare);   //Search for a matching saved reminder

protected:
    char *title;			//Title of the reminder
    char *desc; 			//Description of the reminder
};

//This is a derived class from the calendar_item class. It contains the information of a to-do list.
//The to-do list is stored in a dynamic array of char pointers. The size is determined at runtime
//by the user. It is also able to store the title of the list and the size of the array (once determined).
class to_do: public calendar_item
{
public:
    to_do();			//Default constructor
    to_do(int new_size);		//Constructor w/ args
    to_do(const to_do &copy);	//Copy constructor
    ~to_do();			//Destructor
    int  read();			//Read in a to-do list
    int  display();			//Display the full to-do list
    bool search(char *toCompare);   //Search for a matching saved to_do item
    int  complete();		//RTTI function. Removes a char from the array

protected:
    char *title;			//Title of the to-do list
    int  size;			//Size of the array
    char **todo_list;		//Dynamic array of char pointers
};


#endif //CALENDAR_ITEM_H
