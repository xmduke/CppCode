// Ex5_ReverseWord.cpp : �������̨Ӧ�ó������ڵ㡣
//5.��һ���ַ������յ������� "hello world" -> "world hello"

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 3


//˼·���Կո�Ϊ�߽�Ե��ʽ��зָ�ٷֱ𱣴浽�ַ�������
typedef struct _WORD
{
	char* aWord;
	int WordLen;
}WORD;

char* split(char* cStr, int iStr)
{
	char tmp[10] = {0};
	int i = 0;
	while (iStr--)
	{
		tmp[i] = *cStr;
		cStr++;
		i++;
	}
	return tmp;
}

void RevWord(char* MultiWord)
{
	WORD *Word = (WORD *)malloc(1 * sizeof(WORD));
	Word->aWord = MultiWord;
	Word->WordLen = 0;
	WORD word1;
	while (*MultiWord != 0x00)
	{
		MultiWord++;
		Word->WordLen++;
		if (*MultiWord == 0x20)
		{
			
			word1.aWord = split(Word->aWord, Word->WordLen);
			word1.WordLen = Word->WordLen;
			Word->aWord = MultiWord + 1;
			Word->WordLen = -1;
		}
	}
	WORD word2;
	word2.aWord = Word->aWord;
	word2.WordLen = Word->WordLen;
	
	char* str;
	char stmp[20] = { 0 };
	int i = 0;
	while (word2.WordLen--)
	{
		if (word2.aWord != "\0")
		{
			stmp[i] = *word2.aWord;
		}
		else
		{
			break;
		}
		word2.aWord++;
		i++;
	}
	stmp[i] = *" ";
	i++;
	while (word1.WordLen--)
	{
		if (word1.aWord != "\0")
		{
			stmp[i] = *word1.aWord;
		}
		else
		{
			break;
		}
		word1.aWord++;
		i++;
	}
	WORD word3;
	word3.aWord = (char*)stmp;
	word3.WordLen = i;
	while (word3.WordLen--)
	{
		printf("%c", *word3.aWord);
		word3.aWord++;
	}
	free(Word);
}

int _tmain(int argc, _TCHAR* argv[])
{
	RevWord("Hello world");
	printf("\n");
	return 0;
}

