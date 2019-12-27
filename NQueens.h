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
    vector<vector<string>> solveNQueens(int n);
    void backtrack(vector<string>& board, int row);
    bool isValid(vector<string>& board, int row, int col);

private:
    vector<vector<string>> res;
};

#endif // NQUEENS_H
