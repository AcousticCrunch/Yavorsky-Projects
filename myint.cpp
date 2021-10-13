/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #5 - MyInt
* Summary: This collection of files allows the user to store an integer with a theoretically limitless size using
*          arrays.
* This File: myint.cpp - MyInt Program File
*/



#include <iostream>
#include <cstring>
#include <cmath>
#include "myint.h"

using namespace std;

int C2I(char c)
// converts character into integer (returns -1 for error)
{
    if (c < '0' || c > '9')	return -1;	// error
    return (c - '0');				// success
}

char I2C(int x)
// converts single digit integer into character (returns '\0' for error)
{
    if (x < 0 || x > 9)		return '\0';	// error
    return (static_cast<char>(x) + '0'); 	// success
}

// Cout Overload
ostream &operator<<(ostream& os, const MyInt& i)
{
    for (int count = 0; count < i.currentSize; count++)
        os << i.bigNumber[count];                       // Prints entire array using for loop

    return os;
}

// Cin overload
istream &operator>>(istream &s, MyInt &i)
{
    i = 0;
    int count = 0;
    char whitespace;
    char peek;

    peek = s.peek();
    while (isspace(peek))
    {
        s.get(whitespace);
        peek = s.peek();                        // Uses peek() to see if there is leading whitespace
    }

    do
    {
        i.currentSize++;
        if (i.currentSize == i.maxSize)                     // increases size of array
            i.Grow();

        i.bigNumber[count] = C2I(s.get());                  // assigns numbers 1 by 1 to buffer
        if (C2I(s.get()) == -1)
        {
            cout << "Invalid String" << endl;               // Error checks buffer
            i.currentSize = 1;
            i.bigNumber[0] = 0;
            break;
        }

        count++;                                            // increments counter and checks next space to
        peek = s.peek();                                    // see if loop can stop
    }
    while (isdigit(peek));

    if(isalpha(peek) || isspace(peek))
        return s;                                           // returns buffer when encountering a space or char

}

// Addition Overload
MyInt operator+(const MyInt &x, const MyInt &y)
{
    MyInt z;
    int carryNumber = 0;
    int xCounter = x.currentSize - 1;
    int yCounter = y.currentSize - 1;

    if (x.currentSize >= y.currentSize)             // Case if first variable is bigger or equal in terms of places
    {

        while (z.currentSize != x.currentSize)
        {
            z.currentSize++;
            if (z.currentSize == z.maxSize)         // increases size of object array to new size
                z.Grow();
        }




        int sum[z.maxSize];                         // creates separate sum array
        while (xCounter >= 0)
        {

            sum[xCounter] = x.bigNumber[xCounter] + y.bigNumber[yCounter] + carryNumber;        // adds numbers
                                                                                                // to sum array

            if (sum[0] >= 10)                                                           // if statement to check
            {                                                                           // if number is increasing
                                                                                        // in places

                z.currentSize++;                                                        // increments size of array
                if (z.currentSize == z.maxSize)
                    z.Grow();


                for (int count = 0; count < z.currentSize - 1; count++)
                {
                    z.bigNumber[count + 1] = z.bigNumber[count];                        // for loops to shift numbers
                    sum[count + 1] = sum[count];                                        // down 1 spot
                }

                z.bigNumber[1] = sum[1] % 10;                                           // calculates sum and
                carryNumber = sum[1] / 10;                                              // carries number into new spot
                z.bigNumber[0] = carryNumber;
                break;                                                                  // ends loop
            }

            z.bigNumber[xCounter] = sum[xCounter] % 10;                                 // adds remainder to specified
                                                                                        // array spot
            carryNumber = sum[xCounter] / 10;                                           // carry number is specified if
                                                                                        // needed

            xCounter--;
            yCounter--;



        }

    }

    else                                                                        // replication of above statement
    {                                                                           // only second number is bigger
                                                                                // in places

        while (z.currentSize != y.currentSize)
        {
            z.currentSize++;
            if (z.currentSize == z.maxSize)
                z.Grow();
        }

        int sum[z.maxSize];

        while (yCounter >= 0)
        {

            sum[yCounter] = x.bigNumber[xCounter] + y.bigNumber[yCounter] + carryNumber;

            if (sum[0] >= 10)
            {
                z.currentSize++;
                if (z.currentSize == z.maxSize)
                    z.Grow();


                for (int count = 0; count < z.currentSize - 1; count++)
                {
                    z.bigNumber[count + 1] = z.bigNumber[count];
                    sum[count + 1] = sum[count];
                }
                cout << z.bigNumber[0] << endl;
                cout << z.bigNumber[1] << endl;
                cout << z.bigNumber[2] << endl;
                z.bigNumber[1] = sum[1] % 10;
                carryNumber = sum[1] / 10;
                z.bigNumber[0] = carryNumber;
                break;
            }

            z.bigNumber[yCounter] = sum[yCounter] % 10;
            carryNumber = sum[yCounter] / 10;
            xCounter--;
            yCounter--;
        }
    }

    return z;                                               // returns result as a MyInt object
}

// Multiplication Overload
MyInt operator*(const MyInt& x, const MyInt& y)
{

    return MyInt();
}

// Less Than Overload
bool operator<(const MyInt &x, const MyInt &y)
{
    if (x.currentSize < y.currentSize)          // Test if the places are less than, returns true
        return true;
    if (x.currentSize > y.currentSize)          // Test if the places are greater than, returns false
        return false;
    else
    {
        for (int count = 0; count < x.currentSize; count++)
        {
            if (x.bigNumber[count] < y.bigNumber[count])        // If places are equal, returns true if number
                                                                // is less than
                return true;
        }
        return false;
    }

}

