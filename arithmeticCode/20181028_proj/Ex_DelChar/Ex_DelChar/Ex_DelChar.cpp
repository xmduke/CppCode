// Ex_DelChar.cpp : 定义控制台应用程序的入口点。
//从一个特定字符串中删除一个特定字符
//void delChar(char *str, char del)
//void delChars(char *str, char dels[], size_t len)
//Hello world o -> Hell wrld
//Hello world ol -> He wrd

#include "stdafx.h"


char *delChar(char *str, char *outstr, char del)
{
	char *pread = str;
	int i = 0;
	while (*pread != NULL)
	{
		if (*pread != del)
		{
			outstr[i] = *pread;
			i++;
		}
		pread++;
	}
	return outstr;
}

char* delChars(char *str, char* outstr, char dels[], size_t len)
{
	char *pread = str;
	int i = 0;
	
	while (*pread != NULL)
	{
		int flag = len;
		int count = 0;
		while(count < len)
		{
			if (*pread != dels[count])
			{
				flag--;
			}
			count++;
		}
		if (flag == 0)
		{
			outstr[i] = *pread;
			i++;
		}
		
		pread++;
		
	}
	return outstr;

}

int _tmain(int argc, _TCHAR* argv[])
{
	char *str = "Hello world";
	char pwrite[12] = { 0 };
	str = delChar(str, pwrite, 'o');
	printf("%s\n", str);
	char *str2 = "Hello world";
	char dels[] = {"ol"};
	char pwrite2[12] = { 0 };
	str2 = delChars(str2, pwrite2, dels, 2);
	printf("%s\n", str2);
	return 0;
}

