#include "board.h"
#include "ai.h"
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;
using std::end;

board::board() {
    // char custom;
    // cout << "Would you like to use a custom position? (enter y for yes and n for no) \n";
    // cin >> custom;

    // if (custom == 'n'){
	//     startingpos();
    // } else {
    //     string inputFile;
    //     cout << "Enter name of input file: \n";
    //     cin >> inputFile;
    //     customPos(inputFile);
    //     iscustom = true;
    // }
}

board& board::operator=(const board& board){
    piece = board.piece;
    ix = board.ix;
    iy = board.iy;
    fx = board.fx;
    fy = board.fy;

    ix_jumped = board.ix_jumped;
    iy_jumped = board.iy_jumped;

    color = board.color;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            array[i][j] = board.array[i][j];
        }
    }

    xm = board.xm;
    ym = board.ym;

    return *this;

}

void board::startingpos(){
	
    //1 is black
    //2 is red
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i + j) % 2 == 0){
                this->array[i][j] = -1;
            }
            else{
                this->array[i][j] = 0;
            }
        }
    }

    this->array[0][1] = 1;
    this->array[0][3] = 1;
    this->array[0][5] = 1;
    this->array[0][7] = 1;
    this->array[1][0] = 1;
    this->array[1][2] = 1;
    this->array[1][4] = 1;
    this->array[1][6] = 1;
    this->array[2][1] = 1;
    this->array[2][3] = 1;
    this->array[2][5] = 1;
    this->array[2][7] = 1;

    this->array[5][0] = 2;
    this->array[5][2] = 2;
    this->array[5][4] = 2;
    this->array[5][6] = 2;
    this->array[6][1] = 2;
    this->array[6][3] = 2;
    this->array[6][5] = 2;
    this->array[6][7] = 2;
    this->array[7][0] = 2;
    this->array[7][2] = 2;
    this->array[7][4] = 2;
    this->array[7][6] = 2;


    // this->array[0][1] = 0;
    // this->array[0][3] = 0;
    // this->array[0][5] = 0;
    // this->array[0][7] = 0;
    // this->array[1][0] = 0;
    // this->array[1][2] = 0;
    // this->array[1][4] = 4;
    // this->array[1][6] = 0;
    // this->array[2][1] = 0;
    // this->array[2][3] = 0;
    // this->array[2][5] = 0;
    // this->array[2][7] = 0;

    // this->array[3][6] = 1;
    // this->array[4][5] = 2;

    // this->array[5][0] = 0;
    // this->array[5][2] = 2;
    // this->array[5][4] = 0;
    // this->array[5][6] = 0;
    // this->array[6][1] = 0;
    // this->array[6][3] = 0;
    // this->array[6][5] = 0;
    // this->array[6][7] = 0;
    // this->array[7][0] = 0;
    // this->array[7][2] = 0;
    // this->array[7][4] = 0;
    // this->array[7][6] = 0;


    // this->array[0][1] = 0;
    // this->array[0][3] = 0;
    // this->array[0][5] = 0;
    // this->array[0][7] = 0;
    // this->array[1][0] = 0;
    // this->array[1][2] = 0;
    // this->array[1][4] = 0;
    // this->array[1][6] = 0;
    // this->array[2][1] = 2;
    // this->array[2][3] = 0;
    // this->array[2][5] = 0;
    // this->array[2][7] = 0;

    // this->array[3][0] = 1;
    // this->array[4][1] = 2;

    // this->array[5][0] = 0;
    // this->array[5][2] = 2;
    // this->array[5][4] = 0;
    // this->array[5][6] = 0;
    // this->array[6][1] = 0;
    // this->array[6][3] = 0;
    // this->array[6][5] = 0;
    // this->array[6][7] = 0;
    // this->array[7][0] = 0;
    // this->array[7][2] = 0;
    // this->array[7][4] = 0;
    // this->array[7][6] = 0;
}

void board::printBoard(){
    cout<<"----------------------BOARD--------------------\n";
    //cout<<"   a  b  c  d  e  f  g  h\n";
    cout<<"   0  1  2  3  4  5  6  7\n";
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(j == 0){
                cout<<"\n";
                //cout << i+1 << " ";
                cout << i << " ";
            }
            if(this->array[i][j] == -1){
                //impossible spot to go to
                cout << "   ";
            } else if(this->array[i][j] == 0) {
                //possible spot to go to
                cout << " - ";     
            } else if(this->array[i][j] == 1) {
                //regular black
                cout << " 1 ";     
            } else if(this->array[i][j] == 2) {
                //regular red
                cout << " 2 ";     
            } else if(this->array[i][j] == 3) {
                //regular red
                cout << " 3 ";     
            } else {
                cout << " 4 "; 
            }
        }
    }
    cout<<"\n";
    cout<<"----------------------BOARD--------------------\n";
    // cout <<"help\n";
    // cout<<this->array[0][7]<<endl; 
}

