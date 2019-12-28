#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>

using namespace std;

class SimulatedAnnealing
{
private:
    int** queens;  //棋盘
    int** temp;
    int totalTrial;   // 统计移动步数
    int n;//皇后数
    double time;//耗时

public:
    SimulatedAnnealing();
    void initial();
    double getTime(){return time;}
    int findCollision(int row, int col);
    bool check(int** h);
    bool simulated();
    void simulatedAnnealing();
    vector<vector<string>> solveNQueens(int n);
};

#endif // SIMULATEDANNEALING_H
