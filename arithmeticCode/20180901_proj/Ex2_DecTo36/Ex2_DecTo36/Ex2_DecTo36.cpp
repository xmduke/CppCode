// Ex2_DecTo36.cpp : �������̨Ӧ�ó������ڵ㡣
//2.���һ��������ʮ���Ƶ�������ת��Ϊ36�����ַ���
// ��0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ��
//  1 = "0001"; 10 = "000A"; 20 = "000K"; 35 = "000Z"; 36 = "0010";

#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>

int count = 0;
char decNumToc36(unsigned int DecNum)
{
	char c36[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	return c36[DecNum];
}

char* DecTo36(unsigned int DecNum)
{
	//˼·��fzy(36) = f * 36 ^ 2 + z * 36 ^ 1 + y * 36 ^ 0 = 20734(D)
	//     234(D) = 2 * 10 ^ 2 + 3 * 10 ^ 1 + 4 * 10 ^ 0
	//     ���ö̳���ѭ������36������Ϊ36���Ƶ�ֵ�����ϵ���Ϊ��λ����λ
	//     ÿ�ε�����10 =< x <= 35�����ַ�����ת����ͨ���ַ������ձ�����
	int NumModule = 0;
	char *numC36 = (char*)malloc(4 * sizeof(char));
	memset(numC36, 0, sizeof(numC36));
	numC36++;
	while (DecNum > 0)
	{
		NumModule = DecNum % 36;
		DecNum = DecNum / 36;
		*numC36 = decNumToc36(NumModule);
		numC36++;
		count++;
	}
	return numC36;
}

void Reverse36(char* numC36)
{
	for (int i = 1; i <= count; i++)
	{
		printf("%c", *(numC36 - i));
	}
	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int testNum = 20734;
	Reverse36(DecTo36(testNum));
	return 0;
}

