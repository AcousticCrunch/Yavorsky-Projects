/* Name: Hunter Yavorsky Date: 11/8/20 Section: COP 3363 - SEC 0014

Assignment: Module 9

Due Date: 11/8/20

About this project: I will create a menu based program that displays bowling scores, changes scores, displays
                    game with the highest score, displays average game score, and displays a sorted list of
                    scores.

Assumptions: Assumes the user inputs the correct type of value requested.

All work below was performed by Hunter Yavorsky */

#include <iostream>

using namespace std;


// declare function prototypes

int getValidScore();
int getValidGame(int);
int * AddGame(const int *,int &NUM_GAMES);
void displayScores(const int *, int);
void ChangeAScore(int *, int);
void displayGameHighestScore(const int *, int);
void displayAverageScore(const int *, int);

//********************
// main menu function
//********************

int main()
{
    // declare select variable and initial bowling scores and constant

    int NUM_GAMES = 3;
    int s[] = {178,98,288};
    int * scores = s;
    int select;

    cout <<  "Welcome to the help with the bowling tournament program!\n";

    // verify program is intended to run
    do
    {
        // prompt user for input

        cout<<"1) Display the scores\n"
              "2) Change a score\n"
              "3) Display game with the highest score\n"
              "4) Display average game score\n"
              "5) Add a score\n"
              "6) Quit\n"
              "Select an option (1..6)..";
        cin >> select;

        if (select == 1)
            displayScores(scores, NUM_GAMES);

        if (select == 2)
            ChangeAScore(scores, NUM_GAMES);

        if (select == 3)
            displayGameHighestScore(scores, NUM_GAMES);

        if (select == 4)
            displayAverageScore(scores, NUM_GAMES);

        if (select == 5)
            scores = AddGame(scores, NUM_GAMES);

        // verify input

        while (select < 1 || select > 6)
        {
            cout << "Select an option (1..6) ";
            cin >> select;
        }
    }
    while (select != 6);

}

//**********************************
// display scores function (input 1)
//**********************************

void displayScores(const int *scores, int NUM_GAMES)
{
    cout << "Display Scores" << endl;

    for (int title = 1; title <= NUM_GAMES; title++)
        cout << "     " << "Game " << title;

    cout << endl;

    for (int count = 0; count < NUM_GAMES; count++)
        cout << "       " << scores[count] << "  " ;

    cout << endl;
}

//*********************************
// change score function (input 2)
//*********************************

void ChangeAScore(int *scores, int NUM_GAMES)
{
    int gameSelect;
    cout << "Change a Score" << endl;

    // calls input validation functions

    gameSelect = getValidGame(NUM_GAMES) - 1;
    scores[gameSelect] = getValidScore();
}

//****************************************
// display highest game function (input 3)
//****************************************

void displayGameHighestScore(const int *scores, int NUM_GAMES)
{
    int highestGame = 0;
    int highestScore = scores[0];

    for (int index = 0; index < NUM_GAMES; index++)
    {
        if (scores[index] > highestScore)
        {
            highestScore = scores[index];
            highestGame = index;
        }
    }
    cout << "The game with the highest score is " << highestGame + 1 << endl;
}

//********************************
// display average score function (input 4)
//********************************

void displayAverageScore(const int *scores, int NUM_GAMES)
{
    double sum;
    double average;

    // add each score value to sum
    for (int index = 0; index < NUM_GAMES; index++)
        sum += scores[index];

    // divide sum by number of games
    average = sum / NUM_GAMES;

    cout << "Average score is \n" << average << endl;
}

//********************************
// add a new game score (input 5)
//********************************

int *AddGame(const int *scores, int &NUM_GAMES)
{
    // declare new pointer variable and add one more game
    NUM_GAMES += 1;
    int *newScores = new int [NUM_GAMES];

    //copy previous scores to new array
    for (int count = 0; count < NUM_GAMES; count++)
        newScores[count] = scores[count];

    // prompt user for new score for new game
    newScores[NUM_GAMES - 1] = getValidScore();

    // return new array
    return newScores;
}


//******************************************************
// validate game number input for change score function
//******************************************************

int getValidGame(int NUM_GAMES)
{
    int gameNumber;
    cout << "Please enter in the game number ..." << endl;
    cin >> gameNumber;

    while (gameNumber < 1 || gameNumber > NUM_GAMES)
    {
        cout << "Please enter in the game number ..." << endl;
        cin >> gameNumber;
    }
    return gameNumber;
}

//*****************************************************
// validate game score input for change score function
//*****************************************************

int getValidScore()
{
    int gameScore;
    cout << "Please enter in the bowling score..." << endl;
    cin >> gameScore;

    while (gameScore < 0 || gameScore > 300)
    {
        cout << "Please enter in the bowling score..." << endl;
        cin >> gameScore;
    }
    return gameScore;
}




