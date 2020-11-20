/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include <string>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Constants */

const int MIN_WORD_SIZE = 4;
const int NUM_TILE_DIRECTIONS = 8;
const int STANDARD_BOARD_SIZE = 4;
const int BIG_BOARD_SIZE = 5;
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const double PAUSE_TIME = 1000;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
string verifyUserInput(string input);
void giveInstructions();
Grid<char> setupGame();
int getBoggleBoardSize();
string getShuffledBoard(int dimension);
void swapCubes(Vector<string>& cubes, int i, int j);
bool isCustomConfiguration();
void configureBoggleBoard(Grid<char>& board, string config);
string getCustomConfiguration(int dimension);
void drawBoggleBoard(Grid<char>& board);
void getAdjacentTile(int direction, int row, int col, int& adjRow, int& adjCol);
bool recFindWordOnBoard(string partial, string word, int row, int col, Grid<char>& board, Grid<bool>& usedTiles);
bool findWordOnBoard(string word, Grid<char>& board);
void recFindRemaningWordsOnBoard(string partial, int row, int col, Grid<char>& board, Grid<bool>& usedTiles, Lexicon& dictionary, Lexicon& usedWords);
void findRemaningWordsOnBoard(Grid<char>& board, Lexicon& dictionary, Lexicon& usedWords);
void humansTurn(Grid<char>& board, Lexicon& dictionary, Lexicon& guessedWords);
void computersTurn(Grid<char>& board, Lexicon& dictionary, Lexicon& guessedWords);
bool continueGame();

/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    Lexicon dictionary("EnglishWords.dat");
    
    while (true) {
        Lexicon guessedWords;
        
        welcome();
        giveInstructions();
        Grid<char> board = setupGame();
        
        humansTurn(board, dictionary, guessedWords);
        computersTurn(board, dictionary, guessedWords);
        
        if (!continueGame()) break;
    }
    
    return 0;
}

/*
 * Function: setupGame
 * Usage: setupGame();
 * -----------------
 * Cube setup, board drawing and cube shaking. Return the configured
 * board.
 */

Grid<char> setupGame() {
    int dimension = getBoggleBoardSize();
    Grid<char> board(dimension, dimension);
    bool custom = isCustomConfiguration();
    string config;
    
    if (custom) {
        config = getCustomConfiguration(dimension);
        configureBoggleBoard(board, config);
    } else {
        config = getShuffledBoard(dimension);
        configureBoggleBoard(board, config);
    }
    
    drawBoggleBoard(board);
    return board;
}


/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: verifyUserInput
 * Usage: verifyUserInput(input);
 * -----------------
 * Reprompt user for input until he enters y or n.
 */

string verifyUserInput(string choice) {
    choice = toLowerCase(choice);
    
    while (choice != "y" && choice != "n") {
        cout << "Please enter either y or n: ";
        choice = getLine();
    }
    
    return choice;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << "Do you need instructions? ";
    string answer = verifyUserInput(getLine());
    cout << endl;
    
    if (answer == "y") {
        cout << endl;
        cout << "The boggle board is a grid onto which I ";
        cout << "I will randomly distribute cubes. These ";
        cout << "6-sided cubes have letters rather than ";
        cout << "numbers on the faces, creating a grid of ";
        cout << "letters on which you try to form words. ";
        cout << "You go first, entering all the words you can ";
        cout << "find that are formed by tracing adjoining ";
        cout << "letters. Two letters adjoin if they are next ";
        cout << "to each other horizontally, vertically, or ";
        cout << "diagonally. A letter can only be used once ";
        cout << "in each word. Words must be at least four ";
        cout << "letters long and can be counted only once. ";
        cout << "You score points based on word length: a ";
        cout << "4-letter word is worth 1 point, 5-letters ";
        cout << "earn 2 points, and so on. After your puny ";
        cout << "brain is exhausted, I, the supercomputer, ";
        cout << "will find all the remaining words and double ";
        cout << "or triple your paltry score." << endl << endl;
        cout << "Hit return when you're ready..." << endl;
        getLine();
    }
}

