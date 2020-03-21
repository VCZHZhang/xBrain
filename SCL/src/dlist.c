#include "dlist.h"

void dlist_init(d_entry_t* head)
{
	if (!head) return ;
	head->flink = head;
	head->blink = head;
}

void dlist_add(d_entry_t* prev, d_entry_t* next, d_entry_t* newnode)
{
	if (!newnode || !prev || !next) return;
	next->blink = newnode;
	newnode->flink = next;
	newnode->blink = prev;
	prev->flink = newnode;
}

void dlist_add_tail(d_entry_t* head, d_entry_t* newnode)
{
	if (!head || !newnode) return ;

	dlist_add(head->blink, head, newnode);
}

void dlist_add_head(d_entry_t* head, d_entry_t* newnode)
{
	if (!head || !newnode) return ;

	dlist_add(head, head->flink, newnode);
}

