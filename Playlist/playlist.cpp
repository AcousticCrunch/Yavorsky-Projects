/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #4 - Playlist
* Summary: This collection of cpp and header files will
*          give the user the ability to add, take away, view,
*          and categorize songs in a menu-based playlist program.
* This File: playlist.cpp - Playlist.h Program File
*/

#include "playlist.h"
#include <iomanip>
#include <cstring>

// Constructor Function
Playlist::Playlist()
{
    // initializes the pointer as nullptr to prepare it to hold array
    songList = nullptr;
    currentSize = 0;
}

// Deconstructor Function
Playlist::~Playlist()
{
    // deallocates the dynamically allocated array
    delete [] songList;
}

// Add Song Function
void Playlist::AddSong(const char *t, const char *a, Style st, int sz)
{
    // increases new size
    currentSize++;
    cout << "Array currently has a size of " << currentSize << endl;

    // creates new Song object and a bigger temporary array to hold new song
    Song newSong;
    Song *newPlaylist = new Song[currentSize];

    // sets pointer to new song in a brand new array if this is the first song
    if (songList == nullptr)
    {
        songList = new Song[1];
        newSong.Set(t, a, st, sz);
        songList[0] = newSong;
        cout << "Song Added" << endl;
    }

    else
    {
        // increments through old array and copies songs to new array
        for(int count = 0; count < currentSize; count++)
            newPlaylist[count] = songList[count];

        // deletes old array
        delete [] songList;

        // assigns pointer to new array
        songList = newPlaylist;

        // adds new song to newer, bigger array
        newSong.Set(t, a, st, sz);
        songList[currentSize - 1] = newSong;
        cout << "Song Added" << endl;
    }
}

// Remove Song Function
void Playlist::RemoveSong(const char *t)
{
    // array to hold song title to search for
    char songSelection[35];

    // boolean to return whether the song was found
    bool rightSong;

    // spot in array where song was found
    int rightIndex;

    // copies user input to character array
    strcpy(songSelection, t);

    // loops through playlist to find song
    for (int count = 0; count < currentSize; count++)
    {
        if (strcmp(songList[count].GetTitle(), songSelection) == 0)
        {
            rightIndex = count;
            rightSong = true;
            break;
        }
        else
            rightSong = false;
    }

    // returns error if song is not found
    if (!rightSong)
        cout << "Song not Found" << endl;

    // removes song at correct index if song is found
    else
    {
        // shifts all songs in front of removed song down 1 spot
        for (int i = rightIndex + 1; i < currentSize; i++)
            songList[i - 1] = songList[i];

        cout << "Song Removed" << endl;

        // decreases size of playlist
        currentSize--;
        cout << "Array currently has a size of " << currentSize << endl;
    }


}

// Find Song Function
void Playlist::FindSong(const char *i) const
{
    // tracking variable for search matches and array to hold user input
    int songCounter = 0;
    char search[35];

    // copies search term to array
    strcpy(search, i);

    // loops through array to find search term, whether it be a title or artist
    for (int count = 0; count < currentSize; count++)
    {
        if (strcmp(songList[count].GetArtist(), search) == 0)
        {
            songCounter++;
            cout << "Song Found" << endl;
            cout << songList[count] << endl;
        }

        if (strcmp(songList[count].GetTitle(), search) == 0)
        {
            songCounter++;
            cout << songList[count];
        }
    }

    // if no search matches, return error
    if (songCounter == 0)
        cout << "Song(s) not Found" << endl;

}



// Print Playlist Function
void Playlist::PrintPlaylist() const
{
    // labels columns
    cout << left;
    cout << setw(20) << "Title";
    cout << setw(20) << "Artist";
    cout << setw(10) << "Style";
    cout << setw(10) << "Size(MB)";
    cout << endl;

    // prints entire playlist using overloaded cout function
    for (int count = 0; count < currentSize; count++)
        cout << songList[count];
}

// Print Category Function
void Playlist::PrintCategory(Style st) const
{
    // new variable type Style, represents user selection
    Style selection = st;

    // labels columns
    cout << left;
    cout << setw(20) << "Title";
    cout << setw(20) << "Artist";
    cout << setw(10) << "Style";
    cout << setw(10) << "Size(MB)";
    cout << endl;

    // prints songs in user selected category
    for (int count = 0; count < currentSize; count++)
    {
        if (songList[count].GetCategory() == selection)
            cout << songList[count];
    }

}

// ShowSize Function
void Playlist::ShowSize() const
{
    // sum variable to hold size
    double sizeSum = 0;

    // prints size of function using currentSize member data
    cout << "The playlist has " << currentSize << " songs in it." << endl;

    // loops through playlist and adds sizes together
    for (int count = 0; count < currentSize; count++)
        sizeSum += songList[count].GetSize();

    // prints size to 2 decimal places, formatted in MB
    int oldPrecision = cout.precision();
    double mb = sizeSum / 1000.00;
    cout << "The playlist has a size of " << fixed << setprecision(2) << mb << " MB" << endl;
    cout << setprecision(oldPrecision);
}

// ShowSizeCategory Function
void Playlist::ShowSizeCategory(Style st) const
{
    // variable type Style represents user input
    Style selection = st;

    // sum variable holds size
    double categorySum = 0.0;
    int categorySize = 0;

    // loops through playlist and only adds sizes of catergory
    for (int count = 0; count < currentSize; count++)
    {
        if (songList[count].GetCategory() == selection)
        {
            categorySum += songList[count].GetSize();
            categorySize++;
        }

    }

    // prints size to 2 decimal places, formatted in MB
    int oldPrecision = cout.precision();
    double mb = categorySum / 1000.00;

    cout << "There are " << categorySize << " songs in the chosen category" << endl;
    cout << "The category has a size of " << fixed << setprecision(2) << mb << " MB" << endl;
    cout << setprecision(oldPrecision);

}


// ShowSizeKB Function
void Playlist::ShowSizeKB() const
{
    // sum variable to hold size in KB
    double sizeSum;

    // loops through array and adds sizes that are already in KB
    for (int count = 0; count < currentSize; count++)
        sizeSum += songList[count].GetSize();

    // prints size in KB
    int oldPrecision = cout.precision();
    cout << "This playlist is " << fixed << setprecision(2) << sizeSum << " KB" << endl;
    cout << setprecision(oldPrecision);
}





