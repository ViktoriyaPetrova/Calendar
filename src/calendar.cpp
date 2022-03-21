//Viktoriya Petrova
//CS 202
//Program 2
//February 3, 2021

//This code contains all function implementations for the data structure classes. The classes
//included in this file are: LLLnode, DLLnode, and calendar. All classes contain constructors,
//copy constructors, and destructors. All function have some type of return data type (not void)
//in order to communicate success of failure. All repetitive functions use recursion to get
//the job done.

#include "calendar.h"


///*******************************LLL NODE CLASS************************************///

//Default constructor. Initialize all data members to 0 or NULL.
LLLnode::LLLnode(): item(0), next(0)
{}

//Copy constructor. Creates a deep copy of the protected data members.
LLLnode::LLLnode(const LLLnode &copy)
{
    next = copy.next;
    item = copy.item;
}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
LLLnode::~LLLnode()
{
    if(item) delete item;
    item = NULL;
}

//This function gives access to the next pointer in a node. It has no args and returns
//the next ponter.
LLLnode *&LLLnode::go_next()
{
    return next;
}

//This function gives access to the calendar_item pointer in the node. It is called by
//the insert function and it aids in the insertion of an item into the data structure.
//If it inserts correctly it will return a 1, else it will return a 0.
int LLLnode::set_value(calendar_item *toAdd)
{
    item = toAdd;
    if(item) return 1;
    return 0;
}

//This function calls on the virtual function display in order to display the information
//of a saved item.It gets called by both main and the display_all function.
int LLLnode::display()
{
    return item -> display();
}

//This function calls on the virtual search function in the hierarchy. It allows for the
//comparison between two titles when searching for a specific item saved in the data
//structure. It gets called by the remove function and the retrieve function. It catches
//the value returned by the search function and returns that value to the calling function.
//Returning true means a match was found. Returning false means a match was not found.
bool LLLnode::compare(char *toCompare)
{
    return item -> search(toCompare);
}

//The purpose of this function is to aid in the retrieval of an item saved in the data
//structure. It is only called by the retrieve function when a match is found between the
//title the user is looking for and a title of an item saved in the structure. It takes in
//a NULL calendar_item pointer as an arg and points it to the address of the item in question.
//A calendar_item pointer is able to point to a meeting, reminder, and to_do ponter due to
//upcasting performed in main. If it points to the item succefully it will return a 1, otherwise
//it will return a 0.
int LLLnode::retrieve(calendar_item *&toAdd)
{
    toAdd = item;
    if(toAdd)
        return 1;
    return 0;
}

///*******************************DLL NODE CLASS*************************///

//Default constructor. Initialize all data members to 0 or NULL.
DLLnode::DLLnode(): date(0), LLLhead(0), next(0), previous(0)
{}

//Copy constructor. Creates a deep copy of the protected data members.
DLLnode::DLLnode(const DLLnode &copy)
{
    date = copy.date;
    LLLhead = copy.LLLhead;
    next = copy.next;
    previous = copy.previous;
}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
DLLnode::~DLLnode()
{
    remove_all(LLLhead);
    LLLhead = NULL;
    next = previous = NULL;
}

//This function is only called by the destructor. It aids in the deallocation of all dynamic
//memory associated with the DLL. It uses recursion to get the job done.
void DLLnode::remove_all(LLLnode *&head)
{
    if(!head) return;

    remove_all(head -> go_next());
    LLLnode *temp = head;
    head = head -> go_next();
    delete temp;
}

//This function gives access to the next pointer in a node. It has no args and returns
//the next ponter.
DLLnode *& DLLnode::go_next()
{
    return next;
}

//This function gives access to the previous pointer in a node. It has no args and returns
//the previous ponter.
DLLnode *& DLLnode::go_previous()
{
    return previous;
}

//This function gives access to the int date data member in the node. It takes in an int
//as an arg and assigns it to the int date data memebr. This function is only used by the
//insert function when creating a new DLL node. If it sets the date correctly it will
//return a 1, else it will return a 0.
int DLLnode::set_date(int day)
{
    date = day;
    if(date) return 1;
    return 0;
}

