#include <stdlib.h>
#include "tree_set.h"

typedef unsigned char color_t;
const color_t RED = 0;
const color_t BLACK = 1;

typedef int (*cmpf_t)(void*,void*);

typedef struct _node
{
	void* value;
	color_t color;
	struct _node* right;
	struct _node* left;
} _node; 

typedef _node* Node;

typedef struct _tree_set
{
	Node root;
	size_t size;
	cmpf_t cmp;
	bool primitive_set;
} _tree_set;

//PRIVATE FUNCTION DECLARATIONS
void _remove_nodes(Node n, bool free_elements);
bool _set_contains(Node n, cmpf_t cmp, void* e); 
bool _set_add(Node, void*);

/*
 * Creates a new TreeSet instance. 
 *
 * Arguments: 	cmp - Pointer refering the function used to 
 * 		used to compare the elements of the set. This
 *		function must have the following interface:
 *		int func(E,E) where E is the type of the 
 *		element. 
 */
TreeSet create_treeset(void* cmp)
{
	TreeSet t = malloc(sizeof(_tree_set));
	t->root = NULL;
	t->size = 0;
	t->cmp = (cmpf_t) cmp; 

	return t;
}


/*
 * Creates a new node initializated to contain the specified 
 * value.
 */
Node _create_node(void* value)
{
	Node n = malloc(sizeof(_node));
	n->right = n->left = NULL;
	n->color = RED;
	n->value = value;

	return n;
}

/*
 * Adds the element referenced by the passed pointer to this 
 * set if not already present. Returns true if added, false
 * other wise.
 */
bool set_add(TreeSet t, void* e)
{
	return _set_add(t->root, e);
}


/*
 * Removes all elements from this set.
 */
void set_clear(TreeSet t, bool free_elements)
{
	_remove_nodes(t->root, free_elements);
}

void _remove_nodes(Node n, bool free_elements)
{
	if(n==NULL) return;

	_remove_nodes(n->left, free_elements);
	_remove_nodes(n->right, free_elements);
	if(free_elements) free(n->value);
	free(n);
}


/*
 * Removes all elements from this set. If specified by the 
 * free_elements flag the memory used by the elements is 
 * freed aswell.
 */
bool set_contains(TreeSet t, void* e)
{
	return _set_contains(t->root, t->cmp, e);
}

bool _set_contains(Node n, cmpf_t cmp, void* e)
{
	if(n==NULL) 
		return false;
	else if(cmp(n->value, e)==0)
		return true;
	
	return _set_contains(n->left, cmp, e) 
	    	|| _set_contains(n->right, cmp, e);
}

bool set_is_empty(TreeSet t)
{
	return t->root==NULL;
}

size_t set_size(TreeSet t)
{
	return t->size;
}


void set_destroy(TreeSet t, bool free_elements)
{
	_remove_nodes(t->root, free_elements);
	free(t);
}





















