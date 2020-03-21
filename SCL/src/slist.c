#include "slist.h"
#include <stdlib.h>

void slist_init(slist_entry_t* slist)
{
	if (!slist)	return;
	slist->head = NULL;
	slist->tail = NULL;
}

void slist_add_tail(slist_entry_t* slist, s_entry_t* newnode)
{
	if (!slist || !newnode)
		return;
	newnode->flink = NULL;
	if (!slist->head)
	{
		slist->head = newnode;
		slist->tail = newnode;
	}
	else
	{
		slist->tail->flink = newnode;
		slist->tail = newnode;
	}
}

void slist_add_head(slist_entry_t* slist, s_entry_t* newnode)
{
	if (!slist || !newnode)
		return ;

	newnode->flink = slist->head;
	if (!slist->tail)
	{
		slist->tail = newnode;
	}

	slist->head = newnode;
}

