/***
module: singly linked list
*/
#ifndef __SLIST_H__
#define __SLIST_H__

typedef struct s_entry_s
{
	struct s_entry_s *flink;
}s_entry_t;

//µ¥Á´±í
typedef struct slist_entry_s
{
	s_entry_t* head;
	s_entry_t* tail;
}slist_entry_t;

void slist_init(slist_entry_t* slist);

void slist_add_tail(struct slist_entry_s* slist, struct s_entry_s* newnode);

void slist_add_head(slist_entry_t* slist, s_entry_t* newnode);

#define slist_for_each(pos, slist) \
	for (pos = (slist)->head;  pos != NULL; pos = pos->flink)

#endif 