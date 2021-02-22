#include "treeset/private_treeset.h"
#include "wrapper/wrappers.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define assert_false(x) assert(!x)
#define log(x) printf("%s", x)

void print_tree(Int i)
{
	printf("%c\n", i->v);
}

void add_test()
{
	TreeSet t = create_treeset(wrapper_cmp(IntType, false));

	for(int i = -99; i < 100; i++)
	{
		assert(set_add(t, wInt(i)));
	}	

	assert_false(set_add(t, wInt(0)));
	assert_false(set_add(t, wInt(-80)));
	assert(set_add(t, wInt(500)));
}

int main()
{
	log("Add test..."); add_test(); log(" Ok\n");

	return EXIT_SUCCESS;
}
