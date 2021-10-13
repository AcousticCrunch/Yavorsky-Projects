/* Name: Hunter Yavorsky
 * Course: COP3330 - Sec 0006
 * Project: Assignment #1 - Hourglass
 * Summary: A class (hourglass.h) that takes in a size of a equilateral hourglass.
 *          Also provides the user with functions to calculate area, perimeter
 *          and display the hourglass in ASCII formatting, as well as a summary function
 * This File: hourglass.h - Header File
 */


class Hourglass
{
public:
    // Constructor with defaults for border and fill
    Hourglass(int s, char b = '#', char f = '*');

    // Setter functions
    void SetBorder(char b);         // takes in a character
    void SetFill(char f);           // takes in a character

    // Grow/Shrink functions
    void Grow();
    void Shrink();

    // Constant/Getter functions
    int Perimeter() const;
    double Area() const;
    int GetSize() const;            // returns size of hourglass
    void Draw() const;              // returns ASCII drawing of hourglass
    void Summary() const;

private:
    // Private member variables
    int size;
    char border;
    char fill;
};

