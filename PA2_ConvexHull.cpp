#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct Point
{
	int x;
	int y;
} Point;

long long int isLeft(Point topPoint, Point underTopPoint, Point newPoint) //判断新的点是否在原直线的左边
{
	return ((long long)topPoint.x - (long long)underTopPoint.x) * ((long long)newPoint.y - (long long)underTopPoint.y) - ((long long)topPoint.y - (long long)underTopPoint.y) * ((long long)newPoint.x - (long long)underTopPoint.x);
}

int Partition(Point *a, int left, int right)
{
	int flag = a[left].y;
	while (left < right)
	{
		while (a[right].y >= flag && left < right)
			right--;
		if (left < right)
		{
			a[left] = a[right];
			left++;
		}

		while (a[left].y < flag && left < right)
			left++;
		if (left < right)
		{
			a[right] = a[left];
			right--;
		}
	}
	a[left].y = flag;
	return left;
}

void QuicksortSection(Point *a, int left, int right)
{
	if (left < right)
	{
		int i = Partition(a, left, right);
		QuicksortSection(a, left, i - 1);
		QuicksortSection(a, i + 1, right);
	}
}

void QuickSort(Point *a, int n)
{
	int left = 0;
	int right = n - 1;
	QuicksortSection(a, left, right);
}

int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	//输入
	int n;
	//scanf("%d", &n);
	fread(&n, sizeof(int), 1, stdin);
	Point *points = new Point[n];
	for (int i = 0; i < n; i++)
	{
		fread(&(points[i].x), sizeof(int), 1, stdin);
		fread(&(points[i].y), sizeof(int), 1, stdin);
	}
	// for (int i = 0; i < n; i++)
	// {
	// 	scanf("%d", &(points[i].x));
	// 	scanf("%d", &(points[i].y));
	// }
	// 排序
	int lo = 0,hi = 0;
	while(lo < n)
	{
		while(points[hi].x == points[lo].x)
		{
			hi++;
		}
		if(hi - lo > 1)
		{
			QuickSort(&points[lo], hi - lo);
		}
		lo = hi;
	}
	// 生成左右链
	Point *result = new Point[n + 1];
	int len = 0;
	for (int i = 0; i < n; i++)
	{
		// 反向扫描右链
		while (len >= 2 && isLeft(result[len - 1], result[len - 2], points[i]) <= 0)
		{
			len--;
		}
		result[len++] = points[i];
	}
	int lenOfRight = len;
	for (int i = n - 2; i >= 0; i--)
	{
		// 扫描左链
		// "len>tmp" 用于保证右链已生成的点不会被左链扫描所影响
		while (isLeft(result[len - 1], result[len - 2], points[i]) <= 0 && len > lenOfRight)
		{
			len--;
		}
		result[len++] = points[i];
	}
	if (result[len - 1].x == result[0].x && result[len - 1].y == result[0].y)
	{
		len--;
	}
	//寻找第一个输出元素
	Point first = result[0];
	int indexFirst = 0;
	for (int i = 1; i < lenOfRight; i++)
	{
		if ((result[i].y < first.y) || (result[i].y == first.y && result[i].x < first.x))
		{
			first = result[i];
			indexFirst = i;
		}
	}
	//输出元素
	for (int i = indexFirst; i < len; i++)
	{
		printf("%d %d\n", result[i].x, result[i].y);
	}
	for (int i = 0; i < indexFirst; i++)
	{
		printf("%d %d\n", result[i].x, result[i].y);
	}
	return 0;
}
