#include "calendar.h"

int main()
{

    calendar january;
    char response = 'N';
    char title[50];
    int  main_menu = 0;
    int  items;
    int  day;

    do
    {
        cout <<endl;
        cout <<"Main Menu" <<endl;
        cout <<"What would you like to do?"
             <<"\n1. Insert a meeting."
             <<"\n2. Insert a reminder."
             <<"\n3. Insert a to-do list."
             <<"\n4. Remove an item (meeting, reminder, or to-list)."
             <<"\n5. Retrieve an item (meeting, reminder, or to-list)."
             <<"\n6. Mark an item complete from a saved to-do list."
             <<"\n7. Display all info stored in the calendar."
             <<"\n8. Quit program." <<endl;
        cout <<"Please make a selection by entering a number from 1 to 8.";
        cin >>main_menu; cin.ignore(100, '\n');
        cout <<endl;

        //Adding a meeting
        if(main_menu == 1)
        {
            do
            {
                cout <<endl;
                calendar_item *toAdd = new meeting;   //Upcasting
                if(!toAdd -> read())
                    cout <<"ERROR" <<endl;
                cout <<"Which day of the month?" <<endl;
                cin >>day; cin.ignore(100, '\n');
                if(!january.insert(day, toAdd))
                    cout <<"ERROR" <<endl;
                cout <<"Again?";
                cin >>response; cin.ignore(100, '\n');
            }while(toupper(response) == 'Y');
        }

        //Adding a reminder
        if(main_menu == 2)
        {
            do
            {
                cout <<endl;
                calendar_item *toAdd = new reminder;   //Upcasting
                if(!toAdd -> read())
                    cout <<"ERROR" <<endl;
                cout <<"Which day of the month?" <<endl;
                cin >>day; cin.ignore(100, '\n');
                if(!january.insert(day, toAdd))
                    cout <<"ERROR" <<endl;
                cout <<"Again?";
                cin >>response; cin.ignore(100, '\n');
            }while(toupper(response) == 'Y');
        }

        //Adding a to-do list
        if(main_menu == 3)
        {
            do
            {
                cout <<endl;
                cout <<"How many items does your list have?";
                cin >>items; cin.ignore(100,'\n');
                calendar_item *toAdd = new to_do(items);   //Upcasting
                if(!toAdd -> read())
                    cout <<"ERROR" <<endl;
                cout <<"Which day of the month?" <<endl;
                cin >>day; cin.ignore(100, '\n');
                if(!january.insert(day, toAdd))
                    cout <<"ERROR" <<endl;
                cout <<"Again?";
                cin >>response; cin.ignore(100, '\n');
            }while(toupper(response) == 'Y');
        }

        //Removing an item
        if(main_menu == 4)
        {
            cout <<endl;
            cout <<"What is the title of the event you would like to remove?" <<endl;
            cin.get(title, 50, '\n'); cin.ignore(50, '\n');
            cout <<"On which day of the month is the event?" <<endl;
            cin >>day;
            if(!january.remove(day, title))
                cout <<"ERROR" <<endl;
            else
                cout <<"DONE" <<endl;
        }

        //Retrieving an item with RTTI.
        if(main_menu == 5)
        {
            calendar_item *item = NULL;
            meeting *aMeeting = NULL;
            reminder *aReminder = NULL;
            to_do *aList = NULL;

            cout <<endl;
            cout <<"What is the title?" <<endl;
            cin.get(title, 50, '\n'); cin.ignore(50, '\n');
            cout <<"On what day of the month is the event?" <<endl;
            cin >>day;
            if(!january.retrieve(title, item, day))
                cout <<"ERROR" <<endl;
            cout <<endl;
            cout <<"Here's what was found..." <<endl <<endl;

            aMeeting = dynamic_cast<meeting*>(item);	//Downcasting
            if(aMeeting)
            {
                if(!aMeeting -> display())
                    cout <<"ERROR" <<endl;
            }

            aReminder = dynamic_cast<reminder*>(item); 	//Downcasting
            if(aReminder)
            {
                if(!aReminder -> display())
                    cout <<"ERROR" <<endl;
            }

            aList = dynamic_cast<to_do*>(item);		//Downcasting
            if(aList)
            {
                if(!aList -> display())
                    cout <<"ERROR" <<endl;
            }
        }

        //Mark an item complete in the to-do list - RTTI
        if(main_menu == 6)
        {
            calendar_item *item = NULL;
            to_do *toRem = NULL;

            cout <<endl <<endl;
            cout <<"What is the list title?" <<endl;
            cin.get(title, 50, '\n'); cin.ignore(50, '\n');
            cout <<"On what day of the month is the list?" <<endl;
            cin >>day;
            if(!january.retrieve(title, item, day))
                cout <<"ERROR" <<endl;
            toRem = dynamic_cast<to_do*>(item);		//Downcasting
            if(toRem)
            {
                if(!toRem -> complete())
                    cout <<"ERROR" <<endl;
                else
                    cout <<"DONE" <<endl;
            }

        }

        //Display all saved info
        if(main_menu == 7)
        {
            if(!january.display_all())
                cout <<"ERROR" <<endl;
        }

    }while(main_menu != 8);

    return 0;
}