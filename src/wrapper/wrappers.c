#include <stdlib.h>
#include "wrappers.h"


int cmp_wrp(void* i1, void* i2, WrapperType type)
{
	switch(type)
	{
		case IntType:
			return ((Int) i1)->v > ((Int) i2)->v; 
		break;
		case FloatType:
			return ((Float) i1)->v > ((Float) i2)->v; 
		break;
		case DoubleType:
			return ((Double) i1)->v > ((Float) i2)->v; 
		break;
		case CharType:
			return ((Char) i1)->v > ((Char) i2)->v; 
	}

	return 0;
}

int inv_cmp_wrp(void* i1, void* i2, WrapperType type)
{
	return -cmp_wrp(i1, i2, type);
}
