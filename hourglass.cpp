/* Name: Hunter Yavorsky
 * Course: COP3330 - Sec 0006
 * Project: Assignment #1 - Hourglass
 * Summary: A class (hourglass.h) that takes in a size of a equilateral hourglass.
 *          Also provides the user with functions to calculate area, perimeter
 *          and display the hourglass in ASCII formatting, as well as a summary function
 * This File: hourglass.cpp - Function File
 */

#include <iomanip>
#include <iostream>
#include <cmath>
#include "hourglass.h"

using namespace std;


/**********************************
 * Hourglass Constructor Function *
 **********************************/
Hourglass::Hourglass(int s, char b, char f)
{
    if (s < 1)                                  // if statements to error check values are within range
        size = 1;
    else if (s > 39)
        size = 39;
    else
        size = s;

    border = b;                                // sets border and fill characters
    fill = f;
}
/********************
 * GetSize Function *
 ********************/
int Hourglass::GetSize() const
{
    return size;                               // returns size of hourglass
}

/**********************
 * Perimeter Function *
 **********************/
int Hourglass::Perimeter() const
{
    return size * 6;                           // returns perimeter of hourglass
}

/*****************
 * Area Function *
 *****************/
double Hourglass::Area() const
{
    return (0.5*(sqrt(3)*(size*size)));     // area of equilateral hourglass = 2(1/4(sqrt(3)*(side length^2)))
}

/*****************
 * Grow Function *
 *****************/
void Hourglass::Grow()
{
    if (size == 39)                             // if statement to error check if hourglass is already at
        return;                                 // largest size
    else
        size += 1;
}

/*******************
 * Shrink Function *
 *******************/
void Hourglass::Shrink()
{
    if (size == 1)                              // if statement to error check if hourglass is already at
        return;                                 // smallest size
    else
        size -= 1;
}

/**********************
 * SetBorder Function *
 **********************/
void Hourglass::SetBorder(char b)
{
    if (b < 33 || b > 126)                      // if statement to error check if border value is within
        border = '#';                           // accepted value range
    else
        border = b;
}

/********************
 * SetFill Function *
 ********************/
void Hourglass::SetFill(char f)
{
    if (f < 33 || f > 126)                      // if statement to error check if fill value is within
        fill = '*';                             // accepted value range
    else
        fill = f;
}

/*****************
 * Draw Function *
 *****************/
void Hourglass::Draw() const
{

    for (int rows = size; rows > 1; rows--)                         // top triangle row loop
    {

        for (int space = rows; space < size; space++)               // top triangle space loop
        {
            cout << " ";
        }

        for (int columns = 1; columns <= rows; columns++)           // top triangle column loop
        {
            if (rows == size || columns == rows || columns == 1)    // if statements to determine border and
            {                                                       // fill character locations
                cout << border << " ";
            }
            else
            {
                cout << fill << " ";
            }

        }
        cout << endl;
    }

    for(int rows2 = 1; rows2 <= size; rows2++)                      // bottom triangle row loop (inverse of
    {                                                               // top triangle)

        for(int space = rows2; space < size; space++)               // bottom triangle space loop
        {
            cout << " ";
        }

        for(int columns2 = 1; columns2 <= rows2; columns2++)        // bottom triangle column loop
        {
            if(rows2 == size || columns2 == rows2 || columns2 == 1) // same strategy as top triangle to find location
            {                                                       // of border and fill characters
                cout << border << " ";
            }
            else
            {
                cout << fill << " ";
            }
        }
        cout << endl;
    }
}

/********************
 * Summary Function *
 ********************/
void Hourglass::Summary() const                                     // prints information of particular hourglass and
{                                                                   // displays hourglass
    cout << "Size of hourglass's side = " << size << " units." << endl;
    cout << "Perimeter of hourglass's side = " << Perimeter() << " units." << endl;
    cout << "Area of hourglass = " << fixed << setprecision(2) << Area() << " units." << endl;
    cout << "Hourglass looks like:" << endl;
    Draw();
}