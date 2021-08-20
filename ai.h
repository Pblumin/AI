#ifndef _AI_H
#define _AI_H

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <tuple>
#include "board.h"

class ai {

    public:

    ai();

    void score(board b, int color);
    float WcurrentScore = 0;
    float RcurrentScore = 0;
    int specialScore = 10000;

    int maxDepth = 1;

    void result(board &b, int moveNum);

    std::tuple<int,std::__cxx11::list<int>> maxValue(board b, std::__cxx11::list<int> currentMove, int alpha, int beta, int depth);

    std::tuple<int,std::__cxx11::list<int>> minValue(board b, std::__cxx11::list<int> currentMove, int alpha, int beta, int depth);

    std::__cxx11::list<int> alphaBetaScearch(board b);

};

#endif //_AI_H