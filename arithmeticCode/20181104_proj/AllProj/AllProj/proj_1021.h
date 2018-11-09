// Ex_ListOpr.cpp : �������̨Ӧ�ó������ڵ㡣
//1.����һ������2�ַ�����
//2.��������
//3.��һ��������ɾ��һ����㣨Ч�ʸߣ�

#pragma once
#include <stdio.h>
#include <stdlib.h>

#define LEN sizeof(struct struct_node)

typedef struct struct_node3
{
	int data;
	struct_node3 *next;
}node3, *pnode3;


void creatList(node3 *head)
{
	if (head == NULL)
		//head = p1;
		//head = NULL;
		return;
	//node *head;
	node3 *p1, *p2;
	//node *p2;
	p2 = head;
	//��ʼ��5�����
	int nodecount = 5;
	head->data = 0;
	//head = NULL;
	while (nodecount)
	{
		p1 = (node3*)malloc(LEN);
		p1->data = nodecount;
		p2->next = p1;
		p2 = p1;
		nodecount--;
	}
	p1->next = NULL;
	p2 = p1;

	//return(head);
}

//�ǵݹ鷽ʽ
//r = q->next
//q->next = p;
//p = r
node3* ListOprReverse(node3 *head)
{
	//node *p1 = (node*)malloc(LEN);
	//node *head = creatList();
	//��������ָ��p q r
	node3 *tmpP, *tmpQ, *tmpR;
	tmpP = tmpQ = tmpR = head;
	//tmpP->next = NULL;
	while (tmpR->next != NULL)
	{
		//����
		tmpR = tmpQ->next;
		//����
		tmpQ->next = tmpP;
		//����

		tmpP = tmpQ;
		tmpQ = tmpR;

		//tmpR = tmpR->next;
	}
	//����β���
	tmpQ->next = tmpP;
	//����ͷ�ڵ�
	head->next = NULL;
	return tmpQ;
}

//�ݹ鷽ʽ
//��ѡȡ3������������
//���һ�� h->next->next = h;
//���� h == null || h == 1��
node3* ListOprReverse2(node3 *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	node3 *newhead = ListOprReverse2(head->next);
	head->next->next = head;
	head->next = NULL;
	return newhead;
}

//ð������
node3* ListOprSort(node3 *head)
{
	if ((head->next == NULL) || (head->next->next == NULL))
	{
		return head;
	}

	node3 *first, *pre, *cur, *next, *end, *temp;
	first = head;
	end = NULL;
	//������ͷ��ʼ���ϴ�ֵ�����
	while (first->next != end)
	{
		for (pre = first, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			//���ڵĽڵ�Ƚ�
			if (cur->data > next->data)
			{
				cur->next = next->next;
				pre->next = next;
				next->next = cur;
				temp = next;
				next = cur;
				cur = temp;
			}
		}
		end = cur;
	}
	return head;
}

//ѭ��q = q->next
//q->next = p->next
//free(q->next)
//O(1)
//p->value = p->next->value;
//p->next = p->next->next
//free(p->next)
node3* ListOprDelNode(node3* head, int data)
{
	node3 *p;
	p = head;
	while (p != NULL)
	{
		//��ͷ�ڵ�
		if (head->next == NULL && head->data == data)
		{
			free(head);
			head = NULL;
			return head;
		}
		//�м��㺬ͷ���
		if (p->data == data && p->next != NULL)
		{
			p->data = p->next->data;
			p->next = p->next->next;
			//free(p->next);
			return head;
		}

		p = p->next;
	}
	//β��㵥������һ��
	p = head;
	while (p->next != NULL)
	{
		if (p->next->data == data && p->next->next == NULL)
		{
			p->next = NULL;
			free(p->next);
			return head;
		}
		p = p->next;
	}

	return head;
}

void showResult(node3 *head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

