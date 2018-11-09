#pragma once
#include <stdio.h>
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
		while (count < len)
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
