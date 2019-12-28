#ifndef NQUEENS_H
#define NQUEENS_H

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

class Backtrack
{
public:
    Backtrack();
    ~Backtrack();
    vector<vector<string>> solveNQueens(int n, int algorithm);
    void backtrack(vector<string>& board, int row);
    bool isValid(vector<string>& board, int row, int col);
    double getTime(){return time;}

private:
    vector<vector<string>> res;//保存所有解
    double time;
};

#endif // NQUEENS_H
