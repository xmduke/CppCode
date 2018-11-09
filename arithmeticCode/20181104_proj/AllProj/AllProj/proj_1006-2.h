#pragma once
#include <stdio.h>
#include <stdlib.h>
//�ҳ������ѭ�������е���m���
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
	//��ʼ��5�����
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
	//����������������
	/*while (tmp->next != NULL)
	{
	length++;
	tmp = tmp->next;
	}
	if (length < num)
	{
	return NULL;
	}*/
	//����2��ָ�룬һ������num���ڵ�󣬵ڶ���ָ������
	while (num)
	{
		num--;
		first = first->next;
		if (first == NULL)//�������жϣ����ñ���
		{
			return NULL;
		}
	}
	//��ʼͬʱ�ߵ�һ��ָ�����꣬�򷵻صڶ���ָ��ĵ�ַ
	while (first->next != NULL)
	{
		first = first->next;
		second = second->next;
	}
	return second;
}