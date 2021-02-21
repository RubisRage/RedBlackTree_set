#ifndef WRAPPERS_H
#define WRAPPERS_H

struct _int
{
	int v;	
};

typedef struct _int* Int;

struct _float
{
	float v;
};

typedef struct _float* Float;

struct _double
{
	double v;
};

typedef struct _double* Double;

struct _char
{
	char v;
};

typedef struct _char* Char;

typedef enum _wrp_type
{
	IntType,
	FloatType,
	DoubleType,
	CharType
} WrapperType;

#endif /* WRAPPERS_H */
