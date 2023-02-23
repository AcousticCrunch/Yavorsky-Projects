/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #6 - StudentList
* Summary: This collection of files imports a file of a specific layout to an internal array of
*          objects of type Student. The user can then export a grade report that includes various information
*          about each student (Final Grade, Letter Grade, Final Exam Grade).
* This File: main.cpp - Main Menu Function
*/

#include <iostream>
#include <iomanip>
#include "studentlist.h"

using namespace std;

// Main Menu Function - Loops user through menu based interface
int main()
{
    // creates StudentList object to hold data
    StudentList list;
    char selection;

    // keepLooping variable will break loop if user selects 'Q'
    bool keepLooping = true;

    do
    {

        // Prompts user for input
        cout << "        " << "*** Student List Menu ***" << endl
             << left << setw(8) << "I" << "Import Students from a file" << endl
             << setw(8) << "S" << "Show student list (brief)" << endl
             << setw(8) << "E" << "Export a Grade Report (to file)" << endl
             << setw(8) << "M"  << "Show this Menu" << endl
             << setw(8) << "Q" << "Quit Program" << endl;

        cin >> selection;

        switch (selection)
        {
            // Import Student Selection
            case 'I':
            case 'i':
            {
                char filename[30];

                // prompts user for filename and attempts to import file to array
                cout << "Enter Filename: ";
                cin >> filename;

                // if unsuccessful, returns error message
                if (!list.ImportFile(filename))
                    cout << "Could not import file. Process aborted" << endl;

                break;
            }

            // Show (Brief) List Selection
            case 'S':
            case 's':
            {
                // Simply calls ShowList function
                list.ShowList();
                break;
            }

            // Export Report File Selection
            case 'E':
            case 'e':
            {
                char filename[30];

                // prompts user for filename and attempts to open new file to write to
                cout << "Enter Filename: ";
                cin >> filename;

                // if unsuccessful, returns error message
                if (!list.CreateReportFile(filename))
                    cout << "Could not create file. Process aborted" << endl;

                break;
            }

            // Show Menu Again Selection
            case 'M':
            case 'm':
                break;

            // Quit
            case 'Q':
            case 'q':
            {
                cout << "Goodbye!" << endl;

                // marks looping variable as false to break loop
                keepLooping = false;
                break;
            }

            // If input is not of specified characters, display error message and prompt user for input again
            default:
            {
                cout << "Invalid Selection! Please try again." << endl;
                break;
            }
        }
        // loops until variable is set as false
    } while (keepLooping);

    return 0;
}
