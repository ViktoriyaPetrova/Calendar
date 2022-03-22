#include "item.h"

///****************************CALENDAR ITEM CLASS**************************///
calendar_item::calendar_item()
{}

calendar_item::~calendar_item()
{}

///**************************MEETING CLASS***********************************///
meeting::meeting(): meeting_ID(0), time(0), title(0)
{}

meeting::meeting(const meeting &copy)
{
    time = new char [strlen(copy.time) + 1];
    strcpy(time, copy.time);

    title = new char[strlen(copy.title) + 1];
    strcpy(title, copy.title);

    meeting_ID = copy.meeting_ID;

}

meeting::~meeting()
{
    if(time) delete [] time;
    if(title) delete [] title;
    time = title = NULL;
    meeting_ID = 0;
}

int meeting::display()
{
    if(!meeting_ID || !time || !title) return 0;

    cout <<"MEETING TITLE: " <<title <<endl;
    cout <<"MEETING TIME: " <<time <<endl;
    cout <<"MEETING ID: " <<meeting_ID <<endl;

    return 1;
}

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

bool meeting::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}

///******************************REMINDER CLASS*************************///
reminder::reminder(): title(0), desc(0)
{}

reminder::reminder(const reminder &copy)
{
    title = new char[strlen(copy.title) + 1];
    strcpy(title, copy.title);

    desc = new char[strlen(copy.desc) + 1];
    strcpy(desc, copy.desc);
}

reminder::~reminder()
{
    if(title) delete [] title;
    if(desc) delete [] desc;
    title = desc = NULL;
}

int reminder::display()
{

    if(!desc || !title) return 0;

    cout <<"REMINDER: " <<title <<endl;
    cout <<"REMINDER DESCRIPTION: " <<desc <<endl;

    return 1;
}

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

bool reminder::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}

///************************************TO_DO CLASS****************************///
to_do::to_do(): title(0), size(0), todo_list(0)
{}

to_do::to_do(int new_size): title(0), size(new_size)
{
    todo_list = new char *[new_size];
    for(int i = 0; i < new_size; ++i)
        todo_list[i] = NULL;
}

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

bool to_do::search(char *toCompare)
{
    if(strcmp(toCompare, title) == 0)
        return true;
    return false;
}

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