// Ex_FindRepNum.cpp : 定义控制台应用程序的入口点。
//从一个正整数组中找出重复的数，假设数组的值的范围都小于65536

#include "stdafx.h"

void FindRepNum()
{
	//int a【65536】 a[v[i]]++
	int array[] = {19,28,37,46,55,44,33,22,10,6,7,8,9,0,9,8,7,6,19,20};
	int arraytmp[100] = {0};
	int i = 0;
	while (i < 100)
	{
		if (i >= 20)
		{
			break;
		}
		arraytmp[array[i]] = arraytmp[array[i]]++;
		i++;
	}
	i = 0;
	while (i < 100)
	{
		if (arraytmp[i] > 1)
		{
			printf("%d, ", i);
		}
		i++;
	}
	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	FindRepNum();
	return 0;
}

