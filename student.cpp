/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #6 - StudentList
* Summary: This collection of files imports a file of a specific layout to an internal array of
*          objects of type Student. The user can then export a grade report that includes various information
*          about each student (Final Grade, Letter Grade, Final Exam Grade).
* This File: student.cpp - Student Function File
*/

#include <cstring>
#include "student.h"
using namespace std;

// First Name Accessor Function
const char *Student::GetFirstName()
{
    return firstName;
}

// Last Name Accessor Function
const char *Student::GetLastName()
{
    return lastName;
}

// Class Name Accessor Function
const char *Student::GetClass()
{
    // Special Case for CS students, since there is a space in "Computer Science"
    if (strcmp(className, "Computer") == 0)
        return "Computer Science";
    else
        return className;
}

// Default Student Constructor - Creates empty character arrays for common data
Student::Student()
{
    firstName[0] = '\0';
    lastName[0] = '\0';
    className[0] = '\0';
}

// Parameterized Student Constructor - Creates Student object based on specified data
Student::Student(const char *l, const char *f, const char *c)
{
    strcpy(lastName, l);
    strcpy(firstName, f);
    strcpy(className, c);
}

// FirstName Mutator Function
void Student::SetFirstName(const char *f)
{
    strcpy(firstName, f);
}

// LastName Mutator Function
void Student::SetLastName(const char* l)
{
    strcpy(lastName, l);
}

// ClassName Mutator Function
void Student::SetClass(const char *c)
{
    strcpy(className, c);
}

// Biology Student Default Constructor - Sets up empty data for Bio grades
Biology::Biology() : Student()
{
    labGrade = 0;
    test1 = 0;
    test2 = 0;
    test3 = 0;
    final = 0;
}

// Parameterized Biology Constructor - Sets up Bio student based on specified data,
// also calls parameterized Student function
Biology::Biology(const char *l, const char *f, const char *c, int lab,
                 int t1, int t2, int t3, int fin) : Student(l, f, c)
{
    labGrade = lab;
    test1 = t1;
    test2 = t2;
    test3 = t3;
    final = fin;
}

// Bio FinalGrade Function - Returns final grade based on Biology class weightings
double Biology::FinalGrade()
{
    double finalGrade;
    finalGrade = (labGrade * 0.30) + ((test1 + test2 + test3) * 0.15) + (final * 0.25);
    return finalGrade;
}

// Final Exam Grade Accessor Function
int Biology::GetFinalExam()
{
    return final;
}

// Theater Student Default Constructor - Sets up empty data for Theater grades
Theater::Theater() : Student()
{
    sceneStudies = 0;
    midterm = 0;
    final = 0;
}

// Parameterized Theater Constructor - Sets up Theater student based on specified data,
// also calls parameterized Student function
Theater::Theater(const char *l, const char *f, const char *c, int p,
                 int m, int fin) : Student(l, f, c)
{
    sceneStudies = p;
    midterm = m;
    final = fin;
}

// Theater FinalGrade Function - Returns final grade based on Theater class weightings
double Theater::FinalGrade()
{
    double finalGrade;
    finalGrade = (sceneStudies * 0.40) + (midterm * 0.25) + (final * 0.35);
    return finalGrade;
}

// Theater Final Exam Grade Accessor Function
int Theater::GetFinalExam()
{
    return final;
}

// CS Student Default Constructor - Sets up empty data for CS grades
ComputerScience::ComputerScience() : Student()
{
    assignAverage = 0;
    test1 = 0;
    test2 = 0;
    final = 0;
}

// Parameterized CS Constructor - Sets up CS student based on specified data,
// also calls parameterized Student function
ComputerScience::ComputerScience(const char *l, const char *f, const char *c,
                                 double a, int t1, int t2, int fin) : Student(l, f, c)
{
    assignAverage = a;
    test1 = t1;
    test2 = t2;
    final = fin;
}

// CS FinalGrade Function - Returns final grade based on CS class weightings
double ComputerScience::FinalGrade()
{
    double finalGrade;
    finalGrade = (assignAverage * 0.30) + (test1 * 0.20) + (test2 * 0.20) + (final * 0.30);
    return finalGrade;
}

// CS Final Exam Grade Accessor Function
int ComputerScience::GetFinalExam()
{
    return final;
}


