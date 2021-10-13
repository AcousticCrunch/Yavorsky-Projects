/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #6 - StudentList
* Summary: This collection of files imports a file of a specific layout to an internal array of
*          objects of type Student. The user can then export a grade report that includes various information
*          about each student (Final Grade, Letter Grade, Final Exam Grade).
* This File: studentlist.cpp - StudentList Function File
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "studentlist.h"
using namespace std;

// Letter Grade Function
char StudentList::LetterGrade(double f)
{
    // Returns letter grade based on passed-in final average grade
    if (f >= 90.0 && f <= 100.0)
        return 'A';

    if (f >= 80.0 && f <= 89.0)
        return 'B';

    if (f >= 70.0 && f <= 79.0)
        return 'C';

    if (f >= 60.0 && f <= 69.0)
        return 'D';

    if (f <= 59.0 && f >= 0.0)
        return 'F';
}

// Grow Function - Grows Array to new size
void StudentList::Grow(int s)
{
    // Assigns nullptr to brand new, empty array of specified size
    if (studentList == nullptr)
    {
        studentList = new Student*[s];
        currentSize += s;
    }

    // Copies over old data from old array into new array, deleting the old one and assigning
    // pointer to new array
    else
    {
        Student **newList = new Student*[currentSize + s];
        for (int count = 0 ; count < currentSize; count++)
            newList[count] = studentList[count];

        delete [] studentList;

        studentList = newList;
        currentSize += s;
    }

}

// Default Constructor - Sets up empty pointer and 0 size
StudentList::StudentList()
{
    studentList = nullptr;
    currentSize = 0;
}

// Destructor - Deallocates all the data in the array, one by one
StudentList::~StudentList()
{
    for (int count = currentSize; count <= 0; count--)
        delete studentList[count];
}

// Import File Function - Imports student file to array
bool StudentList::ImportFile(const char *filename)
{
    // Creates new ifstream object
    ifstream infile;

    infile.open(filename);

    // If file cannot be opened, return false
    if (!infile)
        return false;

    // Reads in size increase and calls Grow function to grow array size
    int sizeIncrease;
    infile >> sizeIncrease;
    Grow(sizeIncrease);

    // do - while to loop through file
    do
    {
        char firstNameBuf[20];
        char lastNameBuf[20];
        char classNameBuf[20];

        // ignores first '\n'
        infile.ignore(1);

        // assigns last name, stopping at ','
        infile.getline(lastNameBuf, 20, ',');

        // ignores space
        infile.ignore(1);

        // assigns first name, stopping at '\n'
        infile.getline(firstNameBuf, 20);

        // assigns className
        infile >> classNameBuf;

        // if statements to make sure to read in correct data in correct order, as well as create correct dynamic object
        if (strcmp(classNameBuf, "Biology") == 0)
        {

            int labGrade, t1, t2, t3, final;

            // reads in lab and test grades
            infile >> labGrade >> t1 >> t2 >> t3 >> final;

            // creates new biology student with all the parameters read in, and places in correct spot in array
            studentList[counter] = new Biology(lastNameBuf, firstNameBuf, classNameBuf, labGrade, t1, t2, t3, final);

        }

        if (strcmp(classNameBuf, "Theater") == 0)
        {
            int sceneStudies, midTerm, final;

            // reads in participation, midterm and final grade
            infile >> sceneStudies >> midTerm >> final;

            // creates new theater student with parameters read in
            studentList[counter] = new Theater(lastNameBuf, firstNameBuf, classNameBuf, sceneStudies, midTerm, final);
        }

        if (strcmp(classNameBuf, "Computer") == 0)
        {
            // reads in next word to buffer variable
            string Science;
            infile >> Science;

            int read;
            int sum = 0;

            // reads in 6 assignment grades
            for(int i = 1; i <= 6; i++)
            {
                infile >> read;
                sum += read;
            }

            // calculates assignment average
            double average = sum/6.00;
            int t1, t2, final;

            // reads in tests and final grades
            infile >> t1 >> t2 >> final;

            // creates new CS student with parameters read in
            studentList[counter] = new ComputerScience(lastNameBuf, firstNameBuf, classNameBuf, average, t1, t2, final);

        }

        // increments counter variable
        counter++;

        // loop stops if counter = currentSize
    }while (counter < currentSize);

    // closes import file and returns true
    infile.close();
    return true;
}


