// Ex6_leftRotate.cpp : 定义控制台应用程序的入口点。
//6.将一个字符串左旋N个字符。如，左旋3个字符"hello world" "lo worldhel"
//dlrow olleh 
#include "stdafx.h"

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

int _tmain(int argc, _TCHAR* argv[])
{
	reverse_Nch("hello world");
	printf("%s\n", tmp);
	return 0;
}





/////////////
/*#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
using namespace std;
#define LEN sizeof(List)
//思路：
//对一个字符串按N分组，
//并存入链表，
//对链表的元素进行交换顺序 


typedef struct _LIST
{
	char *cWord;
	struct _LIST *next;
} List;

List *list;

void creat()
{
	//创建一个带头节点链表，头节点数据为空
	List *head;
	head = (List*)malloc(LEN);
	memset(head, 0, sizeof(head));
	list = head;
}


List* split(List *list, char *cTarget, int iSize)//N
{
	char tmp[5] = {};
	//List* res = list;
	int i = 0;
	int iSizetmp = iSize;
	while (iSize--)
	{
		tmp[i] = *cTarget;
		i++;
		cTarget++;
	}
	//list.insert;
	List *tmplist = (List*)malloc(LEN);
	tmplist->cWord = tmp;
	tmplist->next = NULL;
	list->next = tmplist;
	
	if (*cTarget == 0)
	{
		return list;
	}
	
	list = split(list->next, cTarget, 3);
	return list;
}

//链表排序函数
List* sortlist()
{
	List *head = list;
	List *pre = head;
	List *cur = pre->next;
	List *next = cur->next;
	List *end = NULL;
	List *temp;
	if ((list->next == NULL) || (list->next->next == NULL))
	{
		return list;
	}
	
	
	for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
	{
			
		cur->next = next->next;
		pre->next = next;
		next->next = cur;
		temp = next;
		next = cur;
		cur = temp;
	}
	return head;
}

void freeList(List *list)
{
	free(list);
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	/*creat();

	split(list, "Hello world", 3);
	List *head = list;
	List *pre = head;
	List *cur = pre->next;
	List *next = cur->next;
	List *end = NULL;
	List *temp;
	if ((list->next == NULL) || (list->next->next == NULL))
	{
		return 0;
	}

	for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
	{

		cur->next = next->next;
		pre->next = next;
		next->next = cur;
		temp = next;
		next = cur;
		cur = temp;
	}
	//list = sortlist();
	while (list->next->cWord != NULL)
	{
		puts(list->next->cWord);
		//printf(list->next->cWord);
		list = list->next;
	}
	//freeList(list);
	return 0;
}*/