//This function aids in the insertion of a new item into the data structure. It creates
//a new LLL node, calls on the set_value functions to save the passed in information, and
//it appends the new node into the begining of the linear linked list. Recursion is not needed
//here since we are always adding at the begining. The list doesn't need to be sorted. If it
//the insert is successfull it will return a 1, else it will return a 0.
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

//The only purpose of this function is to make the display_all function a little more user
//friendly. It displays the int saved in a DLL node. It only gets called by the display_all
//function and doesn't return anything.
void DLLnode::display_day()
{
    cout <<date;
}

//This function gets called by the display_all function in order to display the information
//of all items saved in the data structure. It has two parts - wrapper and recursion. The
//recursive function trverses through the LLL and calls on the display() funcion in order to
//display the informaion of the items one at a time.
//Part 1 - Wrapper function
void DLLnode::display_item()
{
    display_item(LLLhead);

}

//Part 2 - Recursive function
void DLLnode::display_item(LLLnode *head)
{
    if(!head) return;
    cout <<endl;
    head -> display();
    cout <<endl;
    return display_item(head -> go_next());
}

//The purpose of this function is to aid in the removal, insertion, and retrieval of an
//item from the data structure. It allows the respective recursive functions to compare
//int numbers when traversing through the DLL. It takes in an int day (provided by the user)
//and compares it to the int data stored in a DLL node. If the passed in int is larger it
//will return a 1, if it is smaller it will return a 2, if it is equal it will return a 3.
int DLLnode::compare(int day)
{
    if(day > date) return 1;
    if(day < date) return 2;
    if(day == date) return 3;
    return 0;
}

//This function is part of the remove an item from the data structure function series. It
//traverses through the LLL, looks for a matching title by calling on the compare function,
//and if a match is found it deletes the necessary node. If it removes succesfully it will
//return a 1, otherwise it will return a 0. It has 2 parts - wrapper, and recursive.
//Part 1 - Wrapper function
int DLLnode::remove(char *title)
{
    return remove(LLLhead, title);
}

//Part 2 - Recursive function
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

//This functin is only used by the calendar remove function. It checks if the
//head of the LLL is NULL. If it is not NULL it will return true, else it will return
//false.
bool DLLnode::check_head()
{
    if(LLLhead) return true;
    return false;
}

//This function is part of the retrieve an item from the data structure funciton series.
//It traverses through the LLL, looks for a matching title by using the compare function,
//and calls on the LLLnode retrive function if a match is found. It will return a 0 if no
//match is found, otherwise it will catch the value returned from the LLLnode retrieve function
//return that to the calling function. This function has 2 parts - wrapper and recursive.
//Part 1 - Wrapper function
int DLLnode::retrieve(char *title, calendar_item *&toAdd)
{
    return retrieve(LLLhead, title, toAdd);
}

//Part 2 - Recursive function
int DLLnode::retrieve(LLLnode *head, char *title, calendar_item *&toAdd)
{
    if(!head) return 0;
    if(head -> compare(title))
        return head -> retrieve(toAdd);
    return retrieve(head -> go_next(), title, toAdd);
}

///******************************CALENDAR CLASS******************************///

//Default constructor. Initialize all data members to 0 or NULL.
calendar::calendar(): DLLhead(0), DLLtail(0)
{}

//Copy constructor. Creates a deep copy of the protected data members.
calendar::calendar(const calendar &copy)
{}

//Destructor. Deallocates all dynamic memory and initializes data members to 0 or NULL.
calendar::~calendar()
{
    remove_all(DLLhead);
    DLLhead = DLLtail = NULL;
}

//The only purpose of this funciton is to aid the destructor in deallocating all dynamic
//memory associated with the DLL. It uses recursion to get the job done.
void calendar::remove_all(DLLnode *&head)
{
    if(!head) return;

    remove_all(head -> go_next());
    DLLnode *temp = head;
    head = head -> go_next();
    delete temp;
}

//This is a monster of a function. It inserts an item into the data structure.
//It has 3 parts - wrapper function located in the calendar class, a recursive
//functon located in the calendar class, and an insert function located in the
//DLLnode class.

