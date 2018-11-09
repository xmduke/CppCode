#pragma once
#include <stdio.h>
#include <stdlib.h>
//找出单向非循环链表中倒数m结点
#define LEN sizeof(struct struct_node)
typedef struct struct_node2
{
	int data;
	struct_node2 *next;
}node2, *pnode2;


node2 *creatList2()
{
	node2 *head;
	node2 *p1, *p2;
	//初始化5个结点
	int nodecount = 5;
	p1 = p2 = (node2*)malloc(LEN);
	p1->data = 0;
	head = NULL;
	while (nodecount)
	{
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (node2*)malloc(LEN);
		p1->data = nodecount;

		nodecount--;
	}
	p1->next = NULL;
	p2->next = p1;
	return(head);
}

node2 *FindLoopNumber(node2 *head, int num)
{
	if (head == NULL)
	{
		return NULL;
	}

	node2 *first = head;
	node2 *second = head;
	node2 *tmp = head;
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