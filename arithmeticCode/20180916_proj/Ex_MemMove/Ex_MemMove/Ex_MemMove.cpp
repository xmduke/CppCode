// Ex_MemMove.cpp : �������̨Ӧ�ó������ڵ㡣
//Ex.ʵ��void *memmove(void *pDst, const void *pSrc, size_t len) �����ص�

#include "stdafx.h"

void *MemMove(char *pDst, const char *pSrc, size_t len)
{
	//˼·����ַ�ص�У�飬pDst + len < pSrc || pDst > pSrc
	if (pDst == NULL || pSrc == NULL)
	{
		return NULL;
	}
	if ((pDst + len) < pSrc || pDst > pSrc)
	{
		//��ַδ�ص�����������
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
		//��ַ�ص������򿽱�
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

