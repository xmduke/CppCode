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

	/* pSrc��pDst����ͬһ���ڴ����� */
	if ((pSrc<pDst) && ((char*)pSrc + size > pDst))
	{
		char *pstrSrc = (char *)pSrc + size - 1;
		char *pstrDst = (char *)pDst + size - 1;
		/*��β�����򿽱�*/
		while (size--)//    
			*pstrDst-- = *pstrSrc--;
	}
	else
	{
		char *pstrSrc = (char *)pSrc;
		char *pstrDst = (char *)pDst;
		/* ����ʼ�����򿽱� */
		//while(--size)�ǲ��еġ��ȼ�1�����жϡ�sizeΪ1��ʱ����˳��˻�����һ��    
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
#define MAX ((int)0x7FFFFFFF)//����λΪ0������λȫΪ1
#define MIN ((int)0x80000000)//����λΪ1������λȫΪ0
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
		//������С����Сֵ ||�������������ֵ
		if ((negative && result > MAX + 1) || (!negative && result > MAX))
		{
			//������
			return 0;
		}

		str++;
	}
	//��������
	if (negative)
		result *= -1;
	return (int)result;
}