#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
const int MAX = 18000000;
int len, Len[2 * MAX];
char str[2 * MAX], T[2 * MAX];

void init()
{
    int i;
    T[0] = '@';
    T[1] = '#';
    for (i = 0; i < len; i++)
    {
        T[2 * i + 2] = str[i];
        T[2 * i + 3] = '#';
    }
    T[2 * len + 2] = '\0';
    return;
}

void Manacher()
{
    int i, j, id, maxid = 0, ans = 1;
    len = 2 * len + 2;
    for (i = 0; i < len; i++)
    {
        if (maxid > i)
        {
            Len[i] = Len[2 * id - i] < maxid - i ? Len[2 * id - i] : maxid - i;
        }
        else
        {
            Len[i] = 1;
        }
        while (T[i + Len[i]] == T[i - Len[i]])
            Len[i]++;
        if (Len[i] + i > maxid)
        {
            maxid = Len[i] + i;
            id = i;
        }
    }
}

int main()
{

    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
    
    scanf("%s", &str);
    len = strlen(str);
    init();
    Manacher();
    long long int sum = 0;
    for (int i = 1; i < len; i++)
    {
        sum += ceil(float(Len[i] - 1) / float(2));
    }
    printf("%lld\n", sum);
    return 0;
}