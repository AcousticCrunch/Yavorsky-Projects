/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #4 - Playlist
* Summary: This collection of cpp and header files will
*          give the user the ability to add, take away, view,
*          and categorize songs in a menu-based playlist program.
* This File: song.cpp - Song.h Program File
*/
#include <iomanip>
#include <iostream>
#include <cstring>
#include "song.h"

// Cout Overload Function
ostream &operator<<(ostream &os, const Song &s)
{
    // formats columns to 20 spaces for title and artist
    os << left;
    os << setw(20) << s.GetTitle();
    os << setw(20) << s.GetArtist();

    // prints abbreviation based on enum status
    switch (s.GetCategory())
    {
        case POP:
            os << setw(10) << "Pop";
            break;
        case ROCK:
            os << setw(10) << "Rock";
            break;
        case ALTERNATIVE:
            os << setw(10) << "Alt";
            break;
        case COUNTRY:
            os << setw(10) << "Ctry";
            break;
        case HIPHOP:
            os << setw(10) << "HH";
            break;
        case PARODY:
            os << setw(10) << "Par";
            break;
    }

    // formats KB size in MB and prints
    int oldprecision = os.precision();
    double mb = s.size / 1000.0;
    os << setw(10) << fixed << setprecision(1) << mb;
    os << setprecision(oldprecision);
    os << endl;
    return os;
}

// Default Constructor
Song::Song()
{
    title[0] = '\0';
    artist[0] = '\0';
    category = POP;
    size = 0;
}

// Set Function
void Song::Set(const char *t, const char *a, Style st, int sz)
{
    // strcpy title and artist to char array
    strcpy(title, t);
    strcpy(artist, a);

    // sets enum variable and int variable
    category = st;
    size = sz;
}

// GetTitle Function
const char *Song::GetTitle() const
{
    // returns title of Song
    return title;
}

// GetArtist Function
const char *Song::GetArtist() const
{
    // returns artist of Song
    return artist;
}

// GetSize Function
int Song::GetSize() const
{
    // returns size of Song
    return size;
}

// GetCategory Function
Style Song::GetCategory() const
{
    // returns category of Song
    return category;
}

