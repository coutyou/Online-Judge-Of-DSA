#include <cstdlib>
#include "temperature.h"
using namespace std;

const int N = 1201;
const int M = 1201;
int dataMatrix[N][M];//数据矩阵
int treeMatrix[N][M];//二维树状数组
int _n;//用于记录行数
int _m;//用于记录列数

int lowbit(int t) //计算一维树状数组下标为t的项展开的项数
{
    return t & (-t);
}

int sum(int x, int y) //计算(0,0)到(x,y)之间矩形的和
{
    int result = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        for (int j = y; j > 0; j -= lowbit(j))
        {
            result += treeMatrix[i][j];
        }
    }
    return result;
}

void init(int n, int m, int **temp)
{
    //记下n,m的值
    _n = n;
    _m = m;
    //初始化为0
    for (int i = 1; i < _n + 1; i++)
    {
        for (int j = 1; j < _m + 1; j++)
        {
            dataMatrix[i][j] = 0;
            treeMatrix[i][j] = 0;
        }
    }
    //利用change函数将temp矩阵的值转移到我们定义的两个矩阵中
    for (int i = 1; i < _n + 1; i++)
    {
        for (int j = 1; j < _m + 1; j++)
        {
            change(i, j, temp[i][j]);
        }
    }
}

int query(int x1, int y1, int x2, int y2)//利用sum函数以及容斥原理计算总和
{
    int leftDown = sum(x1 - 1, y1 - 1);
    int left = sum(x1 - 1, y2);
    int down = sum(x2, y1 - 1);
    int all = sum(x2, y2);

    int total = all - left - down + leftDown;
    int pointCount = (x2 - x1 + 1) * (y2 - y1 + 1);

    return total / pointCount;
}

void change(int x, int y, int temp)
{
    //计算差值
    int delta = temp - dataMatrix[x][y];
    //修改数据矩阵的值
    dataMatrix[x][y] += delta;
    //修改二维树状数组的值
    for (int i = x; i < _n + 1; i += lowbit(i))
    {
        for (int j = y; j < _m + 1; j += lowbit(j))
        {
            treeMatrix[i][j] += delta;
        }
    }
}
