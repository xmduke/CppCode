// Ex_FindPrime.cpp : 定义控制台应用程序的入口点。
//找出40000以内的素数（筛法）

#include "stdafx.h"
bool is_prime(int num)
{
	if (num <= 3)
	{
		return num > 1;
	}
	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	return true;
}
int FindPrime()
{
	int array[40000] = { 0 };
	//0 和 1 既不是素数也不是合数，从2开始
	for (int i = 2; i < 40000; i++)
	{
		if (is_prime(i))
		{
			array[i] = 1;
		}
		else
		{
			array[i] = 0;
		}
	}
	int count = 0;
	for (int i = 0; i < 40000; i++)
	{
		if (array[i] == 1)
		{
			printf("%d, ", i);
			count++;
			if (count % 10 == 0)
			{
				printf("\n");
			}
		}
	}
	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("40000以内一共%d个素数", FindPrime());
	return 0;
}

