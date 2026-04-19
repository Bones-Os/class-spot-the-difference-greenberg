/*
  File: proj1.cpp
  Project: CMSC 202 Project 1, Fall 2024
  Author: Andrew Greenberg
  Date: 9/12/24
  E-mail: andrew82@umbc.edu

  This file contains all the code for project 1, except the .txt files for the three different
  ASCII arts. This project/file is for a spot-the-difference game with ASCII art. There will
  be a menu with several different options the user can take (load file, display picture, play
  game, or quit). The game itself outlines the edge of the ASCII art with numbered labels for
  the column and row, for both the original and one-character-different artwork.
*/


// get required libraries and namespace
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

// declare and initialize constants for ASCII art's frame
const int NUM_ROWS = 10;
const int NUM_COLUMNS = 21;
char art[NUM_COLUMNS][NUM_ROWS]; // the 2-D array that stores the info for
                                 //ASCII art (what characters at which position
char  changedArt[NUM_COLUMNS][NUM_ROWS]; // the 2-D array that stores the copy of the                                                           //ASCII art with one change
int menuChoice; // user's input from the menu options
ifstream inputStream;
string artFile; // name of text file with ASCII art, to be imported/used


void loadFile (string file, char art[NUM_COLUMNS][NUM_ROWS]);
// Name: loadFile
// PreCondition: is given a string argument and a char 2-D array
// PostCondition: will open the given input file and put the char info into a
                //multidimensional array (the coordinates represented by the
                //char's/elements index values

void displayArt (char art[NUM_COLUMNS][NUM_ROWS]);
// Name: displayArt
// PreCondition: is given a 2-D array of char type
// PostCondition: loops through the given array and prints out the ASCII art given the array,
                //with a grid

void clearArray (char art[NUM_COLUMNS][NUM_ROWS]);
// Name: clearArray
// PreCondition: is given a 2-D array of chars
// PostCondition: will clear the array by replacing all elements with the default (a space, " ")

void guessChange (int changeColumn, int changeRow);
// Name: guessChange
// PreCondition: function is called by playGame() and is given, as ints, the correct location
               //of the changed character in the ASCII art, the column and then row
// PostCondition: will prompt the user for their guess on the location of the changed character,
                //the call to this function will end when the player is correct

void playGame (char art[NUM_COLUMNS][NUM_ROWS]);
// Name: playGame
// PreCondition: is given a 2-D array of strings. Should not contain all spaces
// PostCondition: makes a copy of the given array with one change, displays the contents of
                //both and calls guessChange (guessChange loops and only ends when
                //the player is correct)

int mainMenu ();
// Name: mainMenu
// PreCondition: when prompted for an option, the user replies with an int-type answer
// PostCondition: after asking the user for what they'd like to do, will return an int,
                //which represents the need to call loadFile, displayArt,
                //playGame, or exit

int main () {
  // seed the RNG
  srand(time(NULL));
  
  cout << "Welcome to the Spot The Difference Game" << endl;
  menuChoice = mainMenu();
  // carry out the actions of the game and menu while the user hasn't exited
  while (menuChoice != 4) {
    switch (menuChoice) {
    case 1:
      // before loading the art file, clear it, first (to avoid having wierd amalgamations of art)
      clearArray(art);

      // load the file, after getting the name of it from the user
      cout << "What is the name of the data file to import?" << endl;
      cin >> artFile;
      loadFile(artFile, art);
      break;
      
    case 2:
      displayArt(art);
      break;

    case 3:
       playGame(art);
       break;
    }
    // get user's input again
    menuChoice = mainMenu();
  }
  // thank the user for playing - this is the end of the program
  cout << "Thank you for playing the Spot The Difference Game" << endl;
  return 0;
}


int mainMenu (){
  int option = 0;    // user's reply to what menu option they'd like to choose

  // ask the user for what they'd like to do, until they answer with a valid choice
  do {
    // display menu and options
    cout << "What would you like to do?" << "\n"
	 << "1. Load ASCII Art from File\n"
	 << "2. Display Art\n"
	 << "3. Play Game\n"
	 << "4. Exit" << endl;

    // get user's input, which can only be 1, 2, 3 or 4
    cin >> option;
  } while (option < 1 or option > 4);

  return option;
}


