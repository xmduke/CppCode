// Ex_Strstr.cpp : �������̨Ӧ�ó������ڵ㡣
//Ex �����Ӵ�
//˼·�����Ӵ���ÿ����ĸ��ԭ�����бȽ�
#include "stdafx.h"
#include <stdlib.h>


char* Strstr(char *Src, char *subStr)
{
	char tmp[5] = {0};
	int count = 0;
	char *subStrtmp = subStr;
	while (*Src != NULL)
	{
		while (*subStrtmp != NULL)
		{
			if (*Src == *subStrtmp)
			{
				//�ִ��ַ�����򱣴�tmp�У��ִ�ָ��ڶ����ַ���ԭ��ָ����һ���ַ�
				tmp[count] = *Src;
				Src++;
				count++;
				subStrtmp++;
			}
			else
			{
				//�ִ��ַ��Ƚϲ�����Src++������
				Src++;
				subStrtmp = subStr;
				count = 0;
				break;
			}
		}
		if (*subStrtmp == NULL)
		{
			//�ҵ���
			return subStr;
		}
	}
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char *Src = "Hello world";
	char *subStr = "orl";
	char *subStr2 = "xyz";
	char *res = Strstr(Src, subStr);
	printf("%s\n", res);
	char *res2 = Strstr(Src, subStr2);
	printf("%s\n", res2);
	return 0;
}

