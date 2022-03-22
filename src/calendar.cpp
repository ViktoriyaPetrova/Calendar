#include "calendar.h"


///*******************************LLL NODE CLASS************************************///

LLLnode::LLLnode(): item(0), next(0)
{}

LLLnode::LLLnode(const LLLnode &copy){
    next = copy.next;
    item = copy.item;
}

LLLnode::~LLLnode(){
    if(item) delete item;
    item = NULL;
}

LLLnode *&LLLnode::go_next(){
    return next;
}

int LLLnode::set_value(calendar_item *toAdd){
    item = toAdd;
    if(item) return 1;
    return 0;
}

int LLLnode::display(){
    return item -> display();
}

bool LLLnode::compare(char *toCompare){
    return item -> search(toCompare);
}

int LLLnode::retrieve(calendar_item *&toAdd){
    toAdd = item;
    if(toAdd)
        return 1;
    return 0;
}

///*******************************DLL NODE CLASS*************************///

DLLnode::DLLnode(): date(0), LLLhead(0), next(0), previous(0)
{}

DLLnode::DLLnode(const DLLnode &copy)
{
    date = copy.date;
    LLLhead = copy.LLLhead;
    next = copy.next;
    previous = copy.previous;
}

DLLnode::~DLLnode()
{
    remove_all(LLLhead);
    LLLhead = NULL;
    next = previous = NULL;
}

void DLLnode::remove_all(LLLnode *&head)
{
    if(!head) return;

    remove_all(head -> go_next());
    LLLnode *temp = head;
    head = head -> go_next();
    delete temp;
}

DLLnode *& DLLnode::go_next()
{
    return next;
}

DLLnode *& DLLnode::go_previous()
{
    return previous;
}

int DLLnode::set_date(int day)
{
    date = day;
    if(date) return 1;
    return 0;
}

int DLLnode::insert(calendar_item *toAdd)
{
    LLLnode *temp = new LLLnode;
    if(temp -> set_value(toAdd))
    {
        if(LLLhead)
        {
            temp -> go_next() = LLLhead;
            LLLhead = temp;
        }
        else
            LLLhead = temp;
        return 1;
    }

    else
    {
        delete temp;
        return 0;
    }
}

void DLLnode::display_day()
{
    cout <<date;
}

void DLLnode::display_item()
{
    display_item(LLLhead);

}

void DLLnode::display_item(LLLnode *head)
{
    if(!head) return;
    cout <<endl;
    head -> display();
    cout <<endl;
    return display_item(head -> go_next());
}

int DLLnode::compare(int day)
{
    if(day > date) return 1;
    if(day < date) return 2;
    if(day == date) return 3;
    return 0;
}

int DLLnode::remove(char *title)
{
    return remove(LLLhead, title);
}

int DLLnode::remove(LLLnode *&head, char *title)
{
    if(!head) return 0;
    if(head -> compare(title))
    {
        LLLnode *temp = head;
        head = head -> go_next();
        delete temp;
        return 1;
    }
    return remove(head -> go_next(), title);
}

bool DLLnode::check_head()
{
    if(LLLhead) return true;
    return false;
}

int DLLnode::retrieve(char *title, calendar_item *&toAdd)
{
    return retrieve(LLLhead, title, toAdd);
}

int DLLnode::retrieve(LLLnode *head, char *title, calendar_item *&toAdd)
{
    if(!head) return 0;
    if(head -> compare(title))
        return head -> retrieve(toAdd);
    return retrieve(head -> go_next(), title, toAdd);
}

///******************************CALENDAR CLASS******************************///

calendar::calendar(): DLLhead(0), DLLtail(0)
{}

calendar::calendar(const calendar &copy)
{}

calendar::~calendar()
{
    remove_all(DLLhead);
    DLLhead = DLLtail = NULL;
}

void calendar::remove_all(DLLnode *&head)
{
    if(!head) return;

    remove_all(head -> go_next());
    DLLnode *temp = head;
    head = head -> go_next();
    delete temp;
}