/*
 * Function: getBoggleBoardSize
 * Usage: getBoggleBoardSize();
 * -----------------
 * Return the size of the boggle board to be used.
 */

int getBoggleBoardSize() {
    cout << "You can choose Standard Boggle (4x4 grid)" << endl;
    cout << "or Big Boggle (5x5 grid)." << endl;
    
    string answer = verifyUserInput(getLine("Would you like Big Boggle? "));
    cout << endl;
    
    if (answer == "y") {
        return BIG_BOARD_SIZE;
    } else {
        return STANDARD_BOARD_SIZE;
    }
}

/*
 * Function: getShuffledBoard
 * Usage: getShuffledBoard(dimension);
 * -----------------
 * Return string configuration for shuffled board.
 */

string getShuffledBoard(int dimension) {
    int length;
    Vector<string> cubes;
    
    if (dimension == STANDARD_BOARD_SIZE) {
        length = STANDARD_BOARD_SIZE * STANDARD_BOARD_SIZE;
        
        for (int i = 0; i < length; i++) {
            cubes.add(STANDARD_CUBES[i]);
        }
    } else {
        length = BIG_BOARD_SIZE * BIG_BOARD_SIZE;
        
        for (int i = 0; i < length; i++) {
            cubes.add(BIG_BOGGLE_CUBES[i]);
        }
    }
    
    // Shuffle the cubes in the vector
    string shuffledBoard;
    int n = cubes.size();
    
    for (int i = 0; i < n; i++) {
        int r = randomInteger(i, n - 1);
        swapCubes(cubes, i, r);
    }
    
    for (int i = 0; i < n; i++) {
        string c = cubes.get(i);
        int r = randomInteger(0, c.length() - 1);
        shuffledBoard += c[r];
    }
    
    return shuffledBoard;
}

/*
 * Function: swapCubes
 * Usage: swapCubes(cubes);
 * -----------------
 * Swap the values at given positions in vector.
 */

void swapCubes(Vector<string>& cubes, int i, int j) {
    string temp = cubes.get(i);
    cubes.set(i, cubes.get(j));
    cubes.set(j, temp);
}

/*
 * Function: isCustomCofiguration
 * Usage: isCustomConfiguration();
 * -----------------
 * Return true if the user choose to use a custom configuration.
 */

bool isCustomConfiguration() {
    cout << "You can either choose to specify a custom configuration or the board can be randomly generated." << endl;
    string answer = verifyUserInput(getLine("Do you want to force the board configuration? "));
    cout << endl;
    
    if (answer == "y") {
        return true;
    } else {
        return false;
    }
}

/*
 * Function: configureBoggleBoard
 * Usage: configureBoggleBoard(board, config);
 * -----------------
 * Configures the boggle board according to given config.
 */

void configureBoggleBoard(Grid<char>& board, string config) {
    int size = board.numRows();
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board.set(i, j, config[i * size + j]);
        }
    }
}

/*
 * Function: getCustomConfiguration
 * Usage: getCustomConfiguration(dimension);
 * -----------------
 * Gets the custom board configuration from user.
 */

string getCustomConfiguration(int dimension) {
    int expectedLength = dimension * dimension;
    cout << "Enter a " << expectedLength << "-character string to identify which letters you want on the cubes." << endl;
    cout << "The first " << dimension << " letters are the cubes on the top row from left to right, the next " << dimension << " letters are the second row, and so on." << endl;
    
    string custom;
    while (true) {
        custom = getLine("Enter the string: ");
        if (custom.length() == expectedLength) break;
        cout << "String must have " << expectedLength << " characters." << endl;
    }
    
    custom = toUpperCase(custom);
    
    return custom;
}

