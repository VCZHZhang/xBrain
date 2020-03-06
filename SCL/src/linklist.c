#include "linklist.h"
#include <stdlib.h>
#include <stdio.h>
/*
typedef struct LinkList
{
Node head;
Node tail;
}LinkList;
*/

void LinkListInit(struct LinkList *mylist)
{
	if (!mylist)	return;

	mylist->head.next = &(mylist->tail);
	mylist->tail.next = NULL;
}

int LinkListInsertHead(LinkList *mylist, int inval)
{
	struct Node *node = (Node*)malloc(sizeof(Node));
	node->val = inval;

	node->next = mylist->head.next;
	mylist->head.next = node;
	
	return mylist;
}

int show(LinkList *mylist)
{
	Node* t = mylist->head.next;
	while (t != &mylist->tail)
	{
		printf("%d\n", t->val);
		t = t->next;
	}
	return 0;
}
