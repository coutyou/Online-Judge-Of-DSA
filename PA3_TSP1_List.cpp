#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct Node
{
    int data;
    Node *next;
    int price;
}Node;

class List
{
public:
    Node *head;
    Node *p;
    Node *q;
    int length;

    List()
    {
        head = NULL;
        length = 0;
        p = NULL;
    }
    void add(int t, int price)
    {
        if (head == NULL)
        {
            q = new Node;
            q->data = t;
            q->next = NULL;
            q->price = price;
            length++;
            head = q;
            p = head;
        }
        else
        {
            q = new Node;
            q->data = t;
            q->next = NULL;
            q->price = price;
            length++;
            p->next = q;
            p = q;
        }
    }

    void remove(int n)
    {
        if (n >= length)
        {
            return;
        }
        length--;

        //删除头节点
        if (n == 0)
        {
            q = head;
            head = head->next;
            delete (q);
        }
        else
        {
            q = head;
            for (int i = 0; i < n - 1; i++)
            {
                q = q->next;
            }
            Node *t = q->next;
            q->next = q->next->next;
            delete (t);
        }

        //
        p = head;
        if (p != NULL)
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
        }
    }

    int getSize()
    {
        return length;
    }

    int get(int n)
    {
        q = head;
        for (int i = 0; i < n; i++)
        {
            q = q->next;
        }
        return q->data;
    }

    int getPrice(int t)
    {
        if (length != 0)
        {
            q = head;
            for (int i = 0; i < length - 1; i++)
            {
                if (q->data == t)
                {
                    return q->price;
                }
                q = q->next;
            }
            if (q->data == t)
            {
                return q->price;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }

    void changePrice(int to, int newPrice)
    {
        q = head;
        for (int i = 0; i < length - 1; i++)
        {
            if (q->data == to)
            {
                q->price = newPrice;
                return;
            }
            q = q->next;
        }
        if (q->data == to)
        {
            q->price = newPrice;
        }
    }
};

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

    List *edge = new List[n];

    int from, to, price;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &from, &to, &price);
        if (edge[from - 1].getPrice(to - 1) == 0)
        {
            edge[from - 1].add(to - 1, price);
            inDegree[to - 1]++;
        }
        else if (edge[from - 1].getPrice(to - 1) < price)
        {
            edge[from - 1].changePrice(to - 1, price);
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
                    if (edge[j].getPrice(k) != 0)
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
            if (edge[from].getPrice(to) != 0) //表示有路
            {
                if (maxPath[from] + edge[from].getPrice(to) > maxPath[to])
                {
                    maxPath[to] = maxPath[from] + edge[from].getPrice(to);
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
    printf("%d", max);
    return 0;
}
