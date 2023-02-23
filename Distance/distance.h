/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #3 - Distance
* Summary: A class (distance.h) that calculates a programmer's distance
*          input (miles, yards, feet, inches) and converts it to its
 *         simplest form. It also has operator overloads that makes
 *         comparing and altering the objects easy for the programmer.
* This File: distance.h - Header File
*/
#include <iostream>
using namespace std;


class Distance
{
    // Operator Overload Friend Functions

    // Cout and Cin Functions
    friend ostream& operator<<(ostream& s, const Distance& d);
    friend istream& operator>>(istream& s, Distance& d);

    // Mathematical Functions
    friend Distance operator+(const Distance&, const Distance&);
    friend Distance operator-(const Distance&, const Distance&);
    friend Distance operator*(const Distance& d1, const int);

    // Comparison Functions
    friend bool operator<(const Distance&, const Distance&);
    friend bool operator>(const Distance&, const Distance&);
    friend bool operator<=(const Distance&, const Distance&);
    friend bool operator>=(const Distance&, const Distance&);
    friend bool operator==(const Distance&, const Distance&);
    friend bool operator!=(const Distance&, const Distance&);


    public:
    // Constructors
    Distance();
    Distance(int);
    Distance(int, int, int, int);

    // Increment Functions
    Distance& operator++();
    Distance operator++(int);
    Distance& operator--();
    Distance operator--(int);

    private:
    // Member Data
    int miles;
    int yards;
    int feet;
    int inches;


};
