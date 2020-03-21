#include "slist.h"
#include "dlist.h"
#include "common.h"

#include <stdlib.h>

typedef struct Student
{
	s_entry_t node;
	int age;
}Student;

extern void testslink()
{
	slist_entry_t stu_head;
	slist_init(&stu_head);
	int i = 0;
	for (i = 0; i < 3; ++i)
	{
		struct Student* p = (struct Student*)malloc(sizeof(struct Student));
		p->age = i;
		slist_add_tail(&stu_head, &p->node);
	}
	printf("\n");
	s_entry_t *pos = NULL;
	slist_for_each(pos, &stu_head)
	{
		printf("age:%d ", ((Student*)pos)->age);
	}

	for (i = 0; i < 3; ++i)
	{
		struct Student* p = (struct Student*)malloc(sizeof(struct Student));
		p->age = i;
		slist_add_head(&stu_head, &p->node);
	}
	printf("\n");
	// show   2 1 0 0 1 2 
	
	slist_for_each(pos, &stu_head)
	{
		printf("age:%d ", ((Student*)pos)->age);
	}
}

typedef struct Teacher
{
	d_entry_t node;
	int salary;

}Teacher;

extern void testdlink()
{
	d_entry_t dlist_head;
	dlist_init(&dlist_head);
	int i = 0;
	for (i = 0; i < 3; ++i)
	{
		struct Teacher* p = (struct Teacher*)malloc(sizeof(struct Teacher));
		p->salary = 1000*i+1000;
		dlist_add_tail(&dlist_head, &p->node);
	}
	printf("\n");
	d_entry_t* pos = NULL;
	dlist_for_each(pos, &dlist_head)
	{
		printf("salary:%d ", ((Teacher*)pos)->salary);
	}
	printf("\n");
	struct Teacher* p = NULL;
	dlist_reverse_for_each(pos, &dlist_head)
	{
		p = container_of(pos, struct Teacher, node);
		//printf("salary:%d ", ((Teacher*)pos)->salary);
		printf("salary:%d ", p->salary);
	}

	printf("\n");
}