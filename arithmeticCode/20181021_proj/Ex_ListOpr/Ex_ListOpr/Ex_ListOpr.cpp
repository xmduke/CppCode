// Ex_ListOpr.cpp : 定义控制台应用程序的入口点。
//1.逆置一个链表（2种方法）
//2.链表排序
//3.从一个链表中删除一个结点（效率高）

#include "stdafx.h"
#include <stdlib.h>

#define LEN sizeof(struct struct_node)

typedef struct struct_node
{
	int data;
	struct_node *next;
}node, *pnode;


void creatList(node *head)
{
	if (head == NULL)
		//head = p1;
		//head = NULL;
		return ;
	//node *head;
	node *p1, *p2;
	//node *p2;
	p2 = head;
	//初始化5个结点
	int nodecount = 5;
	head->data = 0;
	//head = NULL;
	while (nodecount)
	{
		p1 = (node*)malloc(LEN);
		p1->data = nodecount;
		p2->next = p1;
		p2 = p1;
		nodecount--;
	}
	p1->next = NULL;
	p2 = p1;

	//return(head);
}

//非递归方式
//r = q->next
//q->next = p;
//p = r
node* ListOprReverse(node *head)
{
	//node *p1 = (node*)malloc(LEN);
	//node *head = creatList();
	//定义三个指针p q r
	node *tmpP, *tmpQ, *tmpR;
	tmpP = tmpQ = tmpR = head;
	//tmpP->next = NULL;
	while (tmpR->next != NULL)
	{
		//保存
		tmpR = tmpQ->next;
		//逆置
		tmpQ->next = tmpP;
		//后移
		
		tmpP = tmpQ;
		tmpQ = tmpR;
		
		//tmpR = tmpR->next;
	}
	//处理尾结点
	tmpQ->next = tmpP;
	//处理头节点
	head->next = NULL;
	return tmpQ;
}

//递归方式
//先选取3个结点进行逆置
//最后一次 h->next->next = h;
//出口 h == null || h == 1；
node* ListOprReverse2(node *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	node *newhead = ListOprReverse2(head->next);
	head->next->next = head;
	head->next = NULL;
	return newhead;
}

//冒泡排序
node* ListOprSort(node *head)
{
	if ((head->next == NULL) || (head->next->next == NULL))
	{
		return head;
	}

	node *first, *pre, *cur, *next, *end, *temp;
	first = head;
	end = NULL;
	//从链表头开始将较大值往后沉
	while (first->next != end)
	{
		for (pre = first, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			//相邻的节点比较
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

//循环q = q->next
//q->next = p->next
//free(q->next)
//O(1)
//p->value = p->next->value;
//p->next = p->next->next
//free(p->next)
node* ListOprDelNode(node* head, int data)
{
	node *p;
	p = head;
	while (p != NULL)
	{
		//仅头节点
		if (head->next == NULL && head->data == data)
		{
			free(head);
			head = NULL;
			return head;
		}
		//中间结点含头结点
		if (p->data == data && p->next != NULL)
		{
			p->data = p->next->data;
			p->next = p->next->next;
			//free(p->next);
			return head;
		}
		
		p = p->next;
	}
	//尾结点单独遍历一次
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

void showResult(node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
int _tmain(int argc, _TCHAR* argv[])
{
	//非递归逆置
	printf("****非递归逆置****\n");
	node *nodeList = (node*)malloc(LEN);
	nodeList->next = NULL;
	creatList(nodeList);
	showResult(nodeList);
	nodeList = ListOprReverse(nodeList);
	showResult(nodeList);
	free(nodeList);
	nodeList = NULL;

	//递归逆置
	printf("****递归逆置****\n");
	node *nodeList2 = (node*)malloc(LEN);
	nodeList2->next = NULL;
	creatList(nodeList2);
	showResult(nodeList2);
	nodeList2 = ListOprReverse2(nodeList2);
	showResult(nodeList2);
	free(nodeList2);
	nodeList2 = NULL;

	//排序
	printf("****排序****\n");
	node *nodeList3 = (node*)malloc(LEN);
	nodeList3->next = NULL;
	creatList(nodeList3);
	showResult(nodeList3);
	nodeList3 = ListOprSort(nodeList3);
	showResult(nodeList3);
	free(nodeList3);
	nodeList3 = NULL;

	//删除
	printf("****删除****\n");
	node *nodeList4 = (node*)malloc(LEN);
	nodeList4->next = NULL;
	creatList(nodeList4);
	showResult(nodeList4);
	nodeList4 = ListOprDelNode(nodeList4, 5);
	showResult(nodeList4);
	free(nodeList4);
	nodeList4 = NULL;

	//删除尾结点
	printf("****删除尾结点****\n");
	node *nodeList5 = (node*)malloc(LEN);
	nodeList5->next = NULL;
	creatList(nodeList5);
	showResult(nodeList5);
	nodeList5 = ListOprDelNode(nodeList5, 1);
	showResult(nodeList5);
	free(nodeList5);
	nodeList5 = NULL;

	return 0;
}

