#ifndef NQUEENS_H
#define NQUEENS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NQueens
{
public:
    NQueens();
    ~NQueens();
    vector<vector<string>> solveNQueens(int n, int algorithm);
    double getTime(){return time;}
private:
    double time;
};

#endif // NQUEENS_H
