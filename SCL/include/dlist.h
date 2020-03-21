/****
module: double linked list
*****/
#ifndef __DLIST_H__
#define __DLIST_H__
typedef struct d_entry_s
{
	struct d_entry_s *flink;
	struct d_entry_s *blink;
}d_entry_t;

void dlist_init(d_entry_t* head);

void dlist_add_tail(d_entry_t* head, d_entry_t* newnode);

void dlist_add_head(d_entry_t* head, d_entry_t* newnode);

#define dlist_for_each(pos, head) \
	for (pos = (head)->flink; pos != head; pos = pos->flink)

#define dlist_reverse_for_each(pos, head)  \
	for (pos = (head)->blink; pos != head; pos = pos->blink)

#endif 
