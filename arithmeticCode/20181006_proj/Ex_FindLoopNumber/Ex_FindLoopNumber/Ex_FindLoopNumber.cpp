// Ex_FindLoopNumber.cpp : 定义控制台应用程序的入口点。
//找出单向非循环链表中倒数m结点

#include "stdafx.h"
#include <stdlib.h>
#define LEN sizeof(struct struct_node)
typedef struct struct_node
{
	int data;
	struct_node *next;
}node, *pnode;


node *creatList()
{
	node *head;
	node *p1, *p2;
	//初始化5个结点
	int nodecount = 5;
	p1 = p2 = (node*)malloc(LEN);
	p1->data = 0;
	head = NULL;
	while (nodecount)
	{
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (node*)malloc(LEN);
		p1->data = nodecount;

		nodecount--;
	}
	p1->next = NULL;
	p2->next = p1;
	return(head);
}

node *FindLoopNumber(node *head, int num)
{
	if (head == NULL)
	{
		return NULL;
	}
	
	node *first = head;
	node *second = head;
	node *tmp = head;
	int length = 0;
	//遍历链表获得链表长度
	/*while (tmp->next != NULL)
	{
	length++;
	tmp = tmp->next;
	}
	if (length < num)
	{
	return NULL;
	}*/
	//设置2个指针，一个先走num个节点后，第二个指针再走
	while (num)
	{
		num--;
		first = first->next;
		if (first == NULL)//在这里判断，则不用遍历
		{
			return NULL;
		}
	}
	//开始同时走第一个指针走完，则返回第二个指针的地址
	while (first->next != NULL)
	{
		first = first->next;
		second = second->next;
	}
	return second;
}

int _tmain(int argc, _TCHAR* argv[])
{
	node *nodelist;
	nodelist = creatList();
	node *resnode = FindLoopNumber(nodelist, 3);
	if (resnode == NULL)
	{
		printf("num 大于 节点数, num 不在链表范围内\n");
	}
	else
	{
		printf("第%d个结点的地址为：0x%x\n", 3, resnode);
	}
	return 0;
}