int board::rgetRN(int ix, int iy){
    int startpiece = this->array[iy][ix];
    int rn = -1;
    fx = 0;
    fy = 0;
    
    if(ix == 0){
        rn = this->array[iy+1][ix+1];
        fx = iy + 1;
        fy = ix + 1;
    } else if(ix == 7){
        rn = -1;
    } else {
        rn = this->array[iy+1][ix+1];
        fx = iy + 1;
        fy = ix + 1;
    }

    if ( (fy != 8) && (fx != 8)  && (fy != -1) && (fx != -1)){ 
        xm.push_back(fx);
        ym.push_back(fy);
        return rn;
    } else {
        return -1;
    }
}

int board::wgetRN(int ix, int iy){
    int startpiece = this->array[iy][ix];
    int rn = -1;
    fx = 0;
    fy = 0;
    if(ix == 0){
        rn = this->array[iy-1][ix+1];
        fx = iy - 1;
        fy = ix + 1;
    } else if(ix == 7){
        rn = -1;
    } else {
        rn = this->array[iy-1][ix+1];
        fx = iy - 1;
        fy = ix + 1;
    }  

    if ( (fy != 8) && (fx != 8)  && (fy != -1) && (fx != -1)){ 
        xm.push_back(fx);
        ym.push_back(fy);
        return rn;
    } else {
        return -1;
    }
}

int board::rgetLN(int ix, int iy){
    int startpiece = this->array[iy][ix];
    int ln;
    fx = 0;
    fy = 0;
    if(ix == 0){
        ln = -1;
    } else if(ix == 7){
        ln = this->array[iy+1][ix-1];
        fx = iy + 1;
        fy = ix - 1;
    } else {
        ln = this->array[iy+1][ix-1];
        fx = iy + 1;
        fy = ix - 1;
    }
    if ( (fy != 8) && (fx != 8)  && (fy != -1) && (fx != -1)){ 
        xm.push_back(fx);
        ym.push_back(fy);
        return ln;
    } else {
        return -1;
    }
}

int board::wgetLN(int ix, int iy){
    int startpiece = this->array[iy][ix];
    int ln;
    fx = 0;
    fy = 0;
    if(ix == 0){
        ln = -1;
    } else if(ix == 7){
        ln = this->array[iy-1][ix-1];
        fx = iy - 1;
        fy = ix - 1;
    } else {
        ln = this->array[iy-1][ix-1];
        fx = iy - 1;
        fy = ix - 1;
    }  

    if ( (fy != 8) && (fx != 8)  && (fy != -1) && (fx != -1)){ 
        xm.push_back(fx);
        ym.push_back(fy);
        return ln;
    } else {
        return -1;
    }
}


