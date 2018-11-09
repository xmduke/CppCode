// Ex_FindPrime.cpp : �������̨Ӧ�ó������ڵ㡣
//�ҳ�40000���ڵ�������ɸ����

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
	//0 �� 1 �Ȳ�������Ҳ���Ǻ�������2��ʼ
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
	printf("40000����һ��%d������", FindPrime());
	return 0;
}

