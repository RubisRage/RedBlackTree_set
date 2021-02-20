#include "tree_set.h"
#include "test_header.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct wrapper
{
	int v;
} Integer;

int compare(Integer* i1, Integer* i2)
{
	if(i1->v > i2->v) return 1;
	if(i1->v < i2->v) return -1;
	return 0;
}

void print_wrapper(Integer* i)
{
	printf("%d\n", i->v);
}

int main()
{
	TreeSet t = create_treeset(compare);
	Integer* i = malloc(sizeof(Integer));
	i->v = 50;
	set_add(t,i);
	i = malloc(sizeof(Integer));
	i->v = 20;
	set_add(t,i);
	i = malloc(sizeof(Integer));
	i->v = 90;
	set_add(t,i);
	i = malloc(sizeof(Integer));
	i->v = 10;
	set_add(t,i);
	i = malloc(sizeof(Integer));
	i->v = 15;
	set_add(t,i);
	
	/*for(int i = 0; i < 10; i++)
	{
		Integer* i1 = malloc(sizeof(Integer));
		i1->v = i;
		printf("%d\n", set_add(t,i1));
		i1 = malloc(sizeof(Integer));
		i1->v = -i;
		printf("%d\n", set_add(t,i1));
	}	
	printf("-----------\n");
	set_clear(t, true);*/

	apply(t, print_wrapper);
	set_destroy(t, true);
}