void board::rlegalMoves(int ix, int iy){
    //cout<< "Piece you want to move: " << ix << ", " << iy << endl;

    int flag = 0;
    if ((moveMade == true) && ((ix != ix_jumped) || (iy != iy_jumped)) ){
        flag = 1;
    }

    //cout << "test\n";

    int startpiece = this->array[iy][ix];
    std::tuple<int,int,int,int> moves;
    int a = -1;
    //int b = -1;
    int ln = rgetLN(ix,iy);
    int rn = rgetRN(ix,iy);
    list<int>::iterator it1 = xm.begin();
    list<int>::iterator it2 = ym.begin();
    // std::advance(it1, 0);
    // std::advance(it2, 0);
    //if (jump == true) cout<<"last move was a jump\n";
    if( (startpiece == 1 || startpiece == 3) && flag == 0) {
        //cout<<rn<<endl;
        //cout << this->array[1][2] <<endl;
        if (ln == 0 && jump == false){
            std::advance(it1, 0);
            std::advance(it2, 0);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2 << ", "  <<  *it1 <<endl;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            if (*it1 != 8) {
                listOfMoves.push_back(moves);
            }
        } 
        else if (ln == 2 || ln == 4) {
            int lnNew = rgetLN(*it2,*it1);
            a = lnNew;
            //cout << lnNew << endl;
            //int rnNew = getRN(*it2,*it1);
            //cout<<*it2<<endl;
            //cout<<*it1<<endl;
            if (lnNew == 0){
                std::advance(it1, 2);
                std::advance(it2, 2);
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if ( (jump == false) && (*it1 != 0) && (*it1 != 8)){
                    listOfMoves.clear();
                }
                if ((*it1 != 0) && (*it1 != 8)) {
                    listOfMoves.push_back(moves);
                    jump = true;
                    jCount++;
                }
            }
            else { 
                //jump = false;
                jCount = 0;
            }
        } 
        else {
            //jump = false;
            //jCount = 0;
        }

        if (rn == 0 && jump == false){
            std::advance(it1, 1);
            std::advance(it2, 1);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2   << ", "  << *it1  <<endl;
            //cout<<*it2<<endl;
            //cout<<*it1<<endl;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            if (*it1 != 8) {
                listOfMoves.push_back(moves);
            }
            legal = true;
        } 
        else if (rn == 2 || rn == 4) {
            //cout<<"jcount: "<<jCount<<endl;
            //cout<<a<<endl;
            //cout << rn << endl;
            if (jCount == 0 ) {
                //cout<<"hi1\n";
                std::advance(it1, 1);
                std::advance(it2, 1);
            } else if ( (startpiece == 3) && (a != 0) ){
                //cout<<"hi2\n";
                std::advance(it1, 4);
                std::advance(it2, 4);
            } else if (a == 0){ 
                //cout<<"hi3\n";
                std::advance(it1, 3);
                std::advance(it2, 3);
                //cout<<"hi"<<endl;
            } else {
                //cout<<"hi4\n";
                std::advance(it1, 1);
                std::advance(it2, 1);
            }
            //cout<<*it2<<endl;
            //cout<<*it1<<endl;
            int rnNew = rgetRN(*it2,*it1);
            //cout << a <<endl;
            if (rnNew == 0){
                if ((jCount == 0) && (startpiece == 1) && (ln == 2 || ln == 4) ){
                    std::advance(it1, 2);
                    std::advance(it2, 2);
                    //cout<<"hi1"<<endl;
                } else if((jCount == 0) && (startpiece == 1) && (a != 0)){
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi2"<<endl;
                } else if((jCount == 0) && (startpiece == 3)) { 
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi2"<<endl;
                } else if ( (startpiece == 3) && (a != 0) ) {
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi3"<<endl;
                } else if ( (startpiece == 3) && (a == 0) ) {
                    std::advance(it1, 2);
                    std::advance(it2, 2);
                    //cout<<"hi4"<<endl;
                } else {
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi4"<<endl;
                }
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if ( (jump == false) && (*it1 != 0) && (*it1 != 8)){
                    listOfMoves.clear();
                }
                if ((*it1 != 0) && (*it1 != 8)) {
                    listOfMoves.push_back(moves);
                    jump = true;
                    jCount++;
                }
            }
            else {
                //jump = false;
                //jCount = 0;
            }
        } 
        else {
            //cout << "no valid right moves\n";
            //jump = false;
            //jCount = 0;
        }
    } 
    else {
        //cout << "No piece on square\n";
        legal = false;
        //jump = false;
        //jCount = 0;
    }
    xm.clear();
    ym.clear();

}

