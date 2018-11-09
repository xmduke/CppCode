// Ex_FindLoopNumber.cpp : �������̨Ӧ�ó������ڵ㡣
//�ҳ������ѭ�������е���m���

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

int _tmain(int argc, _TCHAR* argv[])
{
	node *nodelist;
	nodelist = creatList();
	node *resnode = FindLoopNumber(nodelist, 3);
	if (resnode == NULL)
	{
		printf("num ���� �ڵ���, num ��������Χ��\n");
	}
	else
	{
		printf("��%d�����ĵ�ַΪ��0x%x\n", 3, resnode);
	}
	return 0;
}

