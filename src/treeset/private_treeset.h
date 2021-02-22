#ifndef PRIVATE_TREESET_H
#define PRIVATE_TREESET_H

#include "tree_set.h"

/*
 * Node color type definition. Designed to be used in combination
 * with the negation operator(!): RED = !BLACK <=> BLACK = !RED.
 */
typedef unsigned char color_t;
static const color_t RED = 0;
static const color_t BLACK = 1; 


/*
 * Compare function type definition. This function must accept 
 * two arguments of the stored type and return an integer greater
 * than, equal to or lower than 0 if, respectively, the argument 
 * item is greater than, equal to or lower than the second argument.
 */
typedef int (*cmpf_t)(void*,void*);

/*
 * Data collection representing a tree node. Every node holds a 
 * pointer to the data that is containing as well as its own color
 * which is either RED(0) or BLACK(1).
 */
typedef struct _node
{
	void* value;
	color_t color;
	struct _node* father;
	struct _node* sons[2];
} _node; 

//Convenience type definition for struct _node pointer operations.
typedef _node* Node;

/* Left and right node sons indexes. Elegido por el tema de generar
 * los indices adecuadamente al realizar las comparaciones.
 */
static const int right = 0;
static const int left  = 1;

/*
 * Data collection representing the tree structure. It holds a
 * pointer to the root node and to the cmp function used to 
 * sort the elements.
 */
typedef struct _tree_set
{
	Node root;
	size_t size;
	cmpf_t cmp;
	//bool primitive_set; //NOT YET USED
} _tree_set;

#endif /* PRIVATE_TREESET_H */















