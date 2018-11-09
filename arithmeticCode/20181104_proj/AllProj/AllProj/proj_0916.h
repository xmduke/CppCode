#pragma once
#include <stdio.h>

void _memmove(void *pDst, const void *pSrc, size_t size)
{
	if (pDst == NULL)
	{
		return;
	}

	if (pSrc == NULL)
	{
		return;
	}

	/* pSrc与pDst共享同一块内存区域 */
	if ((pSrc<pDst) && ((char*)pSrc + size > pDst))
	{
		char *pstrSrc = (char *)pSrc + size - 1;
		char *pstrDst = (char *)pDst + size - 1;
		/*从尾部逆向拷贝*/
		while (size--)//    
			*pstrDst-- = *pstrSrc--;
	}
	else
	{
		char *pstrSrc = (char *)pSrc;
		char *pstrDst = (char *)pDst;
		/* 从起始部正向拷贝 */
		//while(--size)是不行的。先减1，再判断。size为1的时候就退出了会少算一个    
		while (size--)
			*pstrDst++ = *pstrSrc++;
	}
}

//int:[-2147483648,2147483647]
int my_itoa(int val, char* buf)
{
	char *p2;
	unsigned int a;        //every digit
	int len;
	char *p1;            //start of the digit char
	char temp;
	unsigned int u;

	if (buf == NULL)
	{
		return 0;
	}

	p2 = buf;

	if (val < 0)
	{
		if (val == 0x80000000)
		{
			char *num = "-2147483648";
			for (int i = 0; i < 12; i++)
			{
				buf[i] = *num++;
			}
			return 11;
		}
		*p2++ = '-';
		val = 0 - val;
	}
	u = (unsigned int)val;
	p1 = p2;
	do
	{
		a = u % 10;
		u /= 10;

		*p2++ = a + '0';

	} while (u > 0);

	len = (int)(p2 - buf);
	*p2-- = 0;
	//swap
	do
	{
		temp = *p2;
		*p2 = *p1;
		*p1 = temp;
		--p2;
		++p1;

	} while (p1 < p2);

	return len;
}

//atoi
#define MAX ((int)0x7FFFFFFF)//符号位为0，其它位全为1
#define MIN ((int)0x80000000)//符号位为1，其它位全为0
//int:[-2147483648,2147483647]
int my_atoi(const char * str)
{
	bool negative = false;
	unsigned long result = 0;

	if (str == NULL)
		return 0;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		negative = true;
		str++;
	}
	else if (*str == '+')
		str++;
	if (*str<'0' || *str>'9')
		return 0;

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		//负数：小于最小值 ||正数：大于最大值
		if ((negative && result > MAX + 1) || (!negative && result > MAX))
		{
			//溢出检测
			return 0;
		}

		str++;
	}
	//负数处理
	if (negative)
		result *= -1;
	return (int)result;
}