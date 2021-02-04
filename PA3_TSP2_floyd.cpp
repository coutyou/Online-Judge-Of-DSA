#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define INF -0xfffffff

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    int n, m;
    scanf("%d %d", &n, &m);

    //创建有向无环图的相关数组并根据输入内容进行初始化
    int *inDegree = new int[n];        //储存每个点的入度
    int *topologicalSort = new int[n]; //储存拓扑排序的结果
    int *maxPath = new int[n];         //用于保存到该节点最长路径的长度
    int *dad = new int[n];             //用于保存该节点是否有父节点
    int *ancestor = new int[n];        //用于保存路径的第一个节点
    for (int i = 0; i < n; i++)
    {
        inDegree[i] = 0;
        topologicalSort[i] = 0;
        maxPath[i] = 0;
        dad[i] = -1;
        ancestor[i] = -1;
    }

    int **edge = new int *[n]; //邻接矩阵储存有向无环图的边的信息
    int **next = new int *[n]; //用于记录下一个节点的值
    int **edgeToTopo = new int *[n];
    for (int i = 0; i < n; i++)
    {
        edge[i] = new int[n];
        next[i] = new int[n];
        edgeToTopo[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            edge[i][j] = INF;
            next[i][j] = j;
            edgeToTopo[i][j] = 0;
        }
    }

    //将输入数据导入邻接矩阵
    int from, to, price;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &from, &to, &price);
        if (edge[from - 1][to - 1] == INF)
        {
            edge[from - 1][to - 1] = price;
        }
        else if (edge[from - 1][to - 1] < price)
        {
            edge[from - 1][to - 1] = price;
        }
        if (edgeToTopo[from - 1][to - 1] == 0)
        {
            edgeToTopo[from - 1][to - 1] = price;
            inDegree[to - 1]++;
        }
        else if (edgeToTopo[from - 1][to - 1] < price)
        {
            edgeToTopo[from - 1][to - 1] = price;
        }
    }


    //floyd
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (edge[i][k] + edge[k][j] > edge[i][j])
                {
                    edge[i][j] = edge[i][k] + edge[k][j];
                    next[i][j] = next[i][k];
                }
                else if (edge[i][k] + edge[k][j]  == edge[i][j])
                {
                    if (next[i][j] > next[i][k])
                    {
                        next[i][j] = next[i][k];
                    }
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
                    if (edgeToTopo[j][k] != 0)
                    {
                        inDegree[k]--;
                    }
                }
                break; //退出循环
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        to = topologicalSort[i];
        for (int j = 0; j < i; j++)
        {
            from = topologicalSort[j];
            if (edgeToTopo[from][to] != 0) //表示有路
            {
                if (maxPath[from] + edgeToTopo[from][to] > maxPath[to])
                {
                    maxPath[to] = maxPath[from] + edgeToTopo[from][to];
                    if (dad[from] == -1) //如果是路线中的第二个节点
                    {
                        ancestor[to] = from;
                    }
                    else
                    {
                        ancestor[to] = ancestor[from];
                    } 
                    dad[to] = 1;
                }
            }
        }
    }

    //找到maxPath中最大值对应的路径中的最小值
    int max = 0;
    int minAncestor = n;
    for (int i = 0; i < n; i++)
    {
        if (maxPath[i] > max)
        {
            max = maxPath[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (maxPath[i] == max && ancestor[i] < minAncestor)
        {
            minAncestor = ancestor[i];
        }
    }

    int start = minAncestor;
    int end;
    for (int i = 0; i < n; i++)
    {
        if (maxPath[i] == max && ancestor[i] == minAncestor)
        {
            end = i;
            break;
        }
    }
    printf("%d ", start + 1);
    while (start != end)
    {
        if (next[start][end] == end)
        {
            printf("%d\n", next[start][end] + 1);
        }
        else
        {
            printf("%d ", next[start][end] + 1);
        }
        start = next[start][end];
    }
    return 0;
}
