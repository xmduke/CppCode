#pragma once
#include <stdio.h>
//��һ���ַ����е�����*��ǰ����hello wor*l*d-- > **hello world

int move_stars_to_front(char *str)
{
	if (NULL == str)
	{
		return 0;
	}

	//i��Ϊдָ�룬jΪ��ָ��
	//j��ʼ��������ɨ���ַ���������*���ԣ�������*ֱ�Ӵ��ݸ�
	//i���ڵ��ڴ棬i�����ƶ�һ��
	int i = strlen(str) - 1;
	for (int j = strlen(str) - 1; j >= 0; j--)
	{
		if (str[j] != '*')
		{
			str[i] = str[j];
			i--;
		}
	}
	for (; i >= 0; i--)
	{
		str[i] = '*';
	}
	return 1;
}

void FindRepNum()
{
	//int a��65536�� a[v[i]]++
	int array[] = { 19, 28, 37, 46, 55, 44, 33, 22, 10, 6, 7, 8, 9, 0, 9, 8, 7, 6, 19, 20 };
	int arraytmp[100] = { 0 };
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