void board::wlegalMoves(int ix, int iy){
    //cout<< "Piece you want to move: " << ix << ", " << iy << endl

    int flag = 0;
    if ((moveMade == true) && ((ix != ix_jumped) || (iy != iy_jumped)) ){
        flag = 1;
    }

    int startpiece = this->array[iy][ix];
    int a = -1;
    std::tuple<int,int,int,int> moves;
    int ln = wgetLN(ix,iy);
    int rn = wgetRN(ix,iy);
    list<int>::iterator it1 = xm.begin();
    list<int>::iterator it2 = ym.begin();
    if( (startpiece == 2 || startpiece == 4) && flag == 0) {
        if (ln == 0 && jump == false){
            std::advance(it1, 0);
            std::advance(it2, 0);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2 << ", "  <<  *it1 <<endl;
            legal = true;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            listOfMoves.push_back(moves);
        } 
        else if (ln == 1 || ln == 3) {
            int lnNew = wgetLN(*it2,*it1);
            a = lnNew;
            //cout << lnNew << endl;
            //int rnNew = getRN(*it2,*it1);
            if (lnNew == 0){
                std::advance(it1, 2);
                std::advance(it2, 2);
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if (jump == false){
                    listOfMoves.clear();
                }
                listOfMoves.push_back(moves);
                jump = true;
                jCount++;
            }
            else { 
                jCount = 0;
            }
        } else {

        }

        if (rn == 0 && jump == false){
            std::advance(it1, 1);
            std::advance(it2, 1);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2   << ", "  << *it1  <<endl;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            listOfMoves.push_back(moves);
            legal = true;
        } 
        else if (rn == 1 || rn == 3) {
            if (jCount == 0 ) {
                std::advance(it1, 1);
                std::advance(it2, 1);
            } else if ( (startpiece == 4) && (a != 0) ){
                std::advance(it1, 4);
                std::advance(it2, 4);
            } else if (a == 0){ 
                std::advance(it1, 3);
                std::advance(it2, 3);
                //cout<<"hi1\n";
            } else {
                std::advance(it1, 1);
                std::advance(it2, 1);
                //cout<<"hi2\n";
            }
            //cout<<*it2<<endl;
            //cout<<*it1<<endl;
            int rnNew = wgetRN(*it2,*it1);
            //cout<<rnNew<<endl;
            //cout<<a<<endl;
            if (rnNew == 0){
                if ((jCount == 0) && (startpiece == 2) && (ln != 3 && ln != 1)){
                    //cout<<ln<<endl;
                    //cout<<"hi1\n";
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                } else if ((jCount == 0) && (startpiece == 2) && (ln == 1 || ln == 3)){
                    //cout<<"hi2"<<endl;
                    std::advance(it1, 2);
                    std::advance(it2, 2);
                } else if((jCount == 0) && (startpiece == 4)) {
                    //cout<<"hi1\n"; 
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                } else if ( (startpiece == 4) && (a != 0) && (jCount == 0) ) {
                    //cout<<"h2\n"; 
                    std::advance(it1, 3);
                    std::advance(it2, 3);
                } else if((jCount != 0) && (a != 0)) {
                    //cout<<"hi3\n"; 
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                } else {
                    //cout<<"hi4\n";
                    std::advance(it1, 2);
                    std::advance(it2, 2);
                }
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if (jump == false){
                    listOfMoves.clear();
                }
                listOfMoves.push_back(moves);
                jump = true; 
                jCount++;
            }
            else {
                //jCount = 0;
            }
        } 
        else {
            //cout << "no valid right moves\n";
            legal = false;
        }
    } 
    else {
        //cout << "No piece on square\n";
        legal = false;
    }
    xm.clear();
    ym.clear();
}

