#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "XOrDoubleLink.h"

Node *head;
Node *tail;

Node * CreateLinker()
{
	head = (Node *)malloc(sizeof(Node));
	if(head == NULL)
	{
		return NULL;
	}
	head->data = -1;
	head->next = NULL;
	tail = head;
	return head;
}


int InsertNode(int data)
{
	Node * node;

	if(tail == NULL)
		return -1;

	node = (Node *)malloc(sizeof(Node));
	if(node == NULL)
	{
		return -1;
	}
	
	else
	{
		node->data = data;
		tail->next = (Node *)(((int)node) ^ ((int)tail->next));
		node->next = (Node *)(((int)tail) ^ NULL );
	}
	tail = node;
	return 0;
}

//Insert by index
int InsertIndex(int index, int data)
{
	Node *node;
	Node *p = head;
	Node *pl = NULL;
	Node *pr = NULL;
	int i=1;

	if(tail == NULL)
		return -1;

	node = (Node *)malloc(sizeof(Node));
	if(node == NULL)
	{
		return -1;
	}
	node->data = data;
	node->next = NULL;

	while(p != tail)
	{
		pr = (Node *)( (int)pl ^ (int)p->next );
		if(i == index)
		{
			node->next = (Node *)( ((int)pr) ^ (int)(p) );
			pr->next = (Node *)( ((int)(pr->next)) ^ (int)p ^ (int)node );
			p->next = (Node *)( (int)pl ^ (int)node );
			return i;
		}
		pl = p;
		p = pr;
		i++;
	}
	return 0;
}

//
int InitLinker(int (&p)[10])
{
	int i;
	
	for(i=0; i<10; i++)
	{
		if(-1 == InsertNode(p[i]))
			return -1; 
	}

	return 0;
}


//Display from head
void DisplayHead()
{	
	int i=1;
	Node *p = head;
	Node *pl = NULL;
	Node *pr = NULL;
	printf("Display from head:\n");
	while(p!=tail)
	{
		pr = (Node *)((int)pl^ (int)p->next);
		printf("[%d]", pr->data);
		pl = p;
		p = pr;
	}
	printf("\n");
}

// Display from tail
void DisplayTail()
{	
	int i=1;
	Node *p = tail;
	Node *pl = NULL;
	Node *pr = NULL;
	printf("Display from tail:\n");
	while(p != head)
	{
		pl = (Node *)((int)pr^ (int)p->next);
		printf("[%d]", p->data);
		pr = p;
		p = pl;
	}
	printf("\n");
}

void Display()
{
	DisplayHead();
	DisplayTail();
}


int DeleteNode(int data)
{
	int i=1;
	Node *p = head;
	Node *pl = NULL;
	Node *pr = NULL;
	int flag = 0;

	while(p!=tail)
	{
		pr = (Node *)((int)pl^ (int)p->next);
		pl = p;
		p = pr;
		if(p->data == data)
		{
			pr = (Node *)((int)pl^ (int)p->next);
			if(pr == NULL) //the data is the tail of linker
			{
				pl->next =(Node *)((int)pl->next^(int)p^NULL);
				tail = pl;
				return i;
			}
			else
			{
				pl->next =(Node *)((int)pl->next^(int)p^(int)pr);
				pr->next = (Node *)((int)p^(int)pr->next^(int)pl );
				return i;
			}
		}
		i++;
	}
	return 0;
	
}

int FindNode(int data)
{
	int i=1;
	Node *p = head;
	Node *pl = NULL;
	Node *pr = NULL;
	int flag = 0;

	while(p!=tail)
	{
		pr = (Node *)((int)pl^ (int)p->next);
		if(pr->data == data)
			return i;
		pl = p;
		p = pr;
		i++;
	}
	return 0;
}

void FreeLinker(Node *head)
{
	Node *p = head;
	Node *pl = NULL;
	Node *pr = NULL;
	if(head == NULL)
	{
		return;
	}
	while(p!=tail)
	{
		pr = (Node *)((int)pl^ (int)p->next);
		if(pl!=NULL)
		{
			printf("release node [%d]\n", pl->data);
			free(pl);
		}
		pl = p;
		p = pr;
	}
	//release pl & p
	if(p==tail)
	{
		printf("release node [%d]\n", pl->data);
		free(pl);
		printf("release node [%d]\n", p->data);
		free(p);
	}
}

void Linker()
{
	Node *Header;
	int index = 0;
	int a;
	int b;
	int c;
	int buf[]={1,2,3,4,5,6,7,8,9,0};
	Header = CreateLinker();
	if(Header == NULL)
		return ;
	if(-1 == InitLinker(buf))
	{
		FreeLinker(Header);
		return;
	}
	printf("\nCreate a linker\n");

	Display();

	a = 0;
	index = DeleteNode(a);
	if(index > 0)
	{
		printf("\nDelete data[%d] at Linker index[%d]\n", a, index);
	}

	Display();

	b = 4;
	index = FindNode(b);
	if(index > 0)
	{
		printf("\nFind data[%d] at Linker index[%d]\n", b, index);
	}

	Display();

	c = 33;
	index = InsertIndex(2, c);
	if(index > 0)
	{
		printf("\nInsert data[%d] befor index[%d]\n", c, 2);
	}

	Display();

	FreeLinker(Header);
}

//void main(void)
//{
//	Linker();
//}