/*
 * Function: drawBoggleBoard
 * Usage: drawBoggleBoard(boggleBoard);
 * -----------------
 * Draw the graphic representation of the boggle board.
 */

void drawBoggleBoard(Grid<char>& board) {
    int size = board.numRows();
    drawBoard(size, size);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            labelCube(i, j, board.get(i, j));
        }
    }
}

/*
 * Function: getAdjacentTile
 * Usage: adjacentTile(direction, row, col, adjRow, adjCol);
 * -----------------
 * direction is specified with integer 0-7.
 * 0 specifies northwest, 7 specifies west, in clockwise direction.
 * Updates adjRow and adjCol according to given direction.
 */

void getAdjacentTile(int direction, int row, int col, int& adjRow, int& adjCol) {
    switch (direction) {
        // North West
        case 0:
            adjRow = row - 1;
            adjCol = col - 1;
            break;
            
        // North
        case 1:
            adjRow = row - 1;
            adjCol = col;
            break;
            
        // North East
        case 2:
            adjRow = row - 1;
            adjCol = col + 1;
            break;
        
        // East
        case 3:
            adjRow = row;
            adjCol = col + 1;
            break;
        
        // South East
        case 4:
            adjRow = row + 1;
            adjCol = col + 1;
            break;
            
        // South
        case 5:
            adjRow = row + 1;
            adjCol = col;
            break;
            
        // South West
        case 6:
            adjRow = row + 1;
            adjCol = col - 1;
            break;
            
        // West
        case 7:
            adjRow = row;
            adjCol = col - 1;
            break;
            
        default:
            break;
    }
}

/*
 * Function: unhighlightBoard
 * Usage: unhighlightBoard(board);
 * -----------------
 * Remove highlighting from board.
 */

void unhighlightBoard(Grid<char>& board) {
    pause(PAUSE_TIME);
    
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            highlightCube(i, j, false);
        }
    }
}

/*
 * Function: recFindWordOnBoard
 * Usage: recFindWordOnBoard(partial, word, row, col, board, usedTiles);
 * -----------------
 * Recursive function to check if word is on board.
 */

bool recFindWordOnBoard(string partial, string word, int row, int col, Grid<char>& board, Grid<bool>& usedTiles) {
    // Base Case 0 (if row or col are out of board):
    if (!board.inBounds(row, col)) return false;
    
    // Base Case 1 (if tile was already used previously):
    if (usedTiles.get(row, col)) return false;
    
    // Go along this path to explore words
    partial += board.get(row, col);
    
    // Check if word is along the path we are exploring
    if (word.substr(0, partial.length()) != partial) {
        return false;
    }
    
    // Continue exploring
    usedTiles.set(row, col, true);
    
    // Check if word is formed
    if (partial == word) {
        highlightCube(row, col, true);
        return true;
    }
    
    // Explore all 8 directions from current tile
    int adjRow;
    int adjCol;
    
    for (int i = 0; i < NUM_TILE_DIRECTIONS; i++) {
        getAdjacentTile(i, row, col, adjRow, adjCol);
        
        if (recFindWordOnBoard(partial, word, adjRow, adjCol, board, usedTiles)) {
            highlightCube(row, col, true);
            return true;
        }
        
        // Backtrack step: Mark tile as unused if its not found
        usedTiles.set(row, col, false);
    }
    
    return false;
}

/*
 * Function: findWordOnBoard
 * Usage: findWordOnBoard(word, board);
 * -----------------
 * Return true if word is on board and highlight tiles.
 */

bool findWordOnBoard(string word, Grid<char>& board) {
    Grid<bool> usedTiles(board.numRows(), board.numCols());
    
    // check if word can formed starting from every tile in the board
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            if (recFindWordOnBoard("", word, i, j, board, usedTiles)) {
                return true;
            }
        }
    }
    
    return false;
}

