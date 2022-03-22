#ifndef CALENDAR_CALENDAR_H
#define CALENDAR_CALENDAR_H
#include "item.h"

class LLLnode
{
public:
    LLLnode();
    LLLnode(const LLLnode &copy);
    ~LLLnode();
    LLLnode *&go_next();
    int  set_value(calendar_item *toAdd);
    int  display();
    bool compare(char *toCompare);
    int  retrieve(calendar_item *&toAdd);

protected:
    calendar_item *item;
    LLLnode *next;
};

class DLLnode
{
public:
    DLLnode();
    DLLnode(const DLLnode &copy);
    ~DLLnode();
    DLLnode *&go_next();
    DLLnode *&go_previous();
    int  set_date(int day);
    int  insert(calendar_item *toAdd);
    int  compare(int day);
    void display_day();
    void display_item();
    int  remove(char *title);
    bool check_head();
    int  retrieve(char *title, calendar_item *&toAdd);

protected:
    int  remove(LLLnode *&head, char *title);
    int  retrieve(LLLnode *head, char *title, calendar_item *&toAdd);
    void display_item(LLLnode *head);
    void remove_all(LLLnode *&head);
    int  date;
    LLLnode *LLLhead;
    DLLnode *next;
    DLLnode *previous;
};

class calendar
{
public:
    calendar();
    calendar(const calendar &copy);
    ~calendar();
    int display_all();
    int insert(int day, calendar_item *toAdd);
    int remove(int day, char *title);
    int retrieve(char *title, calendar_item *&toAdd, int day);

protected:
    int  retrieve(DLLnode *head, char *title, calendar_item *&toAdd, int day);
    int  removeDLLNode(DLLnode *&head);
    int  remove(DLLnode *&head, int day, char *title);
    int  insert(DLLnode *&head, int day, calendar_item *toAdd);
    int  display_all(DLLnode *head);
    void remove_all(DLLnode *&head);
    DLLnode *DLLhead;
    DLLnode *DLLtail;
};
#endif //CALENDAR_CALENDAR_H
