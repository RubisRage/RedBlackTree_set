#include "wrappers.h"
#include <stddef.h>
#include <stdlib.h>

Int wInt(int v)
{
	Int i = malloc(sizeof(struct _int));
	i->v = v;
	return i;
}

int cmp_int(Int i1, Int i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_int_inv(Int i1, Int i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_float(Float i1, Float i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_float_inv(Float i1, Float i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_double(Double i1, Double i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_double_inv(Double i1, Double i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_char(Char i1, Char i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

int cmp_char_inv(Char i1, Char i2)
{
	if(i1->v>i2->v) return 1;
	else if(i1->v<i2->v) return -1;
	else return 0;
}

void* wrapper_cmp(WrapperType type, bool inverted)
{
	switch(type)
	{
		case IntType:
			return inverted? cmp_int_inv : cmp_int;
		break;
		case FloatType:
			return inverted? cmp_float_inv : cmp_float;
		break;
		case DoubleType:
			return inverted? cmp_double_inv : cmp_double;
		break;
		case CharType:
			return inverted? cmp_char_inv : cmp_char;
	}

	return NULL;
}
