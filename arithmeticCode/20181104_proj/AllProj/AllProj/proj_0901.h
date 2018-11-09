#pragma once
#include <stdio.h>
//0901-1.����һ�������Ķ��������ж��ٸ�1
size_t count_one(int val)
{
	size_t count = 0;

	while (val)
	{
		++count;
		val &= (val - 1);
		//val = val&(val-1)
	}
	return count;
}

size_t count_one_2(int x)//unsigned?
{
	size_t count = 0;
	while (x)
	{
		count += (x & 1);
		x >>= 1;
	}
	return count;
}

//0901-2.���һ��������ʮ���Ƶ�������ת��Ϊ36�����ַ���
// ��0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ��
//  1 = "0001"; 10 = "000A"; 20 = "000K"; 35 = "000Z"; 36 = "0010";
char * dto36(int x, char *buf, int len)//��Ҫ���ڴ�ͳ����ɵ������ṩ
{
	if (buf == NULL || len <= 0)
		return NULL;
	int pos = 0;
	int flag = 0;//������־

	if (x < 0)
	{
		x = 0 - x;//ע����С����ת��Ϊ�����������0x80000000���,��������-2147483648��36���ƿ�����buf��
		buf[pos++] = '-';
		flag = 1;
	}
	do //  ��36ȡ�࣬�̼�����36��ֱ��Ϊ0
	{
		int rem = x % 36;
		if (rem < 10)
			buf[pos++] = '0' + rem;
		else
		{
			buf[pos++] = 'A' + rem - 10;
		}
		x /= 36;

		if (pos >= len)
		{
			return NULL;
		}
	} while (x);
	buf[pos] = '\0';
	int total = pos - 1;
	//����
	for (int i = 0 + flag; i < total / 2; i++)
	{
		char tmp = buf[i];
		buf[i] = buf[total - 1 - i];
		buf[total - 1 - i] = tmp;
	}
	return buf;
}

//0901-3.�ж�һ��ƽ̨�ǵ�λ���Ȼ��Ǹ�λ����
int get_endian()
{
	int x = 0x1;
	char *p = (char *)&x;
	return *p;
}

//0901-4.�ı�һ�������Ĵ洢��ʽ��0x12345678->0x87654321��
void reverse_int(int* num)
{
	if (num == NULL)
		return;

	char *p = (char*)num;
	char *q = p + sizeof(int) - 1;
	while (p < q)
	{
		*p = *p^*q;
		*q = *p^*q;
		*p = *p^*q;

		p++;
		q--;
	}
	return;
}

//0901-5.��һ���ַ������յ������� "hello world" -> "world hello"
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
	char tmp[10] = { 0 };
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

//0901-6.��һ���ַ�������N���ַ����磬����3���ַ�"hello world" "lo worldhel"
int _strlen(char *str)
{
	int count = 0;
	char* strtmp = str;
	while ('\0' != *strtmp++)
	{
		count++;
	}
	return count;
}

char tmp[12] = { 0 };
void reverse_str(char *str)
{
	int len = _strlen(str);
	for (int i = 0; i <= len / 2; i++)
	{
		char ch = str[i];
		tmp[i] = str[len - 1 - i];
		tmp[len - 1 - i] = ch;
	}
}

void resverse_Second(char *str, int n)
{
	int len = _strlen(str);
	len = len - n;
	for (int i = n; i < n + (len / 2); i++)
	{
		char ch = str[i];
		tmp[i] = str[len - 1 + i];
		tmp[len - 1 + i] = ch;
	}
}
void resverse_First(char *str, int n)
{
	//int len = _strlen(str);
	for (int i = 0; i < n / 2; i++)
	{
		char ch = str[i];
		tmp[i] = str[n - 1 - i];
		tmp[n - 1 - i] = ch;
	}
}
void reverse_Nch(char *str)
{
	reverse_str(str);
	resverse_First(tmp, 8);
	resverse_Second(tmp, 8);
}


//0901-7.ͨ�����ʵ��һ��ֻ��һ��ָ�����˫������
//p->next = pl^pr
#include "XOrDoubleLink.h"
void Linker();
