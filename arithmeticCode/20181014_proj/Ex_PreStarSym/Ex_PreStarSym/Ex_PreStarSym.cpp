// Ex_PreStarSym.cpp : 定义控制台应用程序的入口点。
//将一个字符串中所有的*提前 he*llo wor*l*d  ->  ***hello world

#include "stdafx.h"

int getLen(char *pStarSym)
{
	int count = 0;
	while (*pStarSym != '\0')
	{
		count++;
		pStarSym++;
	}
	return count;
}

char* PreStarSym(char *pStarSym)
{
	//定义读指针和写指针
	char *read;
	char *write;
	int len = getLen(pStarSym);
	read = write = pStarSym + len;

	int i = len;
	while (len)
	{
		len--;
		read = pStarSym + len;
		if (*read != '*')
		{
			write--;
			*write = *read;
			
			//write = pStarSym + len - 1;
		}
	}
	//记录read指针位置
	pStarSym = read;
	while (read != write)
	{
		*read = '*';
		read++;
	}

	//*(pStarSym + getLen(pStarSym) + 1) = '\0';
	return pStarSym;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char SS[] = { "he*llo wor*l*d" };
	printf("%s\n", PreStarSym(SS));
	return 0;
}

