// Ex1_Calc.cpp : �������̨Ӧ�ó������ڵ㡣
//1.����һ�������Ķ��������ж��ٸ�1


#include "stdafx.h"

int BinCalc(int DecNum)
{
	//˼·����һ������ѭ�����ֱ࣬��С��2Ϊֹ����¼����Ϊ1�Ĵ���
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

