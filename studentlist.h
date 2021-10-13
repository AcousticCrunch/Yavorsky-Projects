/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #6 - StudentList
* Summary: This collection of files imports a file of a specific layout to an internal array of
*          objects of type Student. The user can then export a grade report that includes various information
*          about each student (Final Grade, Letter Grade, Final Exam Grade).
* This File: studentlist.h - StudentList Header File
*/

#ifndef STUDENTLIST_STUDENTLIST_H
#define STUDENTLIST_STUDENTLIST_H

#include <iostream>
#include "student.h"
using namespace std;

// StudentList Class - holds array of Student pointers
class StudentList
{
public:
    // Constructor and Destructor
    StudentList();
    ~StudentList();

    // Import File Function
    bool ImportFile(const char* filename);

    // Export Report File Function
    bool CreateReportFile(const char* filename);

    // Show (Brief) List of Students Function
    const void ShowList() const;

private:
    // private member data and functions
    char LetterGrade(double f);
    void Grow(int s);
    int currentSize;
    int counter = 0;
    Student **studentList;
};

#endif //STUDENTLIST_STUDENTLIST_H
