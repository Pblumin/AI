#include "board.h"
#include "ai.h"
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <time.h>

using namespace std;
using std::end;


int main(){

    board b;
    ai a;

    char custom;
    cout << "Would you like to use a custom position? (enter y for yes and n for no) \n";
    cin >> custom;

    if (custom == 'n'){
	    b.startingpos();
    } else {
        string inputFile;
        cout << "Enter name of input file: \n";
        cin >> inputFile;
        b.customPos(inputFile);
        b.iscustom = true;
    }

    b.user();
    bool error = false;
    while(!b.gameOver()){
        a.score(b, b.color);
        cout << "The score for player 1 is: " << a.RcurrentScore << endl;
        cout << "The score for player 2 is: " << a.WcurrentScore << endl;
        //cout << "The number of remaining pieces is " << b.rp << endl;
        b.displayMoves();
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if((i + j) % 2 == 0){
                    if( (b.array[i][j] == 1) || (b.array[i][j] == 2) || (b.array[i][j] == 3) || (b.array[i][j] == 4)) {
                        cout<<"OH NO\n";
                        error = true;
                        break;
                    }
                }
            }
        }
        if (error == true){
            break;
        }
        b.moveCount++;
        //b.play();
    }
 
    cout<<"Moves: "<<b.moveCount<<endl;
    return 0;
}