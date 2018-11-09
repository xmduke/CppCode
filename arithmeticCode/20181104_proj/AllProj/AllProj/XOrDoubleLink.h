
typedef struct _Node
{
	int data;
	struct _Node * next;
}Node;

extern Node *head;
extern Node *tail;


extern Node * CreateLinker();
extern int  InitLinker(int (&p)[10]);
extern void Display();
extern int DeleteNode(int data);
extern int FindNode(int data);
extern int InsertIndex(int index, int data);
extern void FreeLinker(Node *head);