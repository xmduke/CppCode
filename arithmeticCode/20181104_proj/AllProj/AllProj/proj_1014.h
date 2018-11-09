#pragma once
#include <stdio.h>
//将一个字符串中的所有*提前：如hello wor*l*d-- > **hello world

int move_stars_to_front(char *str)
{
	if (NULL == str)
	{
		return 0;
	}

	//i即为写指针，j为读指针
	//j开始从右往左扫描字符串，遇到*忽略，遇到非*直接传递给
	//i所在的内存，i往左移动一步
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
	//int a【65536】 a[v[i]]++
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