// Create Report File Function - Exports file of specific format using array data
bool StudentList::CreateReportFile(const char *filename)
{
    // creates new ofstream object
    ofstream outFile;

    outFile.open(filename);

    // if file cannot open, return false
    if (!outFile)
        return false;

    // sets default fill to holder variable to be used to default to blankspace later
    char defaultFill = outFile.fill();

    // writes Biology header
    outFile << "Student Grade Summary\n"
            << "---------------------\n\n"
            << "BIOLOGY CLASS\n\n"
            << left << setw(60) << "Student" << setw(6) << "Final" << setw(8) << "Final" << "Letter\n"
            << left << setw(60) << "Name" << setw(6)    << "Exam"  << setw(8) << "Avg"   << "Grade\n"
            << setw(80) << setfill('-') << "" << endl
            << setfill(defaultFill);

    // loops through array and prints every Biology student, with final exam grade, final average and letter grade
    for(int count = 0; count < currentSize; count++)
    {
        if (strcmp(studentList[count]->GetClass(), "Biology") == 0)
        {
            int whiteSpace = strlen(studentList[count]->GetFirstName()) + strlen(studentList[count]->GetLastName() + 1);
            streamsize initialPrecision = outFile.precision();
            outFile << studentList[count]->GetFirstName() << " "
                    << studentList[count]->GetLastName();
                    for (int i = 1; i<= 60 - whiteSpace; i++)
                        outFile << " ";
            outFile << setw(6) << studentList[count]->GetFinalExam() << setw(8) << setprecision(4)
                    << studentList[count]->FinalGrade() << setprecision(initialPrecision)
                    << LetterGrade(studentList[count]->FinalGrade()) << endl;
        }
    }

    // prints Theater header
    outFile << "\n\n\n"
            << "THEATER CLASS\n\n"
            << left << setw(60) << "Student" << setw(6) << "Final" << setw(8) << "Final" << "Letter\n"
            << left << setw(60) << "Name" << setw(6)    << "Exam"  << setw(8) << "Avg"   << "Grade\n"
            << setw(80) << setfill('-') << "" << endl
            << setfill(defaultFill);


    // loops through array and prints every Theater student with final exam, final grade and letter grade
    for(int count = 0; count < currentSize; count++)
    {
        if (strcmp(studentList[count]->GetClass(), "Theater") == 0)
        {
            int whiteSpace = strlen(studentList[count]->GetFirstName()) + strlen(studentList[count]->GetLastName() + 1);
            streamsize initialPrecision = outFile.precision();
            outFile << studentList[count]->GetFirstName() << " "
                    << studentList[count]->GetLastName();
                    for (int i = 1; i<= 60 - whiteSpace; i++)
                        outFile << " ";
            outFile << setw(6) << studentList[count]->GetFinalExam() << setw(8) << setprecision(4)
                    << studentList[count]->FinalGrade() << setprecision(initialPrecision)
                    << LetterGrade(studentList[count]->FinalGrade()) << endl;
        }
    }

    // prints CS header
    outFile << "\n\n\n"
            << "COMPSCI CLASS\n\n"
            << left << setw(60) << "Student" << setw(6) << "Final" << setw(8) << "Final" << "Letter\n"
            << left << setw(60) << "Name" << setw(6)    << "Exam"  << setw(8) << "Avg"   << "Grade\n"
            << setw(80) << setfill('-') << "" << endl
            << setfill(defaultFill);

    // loops through array and prints every CS student with final exam grade, final grade and letter grade
    for(int count = 0; count < currentSize; count++)
    {
        if (strcmp(studentList[count]->GetClass(), "Computer Science") == 0)
        {
            int whiteSpace = strlen(studentList[count]->GetFirstName()) + strlen(studentList[count]->GetLastName() + 1);
            streamsize initialPrecision = outFile.precision();
            outFile << studentList[count]->GetFirstName() << " "
                    << studentList[count]->GetLastName();
                    for (int i = 1; i<= 60 - whiteSpace; i++)
                        outFile << " ";
            outFile << setw(6) << studentList[count]->GetFinalExam() << setw(8) << setprecision(4)
                    << studentList[count]->FinalGrade() << setprecision(initialPrecision)
                    << LetterGrade(studentList[count]->FinalGrade()) << endl;
        }
    }

    // prints overall grade distribution based on letter grade
    outFile << "\n\n\n"
            << "OVERALL GRADE DISTRIBUTION"
            << "\n\n";

    // uses counter variables
    int A_COUNTER = 0;
    int B_COUNTER = 0;
    int C_COUNTER = 0;
    int D_COUNTER = 0;
    int F_COUNTER = 0;

    // loops through array and increments corresponding counter variables
    for (int count = 0; count < currentSize; count++)
    {
        if ((LetterGrade(studentList[count]->FinalGrade())) == 'A')
            A_COUNTER++;
        if ((LetterGrade(studentList[count]->FinalGrade())) == 'B')
            B_COUNTER++;
        if ((LetterGrade(studentList[count]->FinalGrade())) == 'C')
            C_COUNTER++;
        if ((LetterGrade(studentList[count]->FinalGrade())) == 'D')
            D_COUNTER++;
        if ((LetterGrade(studentList[count]->FinalGrade())) == 'F')
            F_COUNTER++;
    }

    // prints variables in columns
    outFile << "A:" << right << setw(6) << A_COUNTER << endl
            << "B:" << setw(6) << B_COUNTER << endl
            << "C:" << setw(6) << C_COUNTER << endl
            << "D:" << setw(6) << D_COUNTER << endl
            << "F:" << setw(6) << F_COUNTER;

    // closes file and returns true
    outFile.close();
    return true;
}

// Show List Function - Shows brief list of students in array
const void StudentList::ShowList() const
{
    // prints column headers of Last name, First name, and Course name
    cout << left
         << setw(21) << "Last"
         << setw(21) << "First"
         << setw(21) << "Course" << "\n\n";

    // loops through array and prints corresponding data
    for (int count = 0; count < currentSize; count++)
    {
        cout << setw(21) << studentList[count]->GetLastName();
        cout << setw(21) << studentList[count]->GetFirstName();
        cout << setw(21) << studentList[count]->GetClass();
        cout << endl;
    }
}