// Greater than Overload
bool operator>(const MyInt &x, const MyInt &y)
{
    return !operator<=(x, y);           // opposite of less than or equal to
}

// Less than or equal to Overload
bool operator<=(const MyInt &x, const MyInt &y)
{
    bool equal;
    if (x.currentSize < y.currentSize)                      // Test if the places are less than, returns true
        return true;
    if (x.currentSize > y.currentSize)                      // Test if the places are greater than, returns false
        return false;
    else
    {
        for (int count = 0; count < x.currentSize; count++)
        {
            if (x.bigNumber[count] < y.bigNumber[count])            // If places are equal, returns true if number
                                                                    // is less than
                return true;
            if (x.bigNumber[count] == y.bigNumber[count])           // If numbers are equal, returns true
                equal = true;
            else
                equal = false;
        }
        if (equal)
            return true;

        return false;
    }
}

// Less than or equal to operator
bool operator>=(const MyInt &x, const MyInt &y)
{
    return !operator<(x, y);        // opposite of less than operator
}

// Equal to operator
bool operator==(const MyInt &x, const MyInt &y)
{
    bool equal;

    if (x.currentSize > y.currentSize || x.currentSize < y.currentSize)         // If any places are less than or
        return false;                                                           // greater than, return false
    else
    {
        for (int count = 0; count < x.currentSize; count++)                     // If places are equal, test to see
        {                                                                       // if numbers are equal, return true
            if (x.bigNumber[count] == y.bigNumber[count])
                equal = true;
            else
                equal = false;
        }
    }
    if (equal)
        return true;

    return false;
}

// Not equal to operator
bool operator!=(const MyInt &x, const MyInt &y)
{
    return !operator==(x, y);               // opposite of equal to operator
}

// Grow Function
void MyInt::Grow()
{
    maxSize = currentSize + 5;                          // increases size of maxSize by 5
    unsigned int *newArray = new unsigned int[maxSize];         // assigns pointer to new array
    for (int count = 0; count < currentSize; count++)
        newArray[count] = bigNumber[count];                     // copies old array contents to new array

    delete[] bigNumber;                                     // deletes old array
    bigNumber = newArray;                                   // assigns pointer to new array
}

// Int Constructor
MyInt::MyInt(int n)
{
    unsigned int newNumber = n;
    unsigned int counterN = n;
    int digitExtractor;
    int counter = 0;
    maxSize = 5;
    bigNumber = new unsigned int [maxSize];
    currentSize = 0;

    if (n >= 10)
    {
        while (counterN != 0)
        {
            counterN = counterN / 10;               // while loop to test how many places number is
            counter++;
            currentSize++;
            if (currentSize == maxSize)
                Grow();
        }


        for (int i = 0; i < currentSize; i++)
        {
            int place = pow(10, counter - 1);                   // assigns each number to its own spot in array
            digitExtractor = newNumber / place;                       // ... works backwards
            newNumber = newNumber % place;
            bigNumber[currentSize - counter] = digitExtractor;
            --counter;
        }
    }

    if (n >= 0 && n <= 9)
    {
        currentSize++;
        bigNumber[currentSize - 1] = newNumber;                     // if only single digit, no need for for loop
        if (currentSize == maxSize)
            Grow();
    }

    if (n < 0)
    {
        currentSize++;                                      // if number is negative, return default
        bigNumber[currentSize - 1] = 0;
    }

}

// String Constructor
MyInt::MyInt(const char* s)
{
    currentSize = 0;
    maxSize = 5;
    bigNumber = new unsigned int [maxSize];
    unsigned int newNumber;
    char *string = new char[strlen(s)];

    strcpy(string, s);                                  // Copies new string to string variable

    for (int count = 0; count < strlen(string); count++)        // for loop to copy string into array
    {
        newNumber = C2I(string[count]);                     // Uses string converter to change string into digits

        if (newNumber == -1)
        {
            cout << "Error. Invalid String." << endl;       // error checking default object if string is not int
            currentSize = 1;
            bigNumber = new unsigned int [1];
            bigNumber[0] = 0;
            break;
        }
        else
        {
            bigNumber[currentSize] = newNumber;             //  each digit gets its own spot in array
            currentSize++;
            if (currentSize == maxSize)
                Grow();
        }

    }

}

// Deconstructor
MyInt::~MyInt()
{
    delete [] bigNumber;            // deletes array to free memory
}

// Copy Constructor
MyInt::MyInt(const MyInt &i)
{
    currentSize = i.currentSize;                // copies size of object

    bigNumber = new unsigned int[i.currentSize];            // assigns pointer to new array

    for (int count = 0; count < currentSize; count++)       // copies contents over to new array
        bigNumber[count] = i.bigNumber[count];

}

// Assignment Operator
MyInt &MyInt::operator= (const MyInt &i)
{
    if (this != &i)
    {
       delete [] bigNumber;                             // deletes number being assigned

       currentSize = i.currentSize;                     // assigns sizes to be the same

       bigNumber = new unsigned int[i.currentSize];     // points pointer to new array

       for (int count = 0; count < currentSize; count++)
           bigNumber[count] = i.bigNumber[count];       // copies contents over to new array
    }

    return *this;                                       // returns *this

}





