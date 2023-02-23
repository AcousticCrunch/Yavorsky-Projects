/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #6 - StudentList
* Summary: This collection of files imports a file of a specific layout to an internal array of
*          objects of type Student. The user can then export a grade report that includes various information
*          about each student (Final Grade, Letter Grade, Final Exam Grade).
* This File: student.h - Student Header File
*/

#ifndef STUDENTLIST_STUDENT_H
#define STUDENTLIST_STUDENT_H

using namespace std;

// Abstract Student Class - holds Student Data
class Student
{
public:
    // Pure Virtual FinalGrade and GetFinalExam Functions
    virtual double FinalGrade() = 0;
    virtual int GetFinalExam() = 0;

    // Common Data - Accessor and Mutator Functions
    const char* GetFirstName();
    void SetFirstName(const char *f);
    const char* GetLastName();
    void SetLastName(const char* l);
    const char* GetClass();
    void SetClass(const char* c);

protected:
    // Protected common member data
    Student();
    Student(const char* l, const char* f, const char* c);
    char firstName[20];
    char lastName[20];
    char className[20];
};

// Child Bio Class
class Biology: public Student
{
public:
    // Default Constructor
    Biology();

    // Parameterized Constructor
    Biology(const char* l, const char* f, const char* c, int lab, int t1, int t2, int t3, int fin);

    // FinalGrade Function
    double FinalGrade();

    // Final Grade Accessor
    int GetFinalExam();

private:
    // private Bio member data
    int labGrade,
        test1,
        test2,
        test3,
        final;
};

// Child Theater Class
class Theater: public Student
{
public:
    // Default Constructor
    Theater();

    // Parameterized Constructor
    Theater(const char* l, const char* f, const char* c, int p, int m, int fin);

    // FinalGrade Function
    double FinalGrade();

    // Final Grade Accessor
    int GetFinalExam();
private:
    // private Theater member data
    int sceneStudies,
        midterm,
        final;
};

// Child CS Class
class ComputerScience: public Student
{
public:
    // Default Constructor
    ComputerScience();

    // Parameterized Constructor
    ComputerScience(const char* l, const char* f, const char* c, double a, int t1, int t2, int fin);

    // FinalGrade Function
    double FinalGrade();

    // Final Grade Accessor
    int GetFinalExam();
private:
    // private CS member data
    double assignAverage;
    int test1,
        test2,
        final;
};

#endif //STUDENTLIST_STUDENT_H
