// Ex2_DecTo36.cpp : 定义控制台应用程序的入口点。
//2.设计一个函数把十进制的正整数转换为36进制字符串
// “0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ”
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
	//思路：fzy(36) = f * 36 ^ 2 + z * 36 ^ 1 + y * 36 ^ 0 = 20734(D)
	//     234(D) = 2 * 10 ^ 2 + 3 * 10 ^ 1 + 4 * 10 ^ 0
	//     采用短除法循环除以36，余数为36进制的值，从上到下为低位到高位
	//     每次的余数10 =< x <= 35进行字符串的转换（通过字符串对照表函数）
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

