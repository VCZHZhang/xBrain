#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct Node
{
	int val;
	struct Node *next;
}Node;
typedef struct Node Node;

typedef struct LinkList
{
	struct Node head;
	struct Node tail;
}LinkList;


void LinkListInit(struct LinkList *mylist);
LinkList* LinkListInsertHead(struct LinkList *mylist, int val);
int show(struct LinkList *list);

#endif 
