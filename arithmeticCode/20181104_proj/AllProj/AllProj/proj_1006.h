// Ex_FindLoopInList.cpp : �������̨Ӧ�ó������ڵ㡣
//
/************************************************************************/
/*   ����ж�һ�����������ѭ��
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
	//��ʼ��5�����
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
	//�����������߹��ڵ�
	node *recorde[16];
	int count = 0;
	while (head->next != NULL)
	{
		//��¼
		recorde[count] = second;
		//first��2���ڵ�
		first = first->next->next;
		//second��1���ڵ�
		second = second->next;

		//С�ڵ�ʱ���ж�ʱ����second�߹��ķ�Χ�ڣ�����ѭ��
		if (first <= second)
		{
			int countbak = count;
			//�ж�first�Ƿ������߹��Ľڵ���
			//�����¼��ǰ�ڵ�Ϊѭ����ڲ�����
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




