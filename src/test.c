#include "treeset/private_treeset.h"
#include "wrapper/wrappers.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define assert_false(x) assert(!x)
#define run_test(str,test) printf("%s", str); test(); printf("\x1b[32m""\t\tOk\n""\x1b[0m");

TreeSet t;
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

void int_setup()
{
	t = create_treeset(wrapper_cmp(IntType, false), true);

	set_add(t, wInt(5));
	set_add(t, wInt(15));
	set_add(t, wInt(-10));
	set_add(t, wInt(-25));
	set_add(t, wInt(0));
	set_add(t, wInt(100));

}

void str_setup()
{
	t = create_treeset(strcmp, false);

	set_add(t,strings[0]);
	set_add(t,strings[1]);
	set_add(t,strings[2]);
	set_add(t,strings[3]);
	set_add(t,strings[4]);
}

void int_add_test()
{
	TreeSet t = create_treeset(wrapper_cmp(IntType, false), true);

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
	t = create_treeset(strcmp, false);

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

void int_contains_test()
{
	int_setup();

	/*
	set_add(t, wInt(5));
	set_add(t, wInt(15));
	set_add(t, wInt(-10));
	set_add(t, wInt(-25));
	set_add(t, wInt(0));
	set_add(t, wInt(100));
	*/

	assert(set_contains(t, wInt(5)));
	assert(set_contains(t, wInt(15)));
	assert(set_contains(t, wInt(-10)));
	assert(set_contains(t, wInt(-25)));
	assert(set_contains(t, wInt(0)));
	assert(set_contains(t, wInt(100)));

	assert_false(set_contains(t, wInt(3)));
	assert_false(set_contains(t, wInt(-8)));
	assert_false(set_contains(t, wInt(-1000)));
	assert_false(set_contains(t, wInt(99)));
	assert_false(set_contains(t, wInt(101)));
	assert_false(set_contains(t, wInt(1)));

	set_destroy(t, true);
}

void str_contains_test()
{
	str_setup();

	assert(set_contains(t,strings[0]));
	assert(set_contains(t,strings[1]));
	assert(set_contains(t,strings[2]));
	assert(set_contains(t,strings[3]));
	assert(set_contains(t,strings[4]));

	assert_false(set_contains(t,strings[5]));
	assert_false(set_contains(t,strings[6]));
	assert_false(set_contains(t, "Hola mundo"));
	assert_false(set_contains(t, "This string is not contained"));
	assert_false(set_contains(t, "Hello, world! English version"));
}

int main()
{
	printf("Starting tests:\n");
	run_test(" - Int wrapper add test", int_add_test)
	run_test(" - String add test", str_add_test)
	run_test(" - Int contains test", int_contains_test)
	run_test(" - String contains test", str_contains_test)
	printf("\n\nAll tests passed successfully\n\n");

	return EXIT_SUCCESS;
}