void board::klegalMoves(int ix, int iy){

    int flag = 0;
    //jump = false;
    if ((moveMade == true) && ((ix != ix_jumped) || (iy != iy_jumped)) ){
        flag = 1;
    }
    

    int a = -1;
    //cout << flag <<endl;
    int startpiece = this->array[iy][ix];
    std::tuple<int,int,int,int> moves;

    if( (startpiece == 3) && (flag == 0) && (color == 1) ){
        //LEGAL MOVES FOR RED KING
        //regular foward moves
        //rlegalMoves(ix,iy);

        //bottom left and right neighbors

        int bln = wgetLN(ix,iy);
        int brn = wgetRN(ix,iy);

        list<int>::iterator it1 = xm.begin();
        list<int>::iterator it2 = ym.begin();

        if (bln == 0 && jump == false){
            std::advance(it1, 0);
            std::advance(it2, 0);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2 << ", "  <<  *it1 <<endl;
            legal = true;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            listOfMoves.push_back(moves);
        } else if (bln == 2 || bln == 4) {
            int lnNew = wgetLN(*it2,*it1);
            a = lnNew;
            //cout << lnNew << endl;
            //int rnNew = getRN(*it2,*it1);
            if (lnNew == 0){
                std::advance(it1, 2);
                std::advance(it2, 2);
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if (jump == false){
                    listOfMoves.clear();
                }
                listOfMoves.push_back(moves);
                jump = true;
                jCount++;
            }
            else { 
                jCount = 0;
            }
        } else {

        }
        //cout<<jCount<<endl;
        if (brn == 0 && jump == false){
            std::advance(it1, 1);
            std::advance(it2, 1);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2   << ", "  << *it1  <<endl;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            listOfMoves.push_back(moves);
            legal = true;
        } else if (brn == 2 || brn == 4) {
            //cout<<"hi1\n";
            if ((jCount == 0) || (a != 0)) {
                std::advance(it1, 1);
                std::advance(it2, 1);
            } else {
                std::advance(it1, 3);
                std::advance(it2, 3);
            }
            // std::advance(it1, 1);
            // std::advance(it2, 1);
            //cout<<*it1<<endl;
            //cout<<*it2<<endl;
            int rnNew = wgetRN(*it2,*it1);
            //cout<<rnNew<<endl;
            if (rnNew == 0){
                //cout<<"hi2\n";
                if ( ( (jCount == 0) || (a != 0) ) && (bln != 2) && (bln != 4)){
                    //cout<<"hi1\n";
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                } else {
                    //cout<<"hi2\n";
                    std::advance(it1, 2);
                    std::advance(it2, 2);
                }
                // std::advance(it1, 1);
                // std::advance(it2, 1);
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if (jump == false){
                    listOfMoves.clear();
                }
                listOfMoves.push_back(moves);
                jump = true; 
                jCount++;
            }
            else {
                //jCount = 0;
            }
        } 

        xm.clear();
        ym.clear();

    } else if ( (startpiece == 4) && (flag == 0) && (color == 0) ){
        //LEGAL MOVES FOR WHITE KING
        //bottom left and right neighbors
        int bln1 = rgetLN(ix,iy);
        int brn1 = rgetRN(ix,iy);

        list<int>::iterator it1 = xm.begin();
        list<int>::iterator it2 = ym.begin();

        if (bln1 == 0 && jump == false){
            std::advance(it1, 0);
            std::advance(it2, 0);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2 << ", "  <<  *it1 <<endl;
            legal = true;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            if (*it1 != 8) {
                listOfMoves.push_back(moves);
            }
        } 
        else if (bln1 == 1 || bln1 == 3) {
            int lnNew = rgetLN(*it2,*it1);
            a = lnNew;

            //cout << lnNew << endl;
            //int rnNew = getRN(*it2,*it1);
            if (lnNew == 0){
                std::advance(it1, 2);
                std::advance(it2, 2);
                moves = std::make_tuple(ix,iy,*it2,*it1);
                if ( (jump == false) && (*it1 != 0) && (*it1 != 8)){
                    listOfMoves.clear();
                }
                if ((*it1 != 0) && (*it1 != 8)) {
                    listOfMoves.push_back(moves);
                    jump = true;
                    jCount++;
                }
            }
            else { 
                //jump = false;
                jCount = 0;
            }
        } 
        else {
            //jump = false;
            //jCount = 0;
        }

        if (brn1 == 0 && jump == false){
            std::advance(it1, 1);
            std::advance(it2, 1);
            //cout << "Valid Move: " << ix << ", " << iy << "--->" << *it2   << ", "  << *it1  <<endl;
            moves = std::make_tuple(ix,iy,*it2,*it1);
            if (*it1 != 8) {
                listOfMoves.push_back(moves);
            }
            legal = true;
        } else if (brn1 == 1 || brn1 == 3) {
            if ( (jCount == 0) || (a != 0)  ) {
                std::advance(it1, 1);
                std::advance(it2, 1);
            } else {
                std::advance(it1, 3);
                std::advance(it2, 3);
            }
            // cout<<*it2<<endl;
            // cout<<*it1<<endl;
            int rnNew = rgetRN(*it2,*it1);
            if (rnNew == 0){
                if ( (jCount == 0) && (a!=0) ){
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi1\n";
                } else if(jCount == 0) {
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi2\n";
                } else {
                    std::advance(it1, 1);
                    std::advance(it2, 1);
                    //cout<<"hi3\n";
                }

                moves = std::make_tuple(ix,iy,*it2,*it1);
                if ( (jump == false) && (*it1 != 0) && (*it1 != 8) ){
                    listOfMoves.clear();
                }
                if ( (*it1 != 0) && (*it1 != 8)) {
                    listOfMoves.push_back(moves);
                    jump = true;
                    jCount++;
                }
            }
            else {
                //jump = false;
                //jCount = 0;
            }
        }

        xm.clear();
        ym.clear();

    } else {
        //DO NOTHING
    }
}

void board::switchColor(){
    if(color == 1){
        color = 0;
    } else {
        color = 1;
    }
}

