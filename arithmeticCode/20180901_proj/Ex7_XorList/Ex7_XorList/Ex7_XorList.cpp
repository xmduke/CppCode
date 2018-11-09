// Ex7_XorList.cpp : �������̨Ӧ�ó������ڵ㡣
//7.ͨ�����ʵ��һ��ֻ��һ��ָ�����˫������
//p->next = pl^pr

#include "stdafx.h"
#include <stdlib.h>
#include <memory.h>
unsigned long FIRST = 0, NEXT = 0, PREV = 0;
struct _XORNODE
{
	char ch;
	unsigned long next;//������������ĵ�ַ
};

typedef struct _xorlist
{
	_XORNODE *head;//ͷβָ��
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
	{//����ǵ�һ���ڵ�
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
	return p;//���ص�pҪô��Ҫ���ҵĽڵ㣬ҪôΪ�ձ�ʾû�д˽ڵ�
}

//delete
void deleteXorList(char ch)
{
	_XORNODE *p = locate(ch), *r;
	if (p == NULL)
	{//û�д˽ڵ�
		printf(" isn't exist!");
		return;
	}
	r = p;//���±�ɾ�ڵ�
	NEXT = PREV ^ p->next;//PREV���ڲ���������Ϊ��ǰ�ڵ��ǰ��
	unsigned long currentP = (unsigned long)(p);
	if (p == list->head && p == list->tail) list->head = list->tail = NULL;//������ֻ��һ���ڵ�
	else if (p == list->head)
	{
		//��Ϊͷ���
		p = (_XORNODE *)(NEXT);
		p->next = PREV ^ currentP ^ p->next;
		list->head = p;
	}
	else if (p == list->tail)
	{
		//��Ϊβ�ڵ�
		p = (_XORNODE *)(PREV);
		p->next = p->next ^ currentP ^ NEXT;
		list->tail = p;
	}
	else
	{
		//һ�����
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

