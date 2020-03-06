#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct Node
{
	int val;
	Node *next;
}Node;
typedef struct Node Node;

typedef struct LinkList
{
	struct Node head;
	struct Node tail;
}LinkList;


typedef struct LinkList LinkList;
void LinkListInit(struct LinkList *mylist);
int LinkListInsertHead(struct LinkList *mylist, int val);
int show(struct LinkList *list);

#endif 