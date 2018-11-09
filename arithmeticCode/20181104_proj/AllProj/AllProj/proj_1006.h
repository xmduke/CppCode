// Ex_FindLoopInList.cpp : 定义控制台应用程序的入口点。
//
/************************************************************************/
/*   如何判断一个单链表存在循环
typedef struct_node
{
int data;
struct_node *next;
}node,*pnode;
node *FindLoop(node *head);
*/
/************************************************************************/
#pragma once
#include <stdio.h>
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
	p1->next = head->next->next;
	p2->next = p1;
	return(head);
}

node *FindLoop(node *head)
{
	node *first = head;
	node *second = head;
	//遍历并保存走过节点
	node *recorde[16];
	int count = 0;
	while (head->next != NULL)
	{
		//记录
		recorde[count] = second;
		//first走2个节点
		first = first->next->next;
		//second走1个节点
		second = second->next;

		//小于的时候判断时候在second走过的范围内，存在循环
		if (first <= second)
		{
			int countbak = count;
			//判断first是否落在走过的节点内
			//是则记录当前节点为循环入口并返回
			while (countbak)
			{
				if (first == recorde[countbak])
				{
					return first;
				}
				countbak--;
			}
			//return first;
		}
		count++;
	}
	return NULL;
}




