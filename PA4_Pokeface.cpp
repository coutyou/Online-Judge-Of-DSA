#include <iostream>
#include <string.h>
using namespace std;

const int N = 500001;
int _tree[N];
int _data[N];
int n, m;

int lowbit(int t) //计算一维树状数组下标为t的项展开的项数
{
    return t & (-t);
}

int sum(int x) //计算(0,x)的和
{
    int result = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        result += _tree[i];
    }
    return result;
}

void change(int x, int target)
{
    //计算差值
    int delta = target - _data[x];
    //修改数据数组的值s
    _data[x] += delta;
    //修改树状数组的值
    for (int i = x; i < n + 1; i += lowbit(i))
    {
        _tree[i] += delta;
    }
}

void init()
{
    //初始化为0
    for (int i = 1; i <= n; i++)
    {
        _data[i] = 0;
        _tree[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        change(i, 1);
    }
}

int main()
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    scanf("%d %d", &n, &m);
    init();

    char opt;
    int from, to, pos;
    for (int i = 0; i < m; i++)
    {
        getchar();
        scanf("%c", &opt);
        if (opt == 'H')
        {
            scanf("%d", &pos);
            if (_data[pos] == 0)
            {
                change(pos, 1);
            }
            else
            {
                change(pos, 0);
            }
        }
        else
        {
            scanf("%d %d", &from, &to);
            printf("%d\n", sum(to) - sum(from - 1));
        }
    }

    return 0;
}