void board::makeMove(int ix, int iy, int fx, int fy){
    // std::cout<<"before: \n";
    // printBoard();
    doSwitch = false;
    int p = king(ix, iy, fx, fy);
    if(p == -1){
        ix = fx;
        iy = fy;
        this->array[fy][fx] = this->array[iy][ix];
        doSwitch = true;
        jump = false;
        moveMade = false;
        jCount = 0;
    } else {
    
        if (jump == false){
            this->array[fy][fx] = p;
            this->array[iy][ix] = 0;
            //switchColor();
            doSwitch = true;
            jCount = 0;
            
            //cout<<"hi1"<<endl;
        } else {
            if (jCount != 0){
                this->array[fy][fx] = p;
                this->array[iy][ix] = 0;
                this->array[(fy + iy)/2][(fx + ix)/2] = 0;
                ix_jumped = fx;
                iy_jumped = fy;
                //cout << iy_jumped << ", " << ix_jumped <<endl;
                moveMade = true;
                //cout<<"hi2"<<endl;
            } else {
                this->array[fy][fx] = p;
                this->array[iy][ix] = 0;
                this->array[(fy + iy)/2][(fx + ix)/2] = 0;
                jump = false;
                ix_jumped = ix;
                iy_jumped = iy;
                moveMade = false;
                doSwitch = true;
                //switchColor();
                jCount = 0;
                //cout<<"hi3"<<endl;
            }
        }
    }
    // std::cout<<"after: \n";
    // printBoard();
    //king(fx,fy);
}

int board::king(int a, int b, int i, int j) {
    // cout << color << endl;
    // cout << ix << endl;
    // cout << iy << endl;
    if( (a > 7) || (b > 7) || (i > 7) || (j > 7) ){
        return -1;
    }
    int startPiece = this->array[b][a];
    int piece = this->array[j][i];
    // cout << "piece: " << piece <<endl;
    // cout<<j<<endl;

    if ( (startPiece != 3) && (startPiece != 4) ){
        isKing = false;
    } else {
        isKing = true;
    }

    if( (color == 1) && (j == 7) ){
        this->array[j][i] == 3;
        isKing = true;
        return 3;
    } else if ( (color == 0) && (j == 0) ){
        this->array[j][i] == 4;
        isKing = true;
        return 4;
    } else if ( (color == 1) && (isKing == false) ){
        isKing = false;
        return 1;
    } else if ( (color == 0) && (isKing == false) ){
        isKing = false;
        return 2;
    } else if( (color == 1) && (isKing == true) ) {
        return 3;
    } else if( (color == 0) && (isKing == true) ) {
        return 4;
    } else {
        cout<<"something went wrong in king function\n";
        return 0;
    }

}

void board::user(){

    // cout << "Enter 1 for red and 0 for white: \n";
    // cin >> color;
    
    // if(color == 1){
    //     cout << "you are red" << endl;
    // } else if(color == 0){
    //     cout << "you are white" << endl;
    // } else {
    //     cout << color << endl;
    // }

    if (iscustom == false){ 
        color = 1;
    } else {
        char q3;
        cout << "Whos move is it in this position? (enter r for red and w for white) \n";
        cin >> q3;
        if (q3 == 'r'){
            color = 1;
        } else if (q3 == 'w'){
            color = 0;
        } 
    }

    char q1;
    char q2;
    cout << "Is player 1 a bot? (enter y for yes and n for no) \n";
    cin >> q1;

    cout << "Is player 2 a bot? (enter y for yes and n for no) \n";
    cin >> q2;

    if (q1 == 'y'){
        botp1 = true;
    }

    if (q2 == 'y'){
        botp2 = true;
    }

}

void board::movesList(){
    listOfMoves.clear();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            piece = this->array[i][j];
            if(color == 1){
                //cout<<"hello\n";
                if (piece == 1){
                    rlegalMoves(j,i);
                } else {
                    rlegalMoves(j,i);
                    klegalMoves(j,i);
                }
                //color = 0;
            } else if (color == 0){
                
                if (piece == 2) {
                    wlegalMoves(j,i);
                } else {
                    wlegalMoves(j,i);
                    klegalMoves(j,i);
                }
            }
        }
    }
}

