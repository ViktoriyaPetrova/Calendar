//Viktoriya Petrova
//CS 202
//Program 2
//February 3, 2021

//This code contains all function implementations for the hierarchy classes. The classes
//included in this file are: calendar_item, meeting, reminder, and to_do. All classes contain
//constructors, copy constructors (except the calendar_item class), and destructors. All function
//have some type of return data type (not void) in order to communicate success of failure. All
//virtual functions have the same return type and the same argument types.

#include "item.h"

///****************************CALENDAR ITEM CLASS**************************///

//Default constructor.
calendar_item::calendar_item()
{}

//Destructor.
calendar_item::~calendar_item()
{}

///**************************MEETING CLASS***********************************///

//Default constructor. Initialize all data members to 0 or NULL.
meeting::meeting(): meeting_ID(0), time(0), title(0)
{}

//Copy constructor. Creates a deep copy of the protected data members.
meeting::meeting(const meeting &copy)
{
    time = new char [strlen(copy.time) + 1];
    strcpy(time, copy.time);

    title = new char[strlen(copy.title) + 1];
    strcpy(title, copy.title);

    meeting_ID = copy.meeting_ID;

}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
meeting::~meeting()
{
    if(time) delete [] time;
    if(title) delete [] title;
    time = title = NULL;
    meeting_ID = 0;
}

//The purpose of this function is to display the information of a single meeting item.
//If this function is called without having a saved meeting_ID, time, or title it will
//return 0 since there is nothing to display. Else it will display the saved info and
//return a 1.
int meeting::display()
{
    if(!meeting_ID || !time || !title) return 0;

    cout <<"MEETING TITLE: " <<title <<endl;
    cout <<"MEETING TIME: " <<time <<endl;
    cout <<"MEETING ID: " <<meeting_ID <<endl;

    return 1;
}

//The purpose of this funciton is to store the information of a single item. All
//data members are dynamically allocated using new and sized correctly at runtime.
//If this function stores the new information correctly it will return a 1, else it
//will return a 0.
int meeting::read()
{
    char titleToAdd[50];
    char timeToAdd[50];

    cout <<"What is the title of the meeting?" <<endl;
    cin.get(titleToAdd, 50, '\n'); cin.ignore(50, '\n');
    title = new char [strlen(titleToAdd) + 1];
    strcpy(title, titleToAdd);

    cout <<"What time is the meeting? (ex: 12:00pm)" <<endl;
    cin.get(timeToAdd, 50, '\n'); cin.ignore(50, '\n');
    time = new char [strlen(timeToAdd) + 1];
    strcpy(time, timeToAdd);

    cout <<"What is the meeting ID? (ex: 1234)" <<endl;
    cin >>meeting_ID; cin.ignore(100, '\n');

    if(!meeting_ID || !time || !title) return 0;

    return 1;
}

//This function looks for a matching title. It will return true
//if a match is found, else it will return false. This function is
//used by the remove and retrieve function when searching for a specific
//item stored in the data structure.
bool meeting::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}

///******************************REMINDER CLASS*************************///

//Default constructor. Initialize all data members to 0 or NULL.
reminder::reminder(): title(0), desc(0)
{}

//Copy constructor. Creates a deep copy of the protected data members.
reminder::reminder(const reminder &copy)
{
    title = new char[strlen(copy.title) + 1];
    strcpy(title, copy.title);

    desc = new char[strlen(copy.desc) + 1];
    strcpy(desc, copy.desc);
}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
reminder::~reminder()
{
    if(title) delete [] title;
    if(desc) delete [] desc;
    title = desc = NULL;
}

//The purpose of this function is to display the information of a single reminder item.
//If this function is called without having a saved description or title it will
//return 0 since there is nothing to display. Else it will display the saved info and
//return a 1.
int reminder::display()
{

    if(!desc || !title) return 0;

    cout <<"REMINDER: " <<title <<endl;
    cout <<"REMINDER DESCRIPTION: " <<desc <<endl;

    return 1;
}

//The purpose of this funciton is to store the information of a single item. All
//data members are dynamically allocated using new and sized correctly at runtime.
//If this function stores the new information correctly it will return a 1, else it
//will return a 0.
int reminder::read()
{
    char titleToAdd[50];
    char descToAdd[200];

    cout <<"What is the title of the reminder?" <<endl;
    cin.get(titleToAdd, 50, '\n'); cin.ignore(50, '\n');
    title = new char [strlen(titleToAdd) + 1];
    strcpy(title, titleToAdd);

    cout <<"What description of the reminder? (max 200 chars)" <<endl;
    cin.get(descToAdd, 200, '\n'); cin.ignore(200, '\n');
    desc = new char [strlen(descToAdd) + 1];
    strcpy(desc, descToAdd);

    if(!desc || !title) return 0;

    return 1;
}

