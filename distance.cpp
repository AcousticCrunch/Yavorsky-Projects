/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #3 - Distance
* Summary: A class (distance.h) that calculates a programmer's distance
*         input (miles, yards, feet, inches) and converts it to its
*         simplest form. It also has operator overloads that makes
*         comparing and altering the objects easy for the programmer.
* This File: distance.cpp - Function File
*/
#include <iostream>
#include "distance.h"

using namespace std;

/***********************
 * Default Constructor *
 ***********************/
Distance::Distance()
{
    miles = 0;                      // default values will be 0 for new objects
    yards = 0;
    feet = 0;
    inches = 0;
}

/**********************
 * Inches Constructor *
 **********************/
Distance::Distance(int i)
{

    if (i < 0)
    {
        miles = 0;                  // defaults values if there are negatives
        yards = 0;
        feet = 0;
        inches = 0;
    }
    else
    {
        inches = i;                 // converts inches entered to respective scales of distances

        miles = inches / 63360;
        inches = inches % 63360;

        yards = inches / 36;
        inches = inches % 36;

        feet = inches / 12;
        inches = inches % 12;       // stores values in member data
    }
}

/**********************
 * Manual Constructor *
 **********************/
Distance::Distance(int m, int y, int f, int i)
{
    miles = m;                                      // takes in values as variables
    yards = y;
    feet = f;
    inches = i;

    if (m < 0 || y < 0 || f < 0 || i < 0)
    {
        miles = 0;                                   // defaults if there are any negatives
        yards = 0;
        feet = 0;
        inches = 0;
    }
    else
    {
        feet += inches / 12;                         // converts the values to their simplest form
        inches = inches % 12;

        yards += feet / 3;
        feet = feet % 3;

        miles += yards / 1760;
        yards = yards % 1760;
    }

}

/**** ************
 * Cout Operator *
 *****************/
ostream& operator<< (ostream& s, const Distance& d)
{
    s << '(';
    if (d.miles != 0)
        s << d.miles << "m ";                           // formats the object data as (Milesm, Yardsy, Feet', Inches")
    if (d.yards != 0)
        s << d.yards << "y ";
    if (d.feet != 0)
        s << d.feet << "' ";
    s << d.inches << '"' << ')' << endl;
    return s;
}

/****************
 * Cin Operator *
 ****************/
istream& operator>> (istream& s, Distance& d)
{
    char comma;

    s >> d.miles >> comma;                               // user input is assumed as miles, yards, feet, inches
    s >> d.yards >> comma;
    s >> d.feet >> comma;
    s >> d.inches;

    if (d.inches < 0 || d.feet < 0 || d.yards < 0 || d.miles < 0)
    {
        d.inches = 0;
        d.feet = 0;                                       // error checks for negatives
        d.yards = 0;
        d.miles = 0;
    }

    d.feet += d.inches / 12;                              // simplifies input
    d.inches = d.inches % 12;

    d.yards += d.feet / 3;
    d.feet = d.feet % 3;

    d.miles += d.yards / 1760;
    d.yards = d.yards % 1760;

    return s;
}

/*********************
 * Addition Operator *
 *********************/
Distance operator+(const Distance& d1, const Distance& d2)
{
    Distance d3;

    d3.inches = d1.inches + d2.inches;                      // adds each element of objects
    d3.feet = d1.feet + d2.feet;
    d3.yards = d1.yards + d2.yards;
    d3.miles = d1.miles + d2.miles;

    d3.feet += d3.inches / 12;                              // simplifies new object
    d3.inches = d3.inches % 12;

    d3.yards += d3.feet / 3;
    d3.feet = d3.feet % 3;

    d3.miles += d3.yards / 1760;
    d3.yards = d3.yards % 1760;

    return d3;
}

/************************
 * Subtraction Operator *
 ************************/
Distance operator-(const Distance& d1, const Distance& d2)
{
    Distance d3;

    d3.inches = d1.inches - d2.inches;                      // subtracts each element of objects
    d3.feet = d1.feet - d2.feet;
    d3.yards = d1.yards - d2.yards;
    d3.miles = d1.miles - d2.miles;

    if (d3.inches < 0 || d3.feet < 0 || d3.yards < 0 || d3.miles < 0)
    {
        d3.inches = 0;
        d3.feet = 0;                                        // checks if subtraction will create a negative value,
        d3.yards = 0;                                       // and sets object to default if it occurs
        d3.miles = 0;
    }


    d3.feet += d3.inches / 12;
    d3.inches = d3.inches % 12;                             // simplifies new object

    d3.yards += d3.feet / 3;
    d3.feet = d3.feet % 3;

    d3.miles += d3.yards / 1760;
    d3.yards = d3.yards % 1760;

    return d3;
}

