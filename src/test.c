#include "treeset/private_treeset.h"
#include "wrapper/wrappers.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define assert_false(x) assert(!x)
#define run_test(str,test) printf("%s", str); test(); printf("\t\tOk\n");

char* strings[] = { "Aaaaaaa",
		  "Bbbbbbb",
		  "Hola Mundo",
		  "zzzzzzzzzz",
		  "Not inserted",
		  "Post insert",
		  "final string"
		};

void print_tree(char* i)
{
	printf("%s\n", i);
}

void int_add_test()
{
	TreeSet t = create_treeset(wrapper_cmp(IntType, false));

	for(int i = -99; i < 100; i++)
	{
		assert(set_add(t, wInt(i)));
	}	

	assert_false(set_add(t, wInt(0)));
	assert_false(set_add(t, wInt(-80)));
	assert(set_add(t, wInt(102)));
	assert(set_add(t, wInt(101)));

	for(int i = -99; i < 100; i++)
	{
		assert_false(set_add(t, wInt(i)));
	}

	set_destroy(t, true);
}

void str_add_test()
{
	TreeSet t = create_treeset(strcmp);

	assert(set_add(t,strings[0]));
	assert(set_add(t,strings[1]));
	assert(set_add(t,strings[2]));
	assert(set_add(t,strings[3]));
	assert(set_add(t,strings[4]));
	
	assert_false(set_add(t,strings[2]));
	assert_false(set_add(t,strings[3]));
	assert_false(set_add(t,strings[0]));
	assert_false(set_add(t,strings[1]));

	assert(set_add(t,strings[5]));
	assert(set_add(t,strings[6]));

	//apply(t, print_tree);

	set_destroy(t, false);
}

int main()
{
	printf("Starting test:\n");
	run_test(" - Int wrapper add test", int_add_test)
	run_test(" - String add test", str_add_test)

	return EXIT_SUCCESS;
}