void board::displayMoves(){

    printBoard();
    ai a;
    //board b;

    if(color == 1){
        cout<<"Its Player 1's turn"<<endl;
    } else {
        //cout<<color<<endl;
        cout<<"Its Player 2's turn"<<endl;
    }

    movesList();

    if( (listOfMoves.empty() == true) && (jump == false) && (moveMade == false) ) {
        //cout<<"I am Here\n";
        noMoves = true;
    } else {

        if( (listOfMoves.empty()) && (jump == true)){
            cout<<"No More Jumps\n";
            switchColor();
            jump = false;
            moveMade = false;
        } else {
            
            int n = 1;
            //cout << listOfMoves.size() <<endl;
            for(auto i = listOfMoves.begin(); i != listOfMoves.end(); ++i){
                cout << n << ": ";
                cout << std::get<0>(*i) << ", ";
                cout << std::get<1>(*i) << "--->";
                cout << std::get<2>(*i) << ", ";
                cout << std::get<3>(*i) << endl;
                n++;
                
            }

            if ( (color == 1) && (botp1 == true) ){
                auto it = listOfMoves.cbegin();
                list<int> absMoves;
                int bestMove;
                if(listOfMoves.size() == 1){
                    bestMove = 0;
                } else {
                    clock_t start1, end1;
                    start1 = clock() / CLOCKS_PER_SEC;
                    
                    // while ((point - start) < 5){ 
                    //     start = clock() / CLOCKS_PER_SEC;
                    //     bestMove = a.alphaBetaScearch(board());
                    //     point = clock() / CLOCKS_PER_SEC;
                    //     a.maxDepth++;
                    // }
                    //printBoard();
                    //cout<<"List of moves size "<<listOfMoves.size()<<endl;
                    absMoves = a.alphaBetaScearch(*this);
                    end1 = clock() / CLOCKS_PER_SEC;
                    bestMove = absMoves.front();
                    cout<<"Time taken to search in seconds is: " << (end1 - start1) << endl;
                }
                cout<<"Best move: " << bestMove << endl;
                std::advance(it, bestMove);

                // srand((unsigned) time(0));
                // int randomMove = rand() % listOfMoves.size();
                // std::advance(it, randomMove);

                makeMove( std::get<0>(*it) , std::get<1>(*it) , std::get<2>(*it) , std::get<3>(*it) );
                if(doSwitch == true){
                    switchColor();
                }
                listOfMoves.clear();

                //print out the move bot made
                cout << "Move player 1 bot made: ";
                cout << bestMove << ": ";
                cout << std::get<0>(*it) << ", ";
                cout << std::get<1>(*it) << "--->";
                cout << std::get<2>(*it) << ", ";
                cout << std::get<3>(*it) << endl;

            } else if ( (color == 0) && (botp2 == true) ){
                auto it = listOfMoves.cbegin();
                list<int> absMoves;

                int bestMove = 0;
                if(listOfMoves.size() == 1){
                    bestMove = 0;
                } else {
                    clock_t start, end;
                    start = clock() / CLOCKS_PER_SEC;
                    // while ((point1 - start1) < 5){ 
                    //     start1= clock() / CLOCKS_PER_SEC;
                    //     bestMove = a.alphaBetaScearch(board());
                    //     point1 = clock() / CLOCKS_PER_SEC;
                    //     a.maxDepth++;
                    // }
                    //printBoard();
                    //cout<<"List of moves size "<<listOfMoves.size()<<endl;
                    absMoves = a.alphaBetaScearch(*this);
                    end = clock()/ CLOCKS_PER_SEC;;
                    bestMove = absMoves.front();
                    cout<<"Time taken to search in seconds is is: " << (end - start) << endl;

                }
                
                // srand((unsigned) time(0));
                // int randomMove = rand() % listOfMoves.size();
                // std::advance(it, randomMove);
                cout<<"Best move: " << bestMove << endl;
                std::advance(it, bestMove);

                

                makeMove( std::get<0>(*it) , std::get<1>(*it) , std::get<2>(*it) , std::get<3>(*it) );
                if(doSwitch == true){
                    switchColor();
                }
                listOfMoves.clear();

                //print out the move bot made
                cout << "Move player 2 bot made: ";
                cout << bestMove << ": ";
                cout << std::get<0>(*it) << ", ";
                cout << std::get<1>(*it) << "--->";
                cout << std::get<2>(*it) << ", ";
                cout << std::get<3>(*it) << endl;

            } else {

                int a;
                cout<< "Which move would you like to make?\n";
                cin >> a;

                auto it = listOfMoves.begin();
                std::advance(it, a-1);
                makeMove( std::get<0>(*it) , std::get<1>(*it) , std::get<2>(*it) , std::get<3>(*it) );
                if(doSwitch == true){
                    switchColor();
                }

                listOfMoves.clear();
            }
        }
    }
    // cout << "The score for player 1 is: " << a.RcurrentScore << endl;
    // cout << "The score for player 2 is: " << a.WcurrentScore << endl;
}

void board::play(){
    int a,b,c,d;
    char comma;

    //int a;
    cout << "From these moves please type in the cordinates of piece that you want to start: \n";
    cin >> a >> comma >> b;

    cout << "From these moves please type in the cordinates of where you want to go: \n";
    cin >> c >> comma >> d;

    // cout<< "Select move number: \n";
    // cin >> a;


    makeMove(a,b,c,d);
    
    // for(auto i = listOfMoves.begin(); i != listOfMoves.end(); ++i){
    //     //cout << i << ": ";
    //     cout << std::get<0>(*i) << ", ";
    //     cout << std::get<1>(*i) << "--->";
    //     cout << std::get<2>(*i) << ", ";
    //     cout << std::get<3>(*i) << endl;
    //     a = std::get<0>(a);
    // }

    // if( (listOfMoves.empty()) && (jump == true) ){
    //     switchColor();
    //     jump = false;
    // }

    listOfMoves.clear();
    
}


