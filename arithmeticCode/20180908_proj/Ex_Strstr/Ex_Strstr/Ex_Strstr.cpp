// Ex_Strstr.cpp : 定义控制台应用程序的入口点。
//Ex 查找子串
//思路：将子串的每个字母与原串进行比较
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
				//字串字符相等则保存tmp中，字串指向第二个字符，原串指向下一个字符
				tmp[count] = *Src;
				Src++;
				count++;
				subStrtmp++;
			}
			else
			{
				//字串字符比较不等则Src++并跳出
				Src++;
				subStrtmp = subStr;
				count = 0;
				break;
			}
		}
		if (*subStrtmp == NULL)
		{
			//找到了
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

