// Ex_itoaAndatoi.cpp : 定义控制台应用程序的入口点。
//Ex. 实现void itoa(int i, char *buf) / int atoi(char *str)

#include "stdafx.h"

//思路，按正数负数分类，进行取模转为字符
char* itoa(int i, char *buf)
{
	char tmp[12] = {0};
	char *buftmp = buf;
	int count = 0;
	if (i >= 0x0 && i <= 0x7fffffff )//2147483647
	{
		while (i != 0)
		{
			tmp[count] = (i % 10) + 0x30;
			i = i / 10;
			count++;
		}
		while (count--)
		{
			*buf = tmp[count];
			buf++;
			
		}
		buf = buftmp;
	}
	else if (i >= 0x80000000 && i <= 0xffffffff)//-2147483648 
	{
		
		if (i == 0x80000000)
		{
			char *tmp = "-2147483648";
			buf = tmp;
		}
		else
		{
			int abs = ~i + 1;
			while (abs != 0)
			{
				tmp[count] = (abs % 10) + 0x30;
				abs = abs / 10;
				count++;
			}
			tmp[count] = '-';
			count++;
			while (count--)
			{
				*buf = tmp[count];
				buf++;
			}
			
			buf = buftmp;
		}
	}
	else
	{
		//溢出
		return NULL;
	}
	return buf;
}

int _10n(int i)
{
	int tmp = 1;
	i--;
	while (i)
	{
		tmp = tmp * 10;
		i--;
	}
	return tmp;
}

//
int atoi(char *str)
{
	int nRes = 0;
	int tmp[10] = { '\0' };
	int tmp2[11] = { '\0' };
	int i = 0;
	if (*str != '-')
	{
		//正数
		while (*str != '\0')
		{
			tmp[i] = *str - 0x30;
			str++;
			i++;
			
		}
		if (i >= 11)
		{
			//溢出
			return 0;
		}
		int j = 0;
		int n = 0;
		while (i)
		{
			n = _10n(i);
			nRes = nRes + tmp[j] * n;
			j++;
			i--;
		}
	}
	else
	{
		////负数
		str++;
		
		while (*str != '\0')
		{
			tmp2[i] = *str - 0x30;
			str++;
			i++;

		}
		if (i >= 11)
		{
			//字符串越界溢出
			return 0;
		}
		int j = 0;
		int n = 0;
		while (i)
		{
			n = _10n(i);
			nRes = nRes + tmp2[j] * n;
			j++;
			i--;
		}
		nRes = ~(nRes - 1);
	}
	
	return nRes;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[12] = { 0 };
	char *res;
	res = itoa(0x80000000, buf);
	printf("%s\n", res);
	char buf2[12] = { 0 };
	char *res1;
	res1 = itoa(0x71234567, buf2);
	printf("%s\n", res1);
	char buf3[12] = { 0 };
	char *res2;
	res2 = itoa(0x81234567, buf3);
	printf("%s\n", res2);

	printf("\n");
	
	printf("%d\n", atoi("1234567890"));
	printf("%d\n", atoi("2147483647"));
	printf("%d\n", atoi("-2128394905"));
	printf("%d\n", atoi("-2147483648"));

	return 0;
}

