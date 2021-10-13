/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #5 - MyInt
* Summary: This collection of files allows the user to store an integer with a theoretically limitless size using
*          arrays.
* This File: myint.h - MyInt Header File
*/

#include <iostream>
using namespace std;

#ifndef MYINT_MYINT_H
#define MYINT_MYINT_H


class MyInt
{
    // Addition and Multiplication Overloads
    friend MyInt operator+ (const MyInt& x, const MyInt& y);
    friend MyInt operator* (const MyInt& x, const MyInt& y);

    // Comparison Overloads
    friend bool operator< (const MyInt& x, const MyInt& y);
    friend bool operator> (const MyInt& x, const MyInt& y);
    friend bool operator<= (const MyInt& x, const MyInt& y);
    friend bool operator>= (const MyInt& x, const MyInt& y);
    friend bool operator== (const MyInt& x, const MyInt& y);
    friend bool operator!= (const MyInt& x, const MyInt& y);

    // User Stream Overloads
    friend ostream& operator<<(ostream& os, const MyInt& i);
    friend istream& operator>>(istream& s, MyInt& i);

public:

    // Constructors
    MyInt(int n = 0);
    MyInt(const char* s);

    // Deconstructor
    ~MyInt();

    // Copy Constructor
    MyInt(const MyInt &i);

    // Assignment Operator
    MyInt& operator=(const MyInt &);

    // Increment Overloads
    MyInt& operator++();
    MyInt operator++(int);
    MyInt& operator--();
    MyInt operator--(int);



private:

    // Private member data + Grow()
    unsigned int *bigNumber;
    int currentSize;
    int maxSize;
    void Grow();

};

#endif //MYINT_MYINT_H
