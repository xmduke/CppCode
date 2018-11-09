// Ex3_LittleOrBig.cpp : 定义控制台应用程序的入口点。
//3.判断一个平台是低位优先还是高位优先

#include "stdafx.h"

void LittleOrBig()
{
	int a = 0x01;
	char *p = (char*)&a;
	if (0 == *p)
	{
		printf("高位优先\n");
	}
	else
	{
		printf("低位优先\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//思路：通过定义一个4字节的数据，将其中2个字节复制出来，进行对比
	//     如果相等则为低位优先，如果不等则为高位优先
	//因此定义int类型
	/*int a = 0xFF;
	short b;
	memcpy(&b, &a, 2);
	if (a == b)
	{
		printf("低位优先\n");
	}
	else
	{
		printf("高位优先");
	}*/
	LittleOrBig();
	return 0;
}

