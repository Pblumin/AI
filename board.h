#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <tuple>

class board{
    public:

    int array[8][8];
    char piece; 

    int ix; //initial x-coordinate of piece
    int iy; //initial y-coordinate of piece
    int fx; //final x-coordinate of piece
    int fy; //final y-coordinate of piece

    int ix_jumped = ix;
    int iy_jumped = iy;

    int color;

    board(); 
    //need to make a board that has squares that AI and player can identify

    board& operator=(const board&);

    void pieces();
    //make red and black pieces

    void startingpos(); 
    //sets up starting pos
    //filps board to face what ever color human player is


    //void turn(); 
    //Whos turn is it?
    //Who goes first

    void printBoard();
    //void reset();
    //reset the board

    void rlegalMoves(int ix, int iy);
    void wlegalMoves(int ix, int iy);

    void klegalMoves(int ix, int iy);

    int rgetLN(int ix, int iy);
    int rgetRN(int ix, int iy);
    int wgetLN(int ix, int iy);
    int wgetRN(int ix, int iy);
    int getNeighbors(int ix, int iy);
     
    void makeMove(int ix, int iy, int fx, int fy);

    std::list<int> xm;
    std::list<int> ym;

    std::list<std::tuple<int,int,int,int>> listOfMoves;

    void printMoves();

    void user();
    void displayMoves();
    void play();
    void switchColor();

    bool legal = false;

    int king(int a, int b, int i, int j);
    bool jump = false;
    //bool turn = false;

    bool gameOver();
    int jCount = 0;

    bool moveMade = false;

    bool isKing = false;

    bool botp1 = false; //is player 1 a bot
    bool botp2 = false; // is player 2 a bot

    int moveCount = 0;

    bool noMoves = false;

    void customPos(std::string inputFile);

    bool iscustom = false;

    bool doSwitch = false;

    void movesList();

    int rp;
};

#endif //_BOARD_H