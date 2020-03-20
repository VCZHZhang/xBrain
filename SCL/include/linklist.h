#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct Node
{
	int val;
<<<<<<< HEAD
	Node *next;
=======
	struct Node *next;
>>>>>>> 4f511a9de4a78505f4e43cbb5de31d03f66f8942
}Node;
typedef struct Node Node;

typedef struct LinkList
{
	struct Node head;
	struct Node tail;
}LinkList;


<<<<<<< HEAD
typedef struct LinkList LinkList;
void LinkListInit(struct LinkList *mylist);
int LinkListInsertHead(struct LinkList *mylist, int val);
int show(struct LinkList *list);

#endif 
=======
void LinkListInit(struct LinkList *mylist);
LinkList* LinkListInsertHead(struct LinkList *mylist, int val);
int show(struct LinkList *list);

#endif 
>>>>>>> 4f511a9de4a78505f4e43cbb5de31d03f66f8942