//This function looks for a matching title. It will return true
//if a match is found, else it will return false. This function is
//used by the remove and retrieve function when searching for a specific
//item stored in the data structure.
bool reminder::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}

///************************************TO_DO CLASS****************************///

//Default constructor. Initialize all data members to 0 or NULL.
to_do::to_do(): title(0), size(0), todo_list(0)
{}

//Constructor with args. Sets the size of the aray at runtime and initializes
//all index pointers to NULL.
to_do::to_do(int new_size): title(0), size(new_size)
{
    todo_list = new char *[new_size];
    for(int i = 0; i < new_size; ++i)
        todo_list[i] = NULL;
}

//Copy constructor. Creates a deep copy of the protected data members.
to_do::to_do(const to_do &copy)
{
    todo_list = new char *[copy.size];
    for(int i = 0; i < copy.size; ++i)
    {
        todo_list[i] = new char[strlen(copy.todo_list[i]) + 1];
        strcpy(todo_list[i], copy.todo_list[i]);
    }
    size = copy.size;
    title = new char[strlen(copy.title) + 1];
    strcpy(title, copy.title);
}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
to_do::~to_do()
{
    for(int i = 0; i < size; ++i)
    {
        if(todo_list[i])
            delete [] todo_list[i];
    }
    if(todo_list) delete [] todo_list;
    if(title) delete [] title;
    title = NULL;
    size = 0;
}

//The purpose of this funciton is to store the information of a to-do list. All
//data members are dynamically allocated using new and sized correctly at runtime.
//Even though the user chooses how large the array is they are still given an option
//here to add less items than the max size. This function will cut them off if the max
//size is reached and the array is full. If this function stores the new information
//correctly it will return a 1, else it will return a 0.
int to_do::read()
{
    char titleToAdd[100];
    char response = 'N';
    int i = 0;
    cout <<"What is the title of the to-do list?" <<endl;
    cin.get(titleToAdd, 100, '\n'); cin.ignore(100, '\n');
    title = new char[strlen(titleToAdd) + 1];
    strcpy(title, titleToAdd);

    do
    {
        char toAdd[200];
        cout <<"Add a to-do item to your list. You have " << (size - i)
             <<" spots left in your list." <<endl;
        cin.get(toAdd, 200, '\n'); cin.ignore(200, '\n');
        todo_list[i] = new char[strlen(toAdd) + 1];
        strcpy(todo_list[i], toAdd);
        ++i;
        cout <<"Another? (Y/N)";
        cin >>response; cin.ignore(100, '\n');
    }while(toupper(response) == 'Y' && i < size);

    if (!title) return 0;
    return 1;
}

//The purpose of this function is to display the saved data in the array of a
//single to_do item. If the array is empty it will return a 0 since there is nothing
//to display. If there is at least one item saved, it will display and return a 1.
int to_do::display()
{
    if(!todo_list[0]) return 0;

    cout <<"TO-DO LIST TITLE: " <<title <<endl <<endl;
    for(int i = 0; i < size; ++i)
    {
        if(todo_list[i])
            cout <<(i + 1) <<". " <<todo_list[i] <<endl;
    }

    return 1;
}

//This function looks for a matching title. It will return true
//if a match is found, else it will return false. This function is
//used by the remove and retrieve function when searching for a specific
//item stored in the data structure.
bool to_do::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}


//This is the RTTI function requirement for this project. The purpose is to remove
//a stored item from the array of chars and mark it as "complete". First the array list
//will be displayed to remind the user what they've saved. Next the user is prompted to
//choose which item they would like to mark complete. Lastly, the function will delete
//the saved char in that index and replace it with "complete". If this function is
//successfull it will return 1, else it will return 0. It gets called directly from main
//in order to use RTTI.
int to_do::complete()
{
    int i;

    display();

    cout <<"Which item would you like to mark complete?(1-" <<size <<"). ";
    cin >>i; cin.ignore(100,'\n');
    cout <<endl;

    if(todo_list[i - 1]) delete [] todo_list[i - 1];
    todo_list[i - 1] = new char[9];
    strcpy(todo_list[i - 1], "Complete");

    if(strcmp(todo_list[i - 1], "Complete") == 0) return 1;
    return 0;
}