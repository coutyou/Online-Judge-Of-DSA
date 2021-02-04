#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
class BitMap {
public:
	BitMap() {
		bitmap = NULL;
		size = 0;
	}
	BitMap(int size) { // contractor, init the bitmap
		bitmap = NULL;
		bitmap = new char[size];
		memset(bitmap, 0x0, size * sizeof(char));
		this->size = size;
	}
	/*
	* set the index bit to 1;
	*/
	int bitmapSet(int index) {
		int addr = index / 8;
		int addroffset = index % 8;
		unsigned char temp = 0x1 << addroffset;
		if (addr > (size + 1)) {
			return 0;
		}
		else {
			bitmap[addr] |= temp;
			return 1;
		}
	}

	/*
	* return if the index in bitmap is 1;
	*/
	int bitmapGet(int index) {
		int addr = index / 8;
		int addroffset = index % 8;
		unsigned char temp = 0x1 << addroffset;
		if (addr > (size + 1)) {
			return 0;
		}
		else {
			return (bitmap[addr] & temp) > 0 ? 1 : 0;
		}
	}

	/*
	* del the index from 1 to 0
	*/
	int bitmapDel(int index) {
		if (bitmapGet(index) == 0) {
			return 0;
		}
		int addr = index / 8;
		int addroffset = index % 8;
		unsigned char temp = 0x1 << addroffset;
		if (addr > (size + 1)) {
			return 0;
		}
		else {
			bitmap[addr] ^= temp;
			return 1;
		}
	}
	int getSize()
	{
		return size;
	}
	char *bitmap;
private:
	int size;
};
int main()
{
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	int n, m;
	scanf("%d %d", &n, &m);
	BitMap bitmap = BitMap(n / 8 + 1);
	int *code = new int[n + 1];
	int *isOnline = new int[m];
	char opt;
	int a, c;
	long long int answer = 0;
	int count = 0;
	for (int i = 0; i < m; i++)
	{
		while (scanf("%c", &opt) && opt != 'I' && opt != 'O'&& opt != 'C'&& opt != 'N'&& opt != 'Q');
		switch (opt)
		{
		case 'I':
			scanf("%d %d", &a, &c);
			if (bitmap.bitmapGet(a) != 1)
			{
				bitmap.bitmapSet(a);
				isOnline[count] = a;
				count++;
			}
			code[a] = c;
			break;
		case 'O':
			scanf("%d", &a);
			if (bitmap.bitmapGet(a) != 0)
			{
				bitmap.bitmapDel(a);
				for (int k = 0; k < count; k++)
				{
					if (isOnline[k] == a)
					{
						isOnline[k] = isOnline[count - 1];
						break;
					}
				}
				count--;
				code[a] = 0;
			}
			break;
		case 'C':
			//memset(bitmap.bitmap, 0x0, bitmap.getSize() * sizeof(char));
			for (int k = 0; k < count; k++)
			{
				bitmap.bitmapDel(isOnline[k]);
			}
			count = 0;
			break;
		case 'N':
			answer += count;
			break;
		case 'Q':
			scanf("%d", &a);
			if (bitmap.bitmapGet(a) != 1)
			{
				answer += -1;
			}
			else
			{
				answer += code[a];
			}
			break;
		default:
			break;
		}
	}
	cout << answer;
	//system("pause");
	return 0;
}