//Part 1 - Wrapper function
//This function deals with the 3 special cases associated with inserting into a
//sorted DLL. If the list is empty, the new node is added at the head, the tail
//pointer is updated, and a 1 is returned. If the new node needs to be added to
//the begining of a non empty list, it will append at the beggining, update head,
//and return 1. If the new node needs to be added at the end of the list, it will
//append using the tail ponter (without the need for traversal), update tail, and
//return a 1. If the node needs to be added in the middle of the list, it will call
//on the recursive insert function in order to find the correct spot for insertion.
//If it doesn't add the new information in any of the casses for any reason it will
//return a 0 for failure.
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

//Part 2 - Recursive function.
//There are two special cases to consider with this function. First case is that the new date
//doesn't exist in the list so the fucntion will create a new node and append it in sorted order.
//The second case is that a node with the same date exists in the list in which case it will add the
//new calendar_item to the LLL associated with that node. If it adds successfully it will return a 1, else
//it will return a 0.
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

//This function displays all saved information in the data structure. It calls on
//the display_day function located in the DLLnode class in order to display the date
//saved in the DLL node. It also calls on the display_item function located in the
//DLLnode class in order to display the calendar_items saved in the DLL node. This
//function will return 0 if the list is empty, and a 1 if there is at least one item
//stored. It has 2 parts - wraper function and a recursive function.
//Part 1 - Wrapper function
int calendar::display_all()
{
    return display_all(DLLhead);
}

//Part 2 - Recursive function
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

//This is another monster function. The purpose is to remove an item from the data
//structure. It has 5 parts - wraper function located in the calendar class, recursive
//function located in the calendar class, special case removeDLLnode function located
//in the calendar class, wrapper function located in the DLLnode class, and a recursive
//function located in the DLLnode class.

//Part 1 - Wrapper function
//This function takes in the title of the item and the day of the month the item is
//located in as argumenents. The day and title are supplied by the user.
int calendar::remove(int day, char *title)
{
    return remove(DLLhead, day, title);
}

//Part 2 - Recursive function
//This function uses recursion to search through the DLL for a matching day
//of the month. If a match is not found or if the list is empty it will return a 0.
//If a match is found it will call on the DLLnode remove function to look for a matching
//title and remove it from the LLL. This function will catch the value returned from the
//DLLnode remove function and will return that to the wrapper function. There is one special
//case to consider. If an item is successfully removed from the LLL and it was the only item
//stored in the LLL this function will delete the DLL node since it is now empty and no
//longer needed. This is done by calling the removeDLLnode function.
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

//Part 3 - Special case function
//This function focuses on removing a node from the DLL. It is only called by the
//remove function when the node is empty and no longer needed. This function deals with
//3 special cases. When the first node in the list is removed, the previous pointer of the
//next node needs to be set to NULL. When removing the last node in the list, the next
//pointer of the previous node needs to be set to NULL. When removing a node from the middle
//of the list, both the next and previous pointers need to be reconnected properly. If this
//function deletes the needed node successfully it will return 1, else it will return 0.
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
//This function retrieves an item from the data structure. It has 5 parts-
//a wrapper function in the calendar clas, a recursive function in the
//calendar class, a wrapper function in the DLLnode class, a recursive
//function in the DLLnode class, and a function in the LLLnode class.
//If it retrieves successfully it will return a 1, else it will return 0.

//Part 1 - Wrapper function
//This function takes in a title of the item, what day the item is located in,
//and the pointer that will be used to store the found information. All arguments
//are supplied by main/user.
int calendar::retrieve(char *title, calendar_item *&toAdd, int day)
{
    return retrieve(DLLhead, title, toAdd, day);
}

//Part 2 - Recursive function
//This function uses recursion to find the correct date in the DLL where the
//item is located in. If there is no match it will return a 0. If a match is
//found it will call on the DLLnode retrieve function which will look for a
//matching title. This function catches the value returned from the DLLnode
//retrieve function and will then continue returning it to the wrapper function.
int calendar::retrieve(DLLnode *head, char *title, calendar_item *&toAdd, int day)
{
    if(!head) return 0;
    if(head -> compare(day) == 3)
        return head -> retrieve(title, toAdd);

    return retrieve(head -> go_next(), title, toAdd, day);
}
