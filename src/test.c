#include "treeset/private_treeset.h"
#include "wrapper/wrappers.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define assert_true(x) assert(x)
#define assert_false(x) assert(!x)

void setup()
{

}

void clean()
{
}

void print_tree(Int i)
{
	printf("%d\n", i->v);
}

int main()
{
	TreeSet t = create_treeset(wrapper_cmp(IntType, false));
	set_add(t, wInt(5));
	apply(t, print_tree);

	return EXIT_SUCCESS;
}
