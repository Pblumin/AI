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
//using std::end;

clock_t start, point; 

ai::ai(){

}

void ai::score(board b, int color){
    //things to consider for score
    //1: count number of regular pieces and kings DONE
    //2: see how far away a piece is from promotion 
    //3: if player ahead try to trade pieces, if player behind try not to trade pieces
    //4: endgame senerio if less than 6 pieces
        //on the winning side try to do the following
            //look to see if there is a enemy piece near or in a corner (will consider 3 squares)
            //if there is favor moves that go to that corner
        //on the losing side try to do the following
            //figure out the closest corner from each piece and try to get there
            //probably will pick topleft and bottom left corners to consider

    //color = b.color;
    float currentScore = 0;
    int redCount = 0;
    int wCount = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            //value for red piece (1)
            if( b.array[i][j] == 1){
                currentScore = currentScore + 3;
                redCount++;
                //distance till promotion
                currentScore = currentScore + (0.5 * i);

                if(b.rp <= 8){
                    currentScore = currentScore + (0.7 * i);
                }
            }
            //value for white piece (2)
            else if( b.array[i][j] == 2){
                currentScore = currentScore - 3;
                wCount++;
                //distance till promotion
                currentScore = currentScore - (0.5 * (7-i));

                if(b.rp <= 8){
                    currentScore = currentScore - (0.7 * (7-i));
                }

            }
            //value for red king (3)
            else if( b.array[i][j] == 3){
                currentScore = currentScore + 7;
                redCount++;
                //endgame   //ADD GOING TO THE OTHER CORNERS 6 CHECK IF PIECES ARE IN ONE OF THE 6 SQUARES THERES
                //cout << b.rp << endl;

                currentScore = currentScore - 0.05*(abs(4-j) + abs(4-i));

                if(b.rp <= 8){
                    currentScore = currentScore + 5;
                }

                // if(b.rp <= 8){
                //     //cout<<"hi1\n";
                //     currentScore = currentScore + 15;
                //     if( (currentScore > 0) ){
                //         if( (b.array[0][7] == 4) || (b.array[1][6] == 4) ){
                //             currentScore = currentScore + 0.1*( (7-i) + j );
                //         } else if( (b.array[7][0] == 4) || (b.array[7][0] == 2) || (b.array[6][1] == 2) || (b.array[6][1] == 4) ){
                //             currentScore = currentScore + 0.1*( i + (7-j) );
                //         } else if ( (b.array[0][1] == 4) || (b.array[0][3] == 4) || (b.array[1][0] == 4) || (b.array[1][2] == 4) || (b.array[2][1] == 4) || (b.array[3][0] == 4) ){
                //             currentScore = currentScore + 0.1*( (7-j) + (7-i) );
                //         } else if ( (b.array[7][6] == 4) || (b.array[7][4] == 4) || (b.array[6][7] == 4) || (b.array[6][5] == 4) || (b.array[5][6] == 4) || (b.array[4][7] == 4) ){
                //             currentScore = currentScore + 0.1*( (j) + (i) );
                //         } else {
                //             //currentScore = currentScore - (abs(4-j) + abs(4-i));
                //         } 
                //     } else {
                //         if( (b.array[0][7] == 0) || (b.array[0][7] == 3) ){
                //             currentScore = currentScore + 0.1*( (7-i) + j );
                //         } else if( (b.array[7][0] == 0) || (b.array[7][0] == 3) ){
                //             //currentScore = currentScore + 0.1*( i + (7-j) );
                //         } else {
                //             //currentScore = currentScore - 0.5(abs(4-j) + abs(4-i));
                //         }
                //     }
                // }

            }
            //value for white king (4)
            else if( b.array[i][j] == 4){
                currentScore = currentScore - 7;
                wCount++;
                //endgame //ADD GOING TO THE OTHER CORNERS 6 CHECK IF PIECES ARE IN ONE OF THE 6 SQUARES THERES
                //cout << b.rp << endl;

                currentScore = currentScore + 0.05*(abs(4-j) + abs(4-i));

                if(b.rp <= 8){
                    currentScore = currentScore - 5;
                }

                // if(b.rp <= 8){
                //     //cout<<"hi2\n";
                //     currentScore = currentScore - 15;
                //     if( (currentScore < 0) ){
                //         if( (b.array[0][7] == 3) || (b.array[1][6] == 1) || (b.array[1][6] == 3) ){
                //             currentScore = currentScore - 0.1*( (7-i) + j );
                //         } else if( (b.array[7][0] == 3) || (b.array[7][0] == 1) || (b.array[6][1] == 1) || (b.array[6][1] == 3) ){
                //             currentScore = currentScore - 0.1*( i + (7-j) );
                //         } else if ( (b.array[0][1] == 3) || (b.array[0][3] == 3) || (b.array[1][0] == 3) || (b.array[1][2] == 3) || (b.array[2][1] == 3) || (b.array[3][0] == 3) ){
                //             currentScore = currentScore + 0.1*( (7-j) + (7-i) );
                //         } else if ( (b.array[7][6] == 3) || (b.array[7][4] == 3) || (b.array[6][7] == 3) || (b.array[6][5] == 3) || (b.array[5][6] == 3) || (b.array[4][7] == 3) ){
                //             currentScore = currentScore + 0.1*( (j) + (i) );
                //         } else {
                //             //currentScore = currentScore + (abs(4-j) + abs(4-i));
                //         }   
                //     } else {
                //         if( (b.array[0][7] == 0) || (b.array[0][7] == 4) ){
                //             currentScore = currentScore - 0.1*( (7-i) + j );
                //         } else if( (b.array[7][0] == 0) || (b.array[7][0] == 4) ){
                //             currentScore = currentScore - 0.1*( i + (7-j) );
                //         } else {
                //             //currentScore = currentScore + 0.5(abs(4-j) + abs(4-i));
                //         }
                //     }
                // }

            }
            //for now nothing
            else {
                currentScore = currentScore;
            }
        }
    }

    if(b.gameOver() && b.color == 1){
        currentScore = 10000;
    } else if (b.gameOver() && b.color == 0){
        currentScore = -10000;
    }

    RcurrentScore = currentScore;
    WcurrentScore = -currentScore;
    //cout<< currentScore;
    //cout << "The score for player 1 is: " << RcurrentScore << endl;
    //cout << "The score for player 2 is: " << WcurrentScore << endl;
    //cout << "board in score function: \n";
    //b.printBoard();
    // cout << "number of reds: " << redCount << endl;
    // cout << "number of whites: " << wCount << endl;
}

