//Viktoriya Petrova
//CS 202
//Program 2
//February 1, 2021

//This is the header file for the data structure used in this program.
//The data structure used is a doubly linked list that holds the day of the week (int) and a pointer to a
//liner linked list. The LLL has a pointer to a calendar_item and through dynamic binding is able to point
//to different data types (meeting, to_do, and reminder).

#ifndef CALENDAR_CALENDAR_H
#define CALENDAR_CALENDAR_H

#include "item.h"

//This class is the LLL node. It contains a pointer to the next node in the list as well as a pointer
//to a calendar item. This gives it a "has a" relationship with the calendar_item class and this is where
//dynamic binding will be needed. Every node of the LLL will be able to point to a different data type.
class LLLnode
{
public:
    LLLnode();				//Default constructor
    LLLnode(const LLLnode &copy);		//Copy constructor
    ~LLLnode();				//Destructor
    LLLnode *&go_next();			//Go to where the "next" pointer is pointing to
    int  set_value(calendar_item *toAdd);   //Store the information of one item
    int  display();				//Display the information of one item
    bool compare(char *toCompare);		//Look for a match between two titles
    int  retrieve(calendar_item *&toAdd);	//Retrieve an item saved in the LLL

protected:
    calendar_item *item;			//Pointer to an item from the hierarchy
    LLLnode *next;				//Points to the next node
};


//This class is the doubly linked list node. It contains the next and previous pointers as well as a
//date and a head pointer to the LLL. The date represents the day of the month and the LLL stores
//all of the things the user has scheduled for that date.
class DLLnode
{
public:
    DLLnode();						//Default constructor
    DLLnode(const DLLnode &copy);				//Copy constructor
    ~DLLnode();						//Destructor
    DLLnode *&go_next();				        //Go to "next" pointer
    DLLnode *&go_previous();		          	//Go to "previous" pointer
    int  set_date(int day);					//Insert a day of the month into the DLL node
    int  insert(calendar_item *toAdd);			//Insert an item into the LLL
    int  compare(int day);					//Compare two different days of the month
    void display_day();					//Display the day of the month
    void display_item();					//Display an item
    int  remove(char *title);				//Remove an item from LLL
    bool check_head();					//Check if head is NULL
    int  retrieve(char *title, calendar_item *&toAdd);	//Search for an item

protected:
    int  remove(LLLnode *&head, char *title);			   //Recursive remove from LLL
    int  retrieve(LLLnode *head, char *title, calendar_item *&toAdd);  //Recursive search through LLL
    void display_item(LLLnode *head);   				   //Recursive display of LLL
    void remove_all(LLLnode *&head);				   //Recursive removal of LLL
    int  date;							   //Day of the week (1-7)
    LLLnode *LLLhead;						   //Head pointer to the LLL
    DLLnode *next;							   //Points to the next node
    DLLnode *previous;						   //Points to the previous node
};

//This class deals with managing the data structure and allowing the user to insert, remove, retrieve, etc,
//from the list of items. It holds the head and tail pointers to the DLL.
class calendar
{
public:
    calendar();						    //Default constructor
    calendar(const calendar &copy); 			    //Copy constructor
    ~calendar();						    //Destructor
    int display_all();					    //Display all saved items in the data structure
    int insert(int day, calendar_item *toAdd);		    //Insert an item into the data structure
    int remove(int day, char *title);			    //Remove an item from the data structure
    int retrieve(char *title, calendar_item *&toAdd, int day);  //Retrieve an item from the data structure

protected:
    int  retrieve(DLLnode *head, char *title, calendar_item *&toAdd, int day); //Recursive retrieve
    int  removeDLLNode(DLLnode *&head);			 	           //Removal of a DLL node
    int  remove(DLLnode *&head, int day, char *title);			   //Recursive removal of an item
    int  insert(DLLnode *&head, int day, calendar_item *toAdd); 		   //Recursive insert
    int  display_all(DLLnode *head);					   //Recursive display of all items
    void remove_all(DLLnode *&head);					   //Recursive removal of DLL
    DLLnode *DLLhead;		     				           //Head ponter to the DLL
    DLLnode *DLLtail;						  	   //Tail pointer to the DLL
};
#endif //CALENDAR_CALENDAR_H
