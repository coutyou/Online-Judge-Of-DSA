#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    //创建有向无环图的相关数组并根据输入内容进行初始化
    int n, m;
    scanf("%d %d", &n, &m);

    int *inDegree = new int[n];        //储存每个点的入度
    int *topologicalSort = new int[n]; //储存拓扑排序的结果
    int *maxPath = new int[n];         //用于保存到该节点最长路径的长度
    for (int i = 0; i < n; i++)
    {
        inDegree[i] = 0;
        topologicalSort[i] = 0;
        maxPath[i] = 0;
    }

    int **edge = new int *[n]; //邻接矩阵储存有向无环图的边的信息
    for (int i = 0; i < n; i++)
    {
        edge[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            edge[i][j] = 0;
        }
    }

    //将输入数据导入邻接矩阵
    int from, to, price;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &from, &to, &price);
        if (edge[from - 1][to - 1] == 0)
        {
            edge[from - 1][to - 1] = price;
            inDegree[to - 1]++;
        }
        else if (edge[from - 1][to - 1] < price)
        {
            edge[from - 1][to - 1] = price;
        }
    }

    //进行拓扑排序
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (inDegree[j] == 0) //找到入度为0的点
            {
                topologicalSort[i] = j;     //存入数组中
                inDegree[j] = -1;           //将其入度置为负数
                for (int k = 0; k < n; k++) //并更新其他点的入度
                {
                    if (edge[j][k] != 0)
                    {
                        inDegree[k]--;
                    }
                }
                break; //退出循环
            }
        }
    }

    //寻找能赚最多钱的路线
    for (int i = 0; i < n; i++)
    {
        to = topologicalSort[i];
        for (int j = 0; j < i; j++)
        {
            from = topologicalSort[j];
            if (edge[from][to] != 0) //表示有路
            {
                if (maxPath[from] + edge[from][to] > maxPath[to])
                {
                    maxPath[to] = maxPath[from] + edge[from][to];
                }
            }
        }
    }

    //找到maxPath中最大值
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (maxPath[i] > max)
        {
            max = maxPath[i];
        }
    }
    printf("%d",max);
    return 0;
}
