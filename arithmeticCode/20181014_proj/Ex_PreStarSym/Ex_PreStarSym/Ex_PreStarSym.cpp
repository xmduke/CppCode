// Ex_PreStarSym.cpp : �������̨Ӧ�ó������ڵ㡣
//��һ���ַ��������е�*��ǰ he*llo wor*l*d  ->  ***hello world

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
	//�����ָ���дָ��
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
	//��¼readָ��λ��
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

