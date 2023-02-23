/* Name: Hunter Yavorsky
* Course: COP3330 - Sec 0006
* Project: Assignment #4 - Playlist
* Summary: This collection of cpp and header files will
*          give the user the ability to add, take away, view,
*          and categorize songs in a menu-based playlist program.
* This File: playlist.h - Playlist Header File
*/

#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H
#include "song.h"

class Playlist
{
public:

    // Constructor and Deconstructor Functions
    Playlist();
    ~Playlist();

    // Basic Functionality Functions
    void AddSong(const char *t, const char *a, Style st, int sz);  // adds song to playlist

    void RemoveSong(const char *t);                                // removes song from playlist

    void FindSong(const char *t) const;                            // finds song in playlist

    void ShowSize() const;                                         // shows size of playlist in MB

    void ShowSizeCategory(Style st) const;                         // shows size of a particular category in playlist

    void ShowSizeKB() const;                                       // shows size of playlist in KB

    void PrintPlaylist() const;                                    // prints every song in playlist using cout overload

    void PrintCategory(Style st) const;                            // prints every song of a particular category
                                                                   // in the playlist


private:
    // Member Data
    int currentSize;
    Song *songList;
};

#endif //SONG_PLAYLIST_H
