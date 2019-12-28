#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing()
{
    //构造函数
}

// 随机生成初始状态
void SimulatedAnnealing::initial() {
    queens = new int* [n];
    temp = new int* [n];
    for (int i = 0; i < n; ++i) {
        queens[i] = new int[n];
        temp[i] = new int[n];
        for (int j = 0; j < n; j++) {
            queens[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int num = rand() % n;
        queens[i][num] = 1;
    }
}

// 统计在该位置下所有皇后的冲突个数
int SimulatedAnnealing::findCollision(int row, int col) {
    int count = 0;
    // 该位置为1
    temp[row][col] = 1;
    for (int k = 0; k < n * n; k++) {
        if (temp[k / n][k % n] == 1) {
            for (int i = 0; i < n; i++)                             // 同一列
                if (i != k / n && temp[i][k % n] == 1)
                    count++;
            for (int i = k / n, j = k % n; i < n && j < n; i++, j++)    // 右下方
                if (i != k / n && temp[i][j] == 1)
                    count++;
            for (int i = k / n, j = k % n; i >= 0 && j >= 0; i--, j--)  // 左上方
                if (i != k / n && temp[i][j] == 1)
                    count++;
            for (int i = k / n, j = k % n; i < n && j >= 0; i++, j--)   // 左下方
                if (i != k / n && temp[i][j] == 1)
                    count++;
            for (int i = k / n, j = k % n; i >= 0 && j < n; i--, j++)   // 右上方
                if (i != k / n && temp[i][j] == 1)
                    count++;
        }
    }
    temp[row][col] = 0;  // 复原位置
    return count / 2;
}

bool SimulatedAnnealing::check(int** h)
{
    for (int i = 0; i < n; i++) {
        bool flag = false;
        for (int j = 0; j < n; j++) {
            if (queens[i][j] == 1 && h[i][j] == 0) { //皇后所在位置没有冲突
                flag = true;
                break;
            }
        }
        if (!flag) { // 皇后所在位置仍有冲突，还需要继续查找
            return false;
        }
    }
    return true;
}

// 模拟退火搜索
bool SimulatedAnnealing::simulated()
{
    double temperature = 5;
    int trial = 0;
    while (temperature > 0.00001) {
        // 拷贝原始棋盘数据到temp
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = queens[i][j];
            }
        }
        int** h = new int* [n];
        for(int i = 0; i < n; i++)
            h[i] = new int[n];
        int curState;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // 在计算h(i, j)之前，对i行所有位置赋值为0
                for (int k = 0; k < n; k++)
                    temp[i][k] = 0;
                // 查找h(i, j)
                h[i][j] = findCollision(i, j);
                // 当前状态的h值
                if (queens[i][j] == 1) {
                    curState = h[i][j];
                }
                // 计算h(i,j)之后要复原数据，避免计算错误
                for (int k = 0; k < n; k++)
                    temp[i][k] = queens[i][k];
            }
        }

        // 随机选取一个下一状态
        bool better = false;
        int next, nextState, times = 0;

        next = rand() % (n * n);
        nextState = h[next / n][next % n];
        int E = nextState - curState;
        if (E < 0) {
            better = true;
        }
        else if (exp((-1) * E / temperature) > ((double)(rand() % 1000) / 1000)) {
            better = true;
        }

        if (better) {
            for (int i = 0; i < n; i++)
                queens[next / n][i] = 0;
            queens[next / n][next % n] = 1;  // 放置皇后
            trial++;
        }

        // 判断是否找到解, 有解则返回值为真
        if (check(h)) {
            totalTrial += trial;
            return true;
        }

        temperature *= 0.99;
    }
    return false;
}

// 模拟退火搜索
void SimulatedAnnealing::simulatedAnnealing()
{
    int count = 0;
    for (int i = 0; i < 1000; i++) {
        initial();
        if (simulated())
            count++;
    }
//    return count;
}

vector<vector<string>> SimulatedAnnealing::solveNQueens(int n)
{
    this->n = n;
    clock_t start = clock();
    simulatedAnnealing();
    clock_t end = clock();
    time = (double)(end-start)/CLOCKS_PER_SEC;
    vector<vector<string>> res;
    vector<string> vec;
    for(int i = 0; i < n; i++)
    {
        string str;
        for(int j = 0; j < n; j++)
        {
            if(queens[i][j] == 1)
                str += 'Q';
            else
                str += '.';
        }
        vec.push_back(str);
    }
    res.push_back(vec);
    return res;
}