bool board::gameOver(){
    std::vector<int> remainingPieces;
    rp = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int piece = this->array[i][j];
            remainingPieces.push_back(piece);
            if( (piece == 1) || (piece == 2) || (piece == 3) || (piece == 4) ){
                rp++;
            }
        }
    }
    
    bool rpiece = std::count(remainingPieces.begin(), remainingPieces.end(), 1);
    bool rking = std::count(remainingPieces.begin(), remainingPieces.end(), 3);
    bool wpiece = std::count(remainingPieces.begin(), remainingPieces.end(), 2);
    bool wking = std::count(remainingPieces.begin(), remainingPieces.end(), 4);
    
    if( (rpiece || rking) && !(wpiece || wking) ){
        cout << "Red Wins!\n";
        return true;
    } else if( !(rpiece || rking) && (wpiece || wking) ){
        cout << "White Wins!\n";
        return true;
    } else if( (noMoves == true) && (color == 0) ){
        cout << "White had no more moves left. Red Wins!\n";
        return true;
    } else if( (noMoves == true) && (color == 1) ){
        cout << "Red had no more moves left. White Wins!\n";
        return true;
    }
    else {
        return false;
    }

}

void board::customPos(string inputFile){
    string line;
    int piece;
    vector<int> customb;
    ifstream inputFileStream(inputFile);
    while (getline(inputFileStream, line)){
        piece = stoi(line);
        customb.push_back(piece);
    }
    inputFileStream.close();

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i + j) % 2 == 0){
                this->array[i][j] = -1;
            }
            else{
                this->array[i][j] = 0;
            }
        }
    }

    this->array[0][1] = customb[0];
    this->array[0][3] = customb[1];
    this->array[0][5] = customb[2];
    this->array[0][7] = customb[3];

    this->array[1][0] = customb[4];
    this->array[1][2] = customb[5];
    this->array[1][4] = customb[6];
    this->array[1][6] = customb[7];

    this->array[2][1] = customb[8];
    this->array[2][3] = customb[9];
    this->array[2][5] = customb[10];
    this->array[2][7] = customb[11];

    this->array[3][0] = customb[12];
    this->array[3][2] = customb[13];
    this->array[3][4] = customb[14];
    this->array[3][6] = customb[15];

    this->array[4][1] = customb[16];
    this->array[4][3] = customb[17];
    this->array[4][5] = customb[18];
    this->array[4][7] = customb[19];

    this->array[5][0] = customb[20];
    this->array[5][2] = customb[21];
    this->array[5][4] = customb[22];
    this->array[5][6] = customb[23];

    this->array[6][1] = customb[24];
    this->array[6][3] = customb[25];
    this->array[6][5] = customb[26];
    this->array[6][7] = customb[27];

    this->array[7][0] = customb[28];
    this->array[7][2] = customb[29];
    this->array[7][4] = customb[30];
    this->array[7][6] = customb[31];
    
}

// int main(){

//     board b;

//     // b.printBoard();
//     // //cout << "Hello";
    
//     // //cout<<"Right N: " << b.getRN(1,2) << endl;
//     // //cout<<"Left N: " << b.getLN(1,2) << endl;
//     // for(int i = 0; i < 8; i++){
//     //     for(int j = 0; j < 8; j++){
//     //         b.rlegalMoves(j,i);
//     //     }
//     // }

//     // b.makeMove(1,2,0,3);
//     // b.printBoard();
//     b.user();
//     bool error = false;
//     while(!b.gameOver()){
//         b.displayMoves();
//         for(int i = 0; i < 8; i++){
//             for(int j = 0; j < 8; j++){
//                 if((i + j) % 2 == 0){
//                     if( (b.array[i][j] == 1) || (b.array[i][j] == 2) || (b.array[i][j] == 3) || (b.array[i][j] == 4)) {
//                         cout<<"OH NO\n";
//                         error = true;
//                         break;
//                     }
//                 }
//             }
//         }
//         if (error == true){
//             break;
//         }
//         b.moveCount++;
//         //b.play();
//     }
 
//     cout<<"Moves: "<<b.moveCount<<endl;
//     return 0;
// }