void ai::result(board &b, int moveNum){
    b.movesList();
    //int result;
    if( (b.listOfMoves.empty() == true) && (b.jump == false) && (b.moveMade == false) ) {
        //cout<<"I am Here\n";
        b.noMoves = true;
    } else {
        if( (b.listOfMoves.empty()) && (b.jump == true)){
                b.switchColor();
                b.jump = false;
                b.moveMade = false;
        } else {

            if ( b.color == 1 ){
                auto it = b.listOfMoves.cbegin();
                std::advance(it, moveNum);
                // std::cout<<"before: \n";
                // b.printBoard();
                b.makeMove( std::get<0>(*it) , std::get<1>(*it) , std::get<2>(*it) , std::get<3>(*it) );
                //cout << "Move Made: " << std::get<0>(*it) << "," << std::get<1>(*it) << "-->"<< std::get<2>(*it) << ","<<std::get<3>(*it) <<endl;
                if(b.doSwitch == true){
                    b.switchColor();
                }
                //b.listOfMoves.clear();
            } else if ( b.color == 0 ){
                auto it = b.listOfMoves.cbegin();
                std::advance(it, moveNum);
                // std::cout<<"before: \n";
                // b.printBoard();
                b.makeMove( std::get<0>(*it) , std::get<1>(*it) , std::get<2>(*it) , std::get<3>(*it) );
                if(b.doSwitch == true){
                    b.switchColor();
                }
                //cout << "Move Made: " << std::get<0>(*it) << "," << std::get<1>(*it) << "-->"<< std::get<2>(*it) << ","<<std::get<3>(*it) <<endl;
                //b.listOfMoves.clear();
            }
        }
    }
    // std::cout<<"after: \n";
    // b.printBoard();
}

std::tuple<int,std::__cxx11::list<int>> ai::maxValue(board b, list<int> currentMove, int alpha, int beta, int depth){
    std::tuple<int,std::__cxx11::list<int>> vMove;
    std::tuple<int,std::__cxx11::list<int>> bestVMoves;
          
    point = clock() / CLOCKS_PER_SEC;
    if( (point-start) > 4.9){
        vMove = std::make_tuple(specialScore, currentMove);
        return vMove;
    }
    
    //cout<<"INSIDE MAXVALUE FUNCTION"<<endl;
    //if game is terminal return score and NULL
    if( depth == maxDepth ){
        score(b, b.color);
        if (b.color == 1){
            vMove = std::make_tuple(RcurrentScore, currentMove);
        } else {
            vMove = std::make_tuple(WcurrentScore, currentMove);
        }
        return vMove; 
    }
    //cout<<"hi1\n";
    // set v to negative infinity
    int v = -999999;
    //get the list of moves given the current board
    //b.movesList();
    //cout<<"hi2\n";
    //get the number of options
    int listLength = b.listOfMoves.size();
    list<int> tempMoves; 
    for(int a = 0; a < listLength; a++){
        //cout<<"hi3\n";
        //new board
        board newb = b;
        tempMoves = currentMove;
        
        if ( (newb.jump == false) && (newb.moveMade == false) ) {
            result(newb, a);
        } else {
            while ( ((newb.jump == true) || (newb.moveMade == true)) ){
                //cout<<"jump is " << b.jump << endl;
                //cout<<"moveMade is " << b.moveMade  << endl;
                result(newb, a);
            }
            //cout<<b.rp<<endl;
            result(newb, a);
            //result(newb, a);
            // result(newb, a);
            // result(newb, a);
            // result(newb, a);
            //result(newb, a);
        }
        // } else {
        //     result(newb, a);
        //     result(newb, a);
        // }
        //result(newb, a);

        //v2,a2 <- minValue
        tempMoves.push_back(a);
        // for (auto i : tempMoves){
        //     cout<<"searching move: "<<i<<endl;
        // }
        //newb.printBoard();
        vMove = minValue(newb, tempMoves, alpha, beta, depth+1); 
        int v2 = std::get<0>(vMove);

        if (v2 == specialScore){
            return vMove;
        }
        
        if (v2 > v){
            v = v2;
            bestVMoves = vMove;
            alpha = max(alpha, v);
        }

        // cout<<"maxMoves: \n";
        // for (auto i : get<1>(bestVMoves) ){
        //     cout<<i<<endl;
        // }
        //cout << "Red Score: " << RcurrentScore<<endl;
        // cout << "Max score: " << v <<endl;
        //newb.printBoard();

        if(v >= beta){
            //make tuple that has v+1 (cause max for min will be v-1) and is the move in the bestMove)
            vMove = std::make_tuple(v+1, get<1>(bestVMoves));
            return vMove; 
        }
    }
    return bestVMoves; 
}

