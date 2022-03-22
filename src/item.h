#ifndef CALENDAR_ITEM_H
#define CALENDAR_ITEM_H

#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

class calendar_item
{
public:
    calendar_item();
    virtual ~calendar_item();
    virtual int display() = 0;
    virtual int read() = 0;
    virtual bool search(char *toCompare) = 0;

protected:
    //none
};

class meeting: public calendar_item
{
public:
    meeting();
    meeting(const meeting &copy);
    ~meeting();
    int  display();
    int  read();
    bool search(char *toCompare);

protected:
    int  meeting_ID;
    char *time;
    char *title;
};

class reminder: public calendar_item
{
public:
    reminder();
    reminder(const reminder &copy);
    ~reminder();
    int  display();
    int  read();
    bool search(char *toCompare);

protected:
    char *title;
    char *desc;
};

class to_do: public calendar_item
{
public:
    to_do();
    to_do(int new_size);
    to_do(const to_do &copy);
    ~to_do();
    int  read();
    int  display();
    bool search(char *toCompare);
    int  complete();

protected:
    char *title;
    int  size;
    char **todo_list;
};

#endif //CALENDAR_ITEM_H
