#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <stdbool.h>

struct _int
{
	int v;	
};

typedef struct _int* Int;
Int wInt(int);
int cmp_int(Int,Int);
int cmp_int_inv(Int,Int);

struct _float
{
	float v;
};

typedef struct _float* Float;
int cmp_float(Float,Float);
int cmp_float_inv(Float,Float);

struct _double
{
	double v;
};

typedef struct _double* Double;
int cmp_double(Double,Double);
int cmp_double_inv(Double,Double);

struct _char
{
	char v;
};

typedef struct _char* Char;
int cmp_char(Char,Char);
int cmp_char_inv(Char,Char);

typedef enum _wrp_type
{
	IntType,
	FloatType,
	DoubleType,
	CharType
} WrapperType;

void* wrapper_cmp(WrapperType type, bool inverted);
#endif /* WRAPPERS_H */