void loadFile (string artFile, char art[NUM_COLUMNS][NUM_ROWS]) {
  int row; // the row the char belongs to
  int col; // the column the char belongs to
  char text; // the current text that should be added to the array
  ifstream tempInputStream (artFile); // local input stream

  
  if (tempInputStream.is_open()) {
    // copy the characters into the appropriate indexes
    while(tempInputStream >> row) {
      tempInputStream >> col >> text;
      art[col][row] = text; // indexes were col and row, changed for debugging
    }
    // confirm to the player that the file was loaded successfully
    cout << "Done" << endl;
  } else {
    cout << "File not found." << endl;
  }
  tempInputStream.close();
}


void displayArt (char art[NUM_COLUMNS][NUM_ROWS]) {
  bool artLoaded = false;
  // see if picture is loaded
  for (int i = 0; i < NUM_COLUMNS; i++) {
    for (int j = 0; j < NUM_ROWS; j++) {
      if (art[i][j] == '_') { // checks for underscores, as all the pictures have at least one in them
	artLoaded = true;
      }
    }
  }

  // only proceed if the picture is loaded, otherwise say it isn't
  if (artLoaded) {
    // display the column grid labels, after getting it set up
    cout << "    ";
    for (int i = 0; i < NUM_COLUMNS; i++) {
      if (i < 10) {
	cout << i << "  ";
      } else {
	cout << i << " ";
      }
    }
    cout << endl; // finish the top row, the grid labels

    // display the row number, then all the characters
    for (int row = 0; row < NUM_ROWS; row++) {
      cout << " " << row;
      for (int col = 0; col < NUM_COLUMNS; col++) {	
	cout << "  " << art[col][row];	
      }
      cout << endl;    
    }

  }else {
    cout << "No file loaded." << endl;
  }
}

void clearArray (char art[NUM_COLUMNS][NUM_ROWS]) {
  for (int c = 0; c < NUM_COLUMNS; c++) {
    for (int r = 0; r < NUM_ROWS; r++) {
      art[c][r] = 32; // make every value a space to essentially "clear" the picture
                      // value of a space gotten from: <https://runestone.academy/ns/books/published/thinkcpp/Chapter2/OperatorsforCharacters.html>
    }
  }
}

void playGame (char art[NUM_COLUMNS][NUM_ROWS]){
  char artCopy[NUM_COLUMNS][NUM_ROWS]; // the array that holds the copy of the actual art's data, but
                                       // will have one character (element) changed at random
  
  // initialize and declare variables for random new coordinates and value for the copy of the art
  int randCol = rand() % (NUM_COLUMNS);
  int randRow = rand() % (NUM_ROWS);
  char randChar = (rand() % (126 + 1 - 33) + 33);

  // check that the file is loaded
  bool artLoaded = false;
  // see if picture is loaded
  for (int i = 0; i < NUM_COLUMNS; i++) {
    for (int j = 0; j < NUM_ROWS; j++) {
      if (art[i][j] == '_') { // checks for underscores, as all the pictures have at least one in them
	artLoaded = true;
      }
    }
  }

  // only proceed if a file is loaded
  if (artLoaded) {
    // make artCopy a copy of art
    for (int c = 0; c < NUM_COLUMNS; c++) {
      for (int r = 0; r < NUM_ROWS; r++) {
	artCopy[c][r] = art[c][r];
      }
    }

    // pick a random row and column to change the value to a random character;
    artCopy[randCol][randRow] = randChar;

    // display original and copied artwork
    displayArt(art);
    cout << endl;
    displayArt(artCopy);

    // call guessChange and continue after they are correct
    guessChange(randCol, randRow);
    

  } else {
    cout << "No file loaded." << endl;
  }
}

void guessChange (int changeColumn, int changeRow) {
  int guessColumn; // player's guess as to which column contains the change
  int guessRow;    // player's guess as to which column row the change

  // prompt the user for their row, then column, guess
  // ^continue until they are correct
  do {
    cout << "What row is the change in?" << endl;
    cin >> guessRow;

    cout << "What column is the change in?" << endl;
    cin >> guessColumn;

    // check user's guess' accuracy
    if (guessRow != changeRow or guessColumn != changeColumn) {
      cout << "That is incorrect!" << endl;
    }
  } while (guessColumn != changeColumn or  guessRow != changeRow);

  // congratulate the user for being correct (as they have to be, if they escaped the above loop
  cout << "You are correct!" << endl;
}
  
