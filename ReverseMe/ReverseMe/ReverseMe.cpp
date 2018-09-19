// ReverseMe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char szName[] = {"y0nngeek201508261314"};
	byte pass[] = { 0x79, 0x30, 0x6e, 0x6e, 0x67, 0x65, 0x65, 0x6B, 0x32, 0x30, 0x31, 0x35, 0x30, 0x38, 0x32, 0x36, 0x31, 0x33, 0x31, 0x34 };


	
	byte *ch1 = (byte *)pass;
	do
	{
		//*ch1 = (*ch1 - 0x78) ^ 0x22;
		*ch1 = (*ch1 ^ 0x22) + 0x78;
		++ch1;
	} while (ch1 != (byte *)pass + sizeof(pass));

	printf("密码为：");
	for (int i = 0; i < sizeof(pass); i++)
	{
		printf("%x", pass[i]);
	}
	
	return 0;
}

