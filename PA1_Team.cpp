#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<string.h>
using namespace std;

//归并排序
void Merge(int arr[], int reg[], int start, int end)
{
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;

	//分成两部分
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	//然后合并
	Merge(arr, reg, start1, end1);
	Merge(arr, reg, start2, end2);

	int k = start;
	//两个序列一一比较,哪的序列的元素小就放进reg序列里面,然后位置+1再与另一个序列原来位置的元素比较
	//如此反复,可以把两个有序的序列合并成一个有序的序列
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];

	//然后这里是分情况,如果arr2序列的已经全部都放进reg序列了然后跳出了循环
	//那就表示arr序列还有更大的元素(一个或多个)没有放进reg序列,所以这一步就是接着放
	while (start1 <= end1)
		reg[k++] = arr[start1++];

	//这一步和上面一样
	while (start2 <= end2)
		reg[k++] = arr[start2++];
	//把已经有序的reg序列放回arr序列中
	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}

void MergeSort(int arr[], int len)
{
	//创建一个同样长度的序列,用于临时存放
	int *reg = new int[len];
	Merge(arr, reg, 0, len - 1);
	delete[] reg;
}

int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	int n, k;
	char result[3] = { 'A','B','C' };
	scanf("%d",&n);
	int*A = new int[n];
	int*B = new int[n];
	int*C = new int[n];
	char*isValid = new char[n];
	memset(isValid, '1', n);
	for (int i = 0; i<n; i++)
	{
		scanf("%d", A + i);
	}
	for (int i = 0; i<n; i++)
	{
		scanf("%d", B + i);
	}
	for (int i = 0; i<n; i++)
	{
		scanf("%d", C + i);
	}
	scanf("%d", &k);
	for (int i = 0; i<n; i++)
	{
		switch (i % 3)
		{
		case 0:
			while (isValid[*A- 1] != '1')
			{
				A++;
			}
			if (*A == k)
			{
				cout << result[i % 3];
				//system("pause");
				return 0;
			}
			else
			{
				isValid[*A - 1] = '0';
				A++;
			}
			break;
		case 1:
			while (isValid[*B - 1] != '1')
			{
				B++;
			}
			if (*B == k)
			{
				cout << result[i % 3];
				//system("pause");
				return 0;
			}
			else
			{
				isValid[*B - 1] = '0';
				B++;
			}
			break;
		case 2:
			while (isValid[*C - 1] != '1')
			{
				C++;
			}
			if (*C == k)
			{
				cout << result[i % 3];
				//system("pause");
				return 0;
			}
			else
			{
				isValid[*C - 1] = '0';
				C++;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}



