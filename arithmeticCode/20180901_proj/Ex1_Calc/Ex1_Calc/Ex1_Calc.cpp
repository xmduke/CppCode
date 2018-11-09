// Ex1_Calc.cpp : 定义控制台应用程序的入口点。
//1.计算一个整数的二进制中有多少个1


#include "stdafx.h"

int BinCalc(int DecNum)
{
	//思路：对一个整数循环求余，直到小于2为止，记录余数为1的次数
	int iMem = 0;
	int count = 0;
	while (DecNum > 0)
	{
		iMem = DecNum % 2;
		DecNum = (DecNum / 2);
		if (iMem == 1)
		{
			count++;
		}
	}
	return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numTest = 989;
	numTest = BinCalc(numTest);
	printf("%d\n", numTest);
	return 0;
}

