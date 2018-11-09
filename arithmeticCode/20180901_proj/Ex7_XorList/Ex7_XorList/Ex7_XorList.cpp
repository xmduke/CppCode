// Ex7_XorList.cpp : 定义控制台应用程序的入口点。
//7.通过异或实现一个只带一个指针域的双向链表
//p->next = pl^pr

#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>
unsigned long FIRST = 0, NEXT = 0, PREV = 0;
struct _XORNODE
{
	char ch;
	unsigned long next;//用来保存异或后的地址
};

typedef struct _xorlist
{
	_XORNODE *head;//头尾指针
	_XORNODE *tail;
}xorlist;

xorlist *list;
//insert 5 elements in list
void insertNode(char elemC)
{
	NEXT = 0;
	_XORNODE *p = (_XORNODE *)malloc(sizeof(_XORNODE));
	p->ch = elemC;
	PREV = (unsigned long)list->tail;
	//list->head = NULL;
	if (list->head == NULL)
	{//如果是第一个节点
		list->head = p;
		list->tail = p;
		p->next = PREV ^ NEXT;
	}
	else
	{
		list->tail = p;
		p->next = PREV ^ NEXT;
		_XORNODE *q = (_XORNODE *)(PREV);
		q->next = q->next ^ (unsigned long)p;
	}
}


//create list head
void createList()
{
	char ch[] = {'a', 'b', 'c', 'd', 'e'};
	for (int i = 0; i != 5; i++)
	{
		insertNode(ch[i]);
	}
}


//traverse1
void showAllListByleft()
{
	PREV = 0;
	_XORNODE *p = list->head;
	while (p != list->tail)
	{
		printf("%c", p->ch);
		NEXT = PREV ^ (p->next);
		PREV = (unsigned long)p;
		p = (_XORNODE *)NEXT;
	}
	printf("%c\n", p->ch);
}

//traverse2
void showAllListByright()
{
	NEXT = 0;
	_XORNODE *p = list->tail;
	while (p != list->head)
	{
		printf("%c", p->ch);
		PREV = NEXT ^ (p->next);
		NEXT = (unsigned long)p;
		p = (_XORNODE *)PREV;
	}
	printf("%c\n", p->ch);
}

//locate
_XORNODE* locate(char ch)
{
	PREV = 0;
	_XORNODE *p = list->head, *r = list->head;
	while (p != NULL && p->ch != ch)
	{
		p = (_XORNODE*)(p->next ^ PREV);
		PREV = (unsigned long)(r);
		r = p;
	}
	return p;//返回的p要么是要查找的节点，要么为空表示没有此节点
}

//delete
void deleteXorList(char ch)
{
	_XORNODE *p = locate(ch), *r;
	if (p == NULL)
	{//没有此节点
		printf(" isn't exist!");
		return;
	}
	r = p;//记下被删节点
	NEXT = PREV ^ p->next;//PREV已在查找中设置为当前节点的前驱
	unsigned long currentP = (unsigned long)(p);
	if (p == list->head && p == list->tail) list->head = list->tail = NULL;//若链表只有一个节点
	else if (p == list->head)
	{
		//若为头结点
		p = (_XORNODE *)(NEXT);
		p->next = PREV ^ currentP ^ p->next;
		list->head = p;
	}
	else if (p == list->tail)
	{
		//若为尾节点
		p = (_XORNODE *)(PREV);
		p->next = p->next ^ currentP ^ NEXT;
		list->tail = p;
	}
	else
	{
		//一般情况
		p = (_XORNODE *)(PREV);
		p->next = p->next ^ currentP ^ NEXT;
		p = (_XORNODE *)(NEXT);
		p->next = PREV ^ currentP ^ p->next;
	}
	delete r;
}


int _tmain(int argc, _TCHAR* argv[])
{
	list = (xorlist *)malloc(sizeof(xorlist));
	memset(list, 0, sizeof(xorlist));
	createList();
	showAllListByleft();
	showAllListByright();
	printf("delete: 'b'\n");
	deleteXorList('b');
	showAllListByleft();
	printf("delete head:\n");
	deleteXorList('a');
	showAllListByleft();
	printf("delete tail:\n");
	deleteXorList('e');
	showAllListByleft();
	return 0;
}

