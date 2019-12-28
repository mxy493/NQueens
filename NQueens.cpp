#include "NQueens.h"
#include "Backtrack.h"

NQueens::NQueens()
{
    //构造函数
}

NQueens::~NQueens()
{
    //析构函数
}

//转向对应算法
vector<vector<string>> NQueens::solveNQueens(int n, int algorithm) {
    // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
    if(algorithm == 0){
        //回溯法
        Backtrack queen;
        vector<vector<string>> res = queen.solveNQueens(n);
        time = queen.getTime();
        return res;
    }
    else if (algorithm == 1){
        //遗传算法
    }
    else if (algorithm == 2){
        //模拟退火
    }
    else if(algorithm == 3){
        //爬山法
    }
}
