#pragma once
#include <stdio.h>
#define MAXN 40001
int sift_prime(void)
{
	int i, j;
	int total = 0;
	int prime[MAXN];

	for (i = 2; i < MAXN; i++)
		prime[i] = 1;
	for (i = 2; i < MAXN; i++)
	{
		if (prime[i] == 1)
		{
			for (j = 2; i * j < MAXN; j++)//2*7,7*2?
				prime[i * j] = 0;
		}
	}
	for (i = 0; i < MAXN; i++)
	{
		if (prime[i] == 1)
		{
			printf("%d ", i);
			total++;

		}
	}
	return total;
}


//一个纯数字的字符串，输出所有标准的IP，例如“11022345”
// 110.2.234.5 1.102.234.5 1.102.23.45 110.2.23.45
int n_atoi(const char *str, int len)
{
	int value = 0;
	for (int i = 0; i < len; i++)
	{
		value = value * 10 + (str[i] - '0');//'9'-'0'=9
	}
	return value;
}

void My_Print(const char *begin, const char *end)
{
	char *p = (char *)begin;
	while (p <= end)
	{
		printf("%c", *p);
		p++;
	}
}



void enumerate_ips(const char *ip)
{
	if (ip == NULL)
	{
		return;
	}

	int len = strlen(ip);
	if (len < 4 || len>12)
		return;

	char *p1 = (char *)ip;


	int loop_len1 = 3;

	while (loop_len1 > 0)
	{
		int loop_len2 = 3;
		char *p2 = p1 + 1;
		if (n_atoi(ip, p1 - ip + 1) > 255)//ip头到p1之间的数字
		{
			p1++;
			loop_len1--;
			continue;
		}
		while (loop_len2 > 0)
		{
			int loop_len3 = 3;
			char *p3 = p2 + 1;
			if (n_atoi(p1 + 1, p2 - p1) > 255)
			{
				p2++;
				loop_len2--;
				continue;//p1+1到p2之间的数字
			}
			while (loop_len3 > 0 && *(p3 + 1))
			{

				if (n_atoi(p2 + 1, p3 - p2) > 255 || n_atoi(p3 + 1, ip + strlen(ip) - 1 - p3) > 255)//p2+1到p3之间的数字,p3+1到末尾之间的数字
				{
					p3++;
					loop_len3--;
					continue;
				}

				My_Print(ip, p1);
				printf("%c", '.');
				My_Print(p1 + 1, p2);
				printf("%c", '.');
				My_Print(p2 + 1, p3);
				printf("%c", '.');
				My_Print(p3 + 1, ip + strlen(ip) - 1);
				printf("\n");
				p3++;
				loop_len3--;
			}
			p2++;
			loop_len2--;
		}

		p1++;
		loop_len1--;
	}

}