int calendar::insert(int day, calendar_item *toAdd)
{
    //Case 1: If the list is empty insert at the head
    if(!DLLhead)
    {
        DLLhead = new DLLnode;
        if(DLLhead -> set_date(day) && DLLhead -> insert(toAdd))
        {
            DLLtail = DLLhead;
            return 1;
        }
        else
        {
            delete DLLhead;
            return 0;
        }
    }

        //Case 2: If the new date is smaller than head, insert at the begining
    else if(DLLhead -> compare(day) == 2)
    {
        DLLnode *temp = new DLLnode;
        if(temp -> set_date(day) && temp -> insert(toAdd))
        {
            temp -> go_next() = DLLhead;
            DLLhead -> go_previous() = temp;
            DLLhead = temp;
            return 1;
        }
        else
        {
            delete temp;
            return 0;
        }
    }

        //Case 3: If the new date is larger than tail, insert at the end without traversing
    else if(DLLtail -> compare(day) == 1)
    {
        DLLtail -> go_next() = new DLLnode;
        DLLtail -> go_next() -> go_previous() = DLLtail;
        DLLtail = DLLtail -> go_next();
        if(DLLtail -> set_date(day) && DLLtail -> insert(toAdd))
            return 1;
        else
        {
            DLLtail = DLLtail -> go_previous();
            delete DLLtail -> go_next();
            DLLtail -> go_next() = NULL;
            return 0;
        }
    }

        //Case 4: The new date is sorted in the middle of the list using recursion
    else
        return insert(DLLhead, day, toAdd);

    return 0;
}

int calendar::insert(DLLnode *&head, int day, calendar_item *toAdd)
{
    //Base case
    if(!head) return 0;

    //Case 1: The new date doesn't exist. Add between head and head's previous.
    if(head -> compare(day) == 2)
    {
        DLLnode *temp = new DLLnode;
        //Make sure all info is added correctly
        if(temp -> set_date(day) && temp -> insert(toAdd))
        {
            temp -> go_next() = head;
            temp -> go_previous() = head -> go_previous();
            head -> go_previous() -> go_next() = temp;
            head -> go_previous() = temp;
            return 1;
        }
        else
        {
            delete temp;
            return 0;
        }
    }

    //Case 2: The new date exists. Add to head's linear linked list.
    if(head -> compare(day) == 3)
    {
        //Make sure all info is added correctly
        if(head -> insert(toAdd))
            return 1;
        else
            return 0;
    }

    return insert(head -> go_next(), day, toAdd);
}

int calendar::display_all()
{
    return display_all(DLLhead);
}

int calendar::display_all(DLLnode *head)
{
    if(!head) return 0;
    cout <<"DAY OF THE MONTH: ";
    head -> display_day();
    cout <<endl <<endl;
    cout <<"SCHEDULED ITEMS:" <<endl;
    head -> display_item();
    display_all(head -> go_next());
    return 1;
}

int calendar::remove(int day, char *title)
{
    return remove(DLLhead, day, title);
}

int calendar::remove(DLLnode *&head, int day, char *title)
{
    if(!head) return 0;
    if(head -> compare(day) == 3)
    {
        //Delete from the LLL
        if(!head -> remove(title))
            return 0;

        //Need to remove the DLL node if LLLhead is null
        if(!head -> check_head())
            return removeDLLNode(head);

        return 1;
    }

    return remove(head -> go_next(), day, title);
}

int calendar::removeDLLNode(DLLnode *&head)
{
    //Case 1: Removing the first node in the DLL
    if(!head -> go_previous())
    {
        DLLnode *temp = head;
        head = head -> go_next();
        if(head)
            head -> go_previous() = NULL;
        delete temp;
        return 1;
    }

    //Case 2: Removing the last node in the DLL
    else if(!head -> go_next())
    {
        DLLnode *temp = head;
        head = head -> go_previous();
        head -> go_next() = NULL;
        delete temp;
        return 1;
    }

    //Case 3: Removing in the middle of the DLL
    else
    {
        DLLnode *temp = head;
        head = head -> go_next();
        temp -> go_previous() -> go_next() = head;
        head -> go_previous() = temp -> go_previous();
        delete temp;
        return 1;
    }
    return 0;
}

int calendar::retrieve(char *title, calendar_item *&toAdd, int day)
{
    return retrieve(DLLhead, title, toAdd, day);
}

int calendar::retrieve(DLLnode *head, char *title, calendar_item *&toAdd, int day)
{
    if(!head) return 0;
    if(head -> compare(day) == 3)
        return head -> retrieve(title, toAdd);

    return retrieve(head -> go_next(), title, toAdd, day);
}