/*
 * Function: recFindRemaningWordsOnBoard
 * Usage: recFindRemainingWordsOnBoard(partial, row, col, board, usedTiles, dictionary, usedWords);
 * -----------------
 * Recursive function to find remaining words.
 */

void recFindRemaningWordsOnBoard(string partial, int row, int col, Grid<char>& board, Grid<bool>& usedTiles, Lexicon& dictionary, Lexicon& usedWords) {
    // Base Case 0 (if row or col are out of board):
    if (!board.inBounds(row, col)) return;
    
    // Base Case 1 (if tile was already used previously):
    if (usedTiles.get(row, col)) return;
    
    // Go along this path to explore words
    partial += board.get(row, col);
    
    // If the dictionary does not contain partial prefix
    if (!dictionary.containsPrefix(partial)) {
        return;
    }
    
    // Continue exploring
    usedTiles.set(row, col, true);
    
    if (dictionary.contains(partial) && !usedWords.contains(partial) && partial.length() >= MIN_WORD_SIZE) {
        usedWords.add(partial);
        recordWordForPlayer(partial, COMPUTER);
    }
    
    // Explore all 8 directions from current tile
    int adjRow;
    int adjCol;
    
    for (int i = 0; i < NUM_TILE_DIRECTIONS; i++) {
        getAdjacentTile(i, row, col, adjRow, adjCol);
        recFindRemaningWordsOnBoard(partial, adjRow, adjCol, board, usedTiles, dictionary, usedWords);
    }
    
    // Backtrack step
    partial.erase(partial.length() - 1);
    usedTiles.set(row, col, false);
}

/*
 * Function: findRemaningWordsOnBoard
 * Usage: findRemainingWordsOnBoard(board, dictionary, usedWords);
 * -----------------
 * Find the remaning words on board.
 */

void findRemaningWordsOnBoard(Grid<char>& board, Lexicon& dictionary, Lexicon& usedWords) {
    Grid<bool> usedTiles(board.numRows(), board.numCols());
    
    // find words starting from every tile on board
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            recFindRemaningWordsOnBoard("", i, j, board, usedTiles, dictionary, usedWords);
        }
    }
}

/*
 * Function: humansTurn
 * Usage: humansTurn(dictionary, guessedWords);
 * -----------------
 * Run routine for getting humans guesses.
 */

void humansTurn(Grid<char>& board, Lexicon& dictionary, Lexicon& guessedWords) {
    cout << "Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line." << endl;
    
    while (true) {
        string wordInput = getLine("Enter a word: ");
        wordInput = toUpperCase(wordInput);
        
        if (wordInput.empty()) break;
        
        if (wordInput.length() < MIN_WORD_SIZE) {
            cout << "Please enter a word that is at least " << MIN_WORD_SIZE << " characters in length." << endl;
        } else if (!dictionary.contains(wordInput)) {
            cout << "That is not a valid word in the computer's English dictionary." << endl;
        } else if (guessedWords.contains(wordInput)) {
            cout << "You have already guessed that." << endl;
        } else if (!findWordOnBoard(wordInput, board)) {
            cout << "You can't make that word." << endl;
        } else {
            guessedWords.add(wordInput);
            recordWordForPlayer(wordInput, HUMAN);
            unhighlightBoard(board);
        }
    }
}

/*
 * Function: computersTurn
 * Usage: computersTurn(board, dictionary, guessedWords);
 * -----------------
 * Run routine for finding remaining words.
 */

void computersTurn(Grid<char>& board, Lexicon& dictionary, Lexicon& guessedWords) {
    findRemaningWordsOnBoard(board, dictionary, guessedWords);
}

/*
 * Function: continueGame
 * Usage: continueGame();
 * -----------------
 * Return true if user wishes to continue game.
 */

bool continueGame() {
    cout << "Would you like to play again? ";
    string answer = verifyUserInput(getLine());
    
    if (answer == "y") {
        return true;
    } else {
        return false;
    }
}