/***************************
 * Multiplication Operator *
 ***************************/
Distance operator*(const Distance& d1, const int i)
{
    Distance d3;

    d3.inches = d1.inches * i;
    d3.feet = d1.feet * i;                          // multiplies each element of objects
    d3.yards = d1.yards * i;
    d3.miles = d1.miles * i;

    d3.feet += d3.inches / 12;
    d3.inches = d3.inches % 12;                     // simplifies new object

    d3.yards += d3.feet / 3;
    d3.feet = d3.feet % 3;

    d3.miles += d3.yards / 1760;
    d3.yards = d3.yards % 1760;

    return d3;
}

/**********************
 * Less Than Operator *
 **********************/
bool operator<(const Distance& d1, const Distance& d2)
{

     if (d1.miles < d2.miles)                                   // multiple tests to rule out equal member data
         return true;
     if (d1.miles == d2.miles && d1.yards < d2.yards)
         return true;
     if (d1.miles == d2.miles && d1.yards == d2.yards && d1.feet < d2.feet)
         return true;
    if (d1.miles == d2.miles && d1.yards == d2.yards && d1.feet == d2.feet && d1.inches < d2.inches)
        return true;
    else
        return false;                                           // if all tests are false, object is not less than

}
/*************************
 * Greater Than Operator *
 *************************/
bool operator>(const Distance& d1, const Distance& d2)
{
    return (d2 < d1);                                           // calls on a backwards less than operation
}

/*************************************
 * Less Than or Equal To Operator *
 *************************************/
bool operator<=(const Distance& d1, const Distance& d2)
{
    return !(d1 > d2);                                          // calls on an inverse of the greater than operation
}

/*************************************
 * Greater Than or Equal To Operator *
 *************************************/
bool operator>=(const Distance& d1, const Distance& d2)
{
    return !(d1 < d2);                                           // calls on an inverse to the less than operation
}

/*********************
 * Equal To Operator *
 *********************/
bool operator==(const Distance& d1, const Distance& d2)
{
    if (d1.miles != d2.miles)                               // uses nested if/else statements to check the opposite
        return false;                                       // cases to test if objects are not equal
    else
    {
        if (d1.yards != d2.yards)
            return false;
        else
        {
            if (d1.feet != d2.feet)
                return false;
            else
            {
                if (d1.inches != d2.inches)
                    return false;
                else
                    return true;
            }
        }
    }
}

/*************************
 * Not Equal To Operator *
 *************************/
bool operator!=(const Distance& d1, const Distance& d2)
{
    return !(d1 == d2);
}

/*******************************
 * PreFix + Increment Operator *
 *******************************/
Distance& Distance::operator++()
{
    inches += 1;                                        // adds 1 to object's inches member data
    feet += inches / 12;
    inches = inches % 12;                               // simplifies object

    yards += feet / 3;
    feet = feet % 3;

    miles += yards / 1760;
    yards = yards % 1760;
    return *this;                                       // returns reference to the object being incremented
}


/********************************
 * PostFix + Increment Operator *
 ********************************/
Distance Distance::operator++(int)
{
    Distance temp = *this;                              // makes a copy of the object to a reference
    inches += 1;                                        // adds 1 to object's inches member data
    feet += inches / 12;
    inches = inches % 12;                               // simplifies object

    yards += feet / 3;
    feet = feet % 3;

    miles += yards / 1760;
    yards = yards % 1760;

    return temp;                                        // returns reference BEFORE incrementation
}

/*******************************
 * PreFix - Increment Operator *
 *******************************/
Distance& Distance::operator--()
{
    if (inches == 0)                                     // if statement to check if inches is already 0
        return *this;                                    // and returns nothing if this is the case

    inches -= 1;                                         // subtracts 1 from object's inches member data
    feet += inches / 12;
    inches = inches % 12;                                // simplifies object

    yards += feet / 3;
    feet = feet % 3;

    miles += yards / 1760;
    yards = yards % 1760;
    return *this;                                        // returns reference to the object being incremented
}

/********************************
 * PostFix - Increment Operator *
 ********************************/
Distance Distance::operator--(int)
{
    if (inches == 0)                                      // if statement to check if inches is already 0
        return *this;                                     // and returns nothing i this is the case

    Distance temp = *this;                                // makes a copy of the object to a reference
    inches -= 1;                                          // subtracts 1 from object's inches member data
    feet += inches / 12;
    inches = inches % 12;                                 // simplifies object

    yards += feet / 3;
    feet = feet % 3;

    miles += yards / 1760;
    yards = yards % 1760;
    return temp;                                           // returns reference BEFORE incrementation
}



