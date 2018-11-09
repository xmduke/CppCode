// Ex_MemMove.cpp : 定义控制台应用程序的入口点。
//Ex.实现void *memmove(void *pDst, const void *pSrc, size_t len) 考虑重叠

#include "stdafx.h"

void *MemMove(char *pDst, const char *pSrc, size_t len)
{
	//思路：地址重叠校验，pDst + len < pSrc || pDst > pSrc
	if (pDst == NULL || pSrc == NULL)
	{
		return NULL;
	}
	if ((pDst + len) < pSrc || pDst > pSrc)
	{
		//地址未重叠，拷贝内容
		while (len)
		{
			*pDst = *pSrc;
			*pSrc++;
			*pDst++;
			len--;
		}
	}
	else
	{
		//地址重叠，反向拷贝
		while (len)
		{
			*pDst = *pSrc;
			*pDst--;
			*pSrc++;
			len--;
		}
		
	}
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char pDir[12] = { 0 };
	MemMove(pDir, "hello world", sizeof("hello world"));
	printf("%s\n", pDir);
	return 0;
}