std::tuple<int,std::__cxx11::list<int>> ai::minValue(board b, list<int> currentMove, int alpha, int beta, int depth){
    std::tuple<int,std::__cxx11::list<int>> vMove;
    std::tuple<int,std::__cxx11::list<int>> bestVMoves;
    
    point = clock() / CLOCKS_PER_SEC;
    if( (point-start) > 4.9){
        vMove = std::make_tuple(specialScore, currentMove);
        return vMove;
    }

    //if game is terminal return score and NULL
    if( depth == maxDepth ){
        score(b, b.color);
        if (b.color == 1){
            vMove = std::make_tuple(RcurrentScore, currentMove);
        } else {
            vMove = std::make_tuple(WcurrentScore, currentMove);
        }
        return vMove; 
    }

    // set v to negative infinity
    int v = 999999;
    //get the list of moves given the current board
    //b.movesList();
    //get the number of options
    int listLength = b.listOfMoves.size(); 
    list<int> tempMoves;
    for(int a = 0; a < listLength; a++){
        //new board
        board newb = b;
        tempMoves = currentMove;
        // std::cout<<"before: \n";
        // b.printBoard();
        
        if ( (newb.jump == false) && (newb.moveMade == false) ) {
            result(newb, a);
        } else {
            while ( ((newb.jump == true) || (newb.moveMade == true)) ){
                //cout<<"jump is " << b.jump << endl;
                //cout<<"moveMade is " << b.moveMade  << endl;
                result(newb, a);
            }
            result(newb, a);
            //result(newb, a);
            // result(newb, a);
            // result(newb, a);
            //result(newb, a);
            //result(newb, a);
        }
        //result(newb, a);

        // std::cout<<"after: \n";
        // b.printBoard();
        //v2,a2 <- minValue
        tempMoves.push_back(a);
        // for (auto i : tempMoves){
        //     cout<<"searching move: "<<i<<endl;
        // }
        //newb.printBoard();
        vMove = maxValue(newb, tempMoves, alpha, beta, depth+1); 
        int v2 = std::get<0>(vMove);

        if (v2 == specialScore){
            return vMove;
        }

        if (v2 < v){
            v = v2;
            bestVMoves = vMove;
            beta = min(beta, v);
        }

        // cout<<"minMoves: \n";
        // for (auto i : get<1>(bestVMoves) ){
        //     cout<<i<<endl;
        // }
        // cout << "Min score: " << v<<endl;
        //cout << "White Score: " << WcurrentScore<<endl;
        //newb.printBoard();
        if(v <= alpha){
            //make tuple that has v+1 (cause max for min will be v-1) and is the move in the bestMove)
            vMove = std::make_tuple(v-1, get<1>(bestVMoves));
            return vMove; 
        }
    }
    
    return bestVMoves; 
}

list<int> ai::alphaBetaScearch(board b){
    std::tuple<int,std::__cxx11::list<int>> vMove;
    list<int> currentMove;
    list<int> bestMove;
    start = clock()/ CLOCKS_PER_SEC;
    maxDepth = 2;
    int depth = 0;
    int move;
    list<int> tempList;
    while(1){
        vMove = maxValue(b, currentMove, -999999, 999999, depth);

        list<int> tempList =  std::get<1>(vMove);
        int checkScore = std::get<0>(vMove);
        if(checkScore == specialScore){
            break;
        }
        maxDepth++;
        //depth++;
        // if( (point-start) < 5){
        //     maxDepth++;
        // }
        
        bestMove = tempList;
        //tempList.clear();
    }
    //end = clock()/ CLOCKS_PER_SEC;
    // cout<<"moves:\n";
    // for (auto i : bestMove){
    //     cout<<i<<endl;
    // }
    //cout<<"Max Depth: " << maxDepth <<endl;
    cout<<"The depth that was searched up to was: " << maxDepth << endl;
    return bestMove;
}