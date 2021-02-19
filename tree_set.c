#include <stdio.h> //DEBUG LIBRARY
#include <stdlib.h>
#include "tree_set.h"


/*
 * Node color type definition. Designed to be used in combination
 * with the negation operator(!): RED = !BLACK <=> BLACK = !RED.
 */
typedef unsigned char color_t;
static const color_t RED = 0;
//static const color_t BLACK = 1; //NOT IN USE YET


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


//PRIVATE FUNCTION DECLARATIONS
void _remove_nodes(Node n, bool free_elements);
bool _set_contains(Node n, cmpf_t cmp, void* e); 
bool _set_add(Node, cmpf_t, void*);
Node _create_node(void* value);
Node _bst_insertion(Node* root, cmpf_t cmp, void* e);


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
	n->father = NULL;
	n->sons[right] = n->sons[left] = NULL;
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
	if(_bst_insertion(&t->root, t->cmp, e)==NULL)
		return false;
	return true;
}

Node _bst_insertion(Node* root, cmpf_t cmp, void* e)
{
	if(*root==NULL)
	{
		*root = _create_node(e);
		return *root;
	}

	Node next = *root, current;
	int c;

	while(next!=NULL)
	{
		c = cmp(next->value, e);
		current = next;

		if(c>0)
			next = next->sons[left];
		else if(c<0)
			next = next->sons[right];
		else
			return NULL;

	} 

	Node new = _create_node(e);
	new->father = current;
	current->sons[c>0] = new;
	
	return new;
}

bool _set_add(Node n, cmpf_t cmp, void* e)
{
	return false;
}

/*
 * Removes all elements from this set. If specified by the
 * free_elements flag the memory used by the elements is 
 * freed aswell.
 */
void set_clear(TreeSet t, bool free_elements)
{
	_remove_nodes(t->root, free_elements);
}


void _remove_nodes(Node n, bool free_elements)
{
	if(n==NULL) return;

	_remove_nodes(n->sons[left], free_elements);
	_remove_nodes(n->sons[right], free_elements);
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


/*
 * Checks for the presence of the specified element. The cmp 
 * function is used to check for equality. Returns true if 
 * contained, false otherwise.
 */
bool _set_contains(Node n, cmpf_t cmp, void* e)
{
	if(n==NULL) 
		return false;
	else if(cmp(n->value, e)==0)
		return true;
	
	return _set_contains(n->sons[left], cmp, e) 
	    	|| _set_contains(n->sons[right], cmp, e);
}


/*
 * Checks if the specified set is empty. Returns true if 
 * it contains no elements, false otherwise.
 */
bool set_is_empty(TreeSet t)
{
	return t->root==NULL;
}


/*
 * Checks if the specified set is empty. Returns true if 
 * it contains no elements, false otherwise.
 */
size_t set_size(TreeSet t)
{
	return t->size;
}


/*
 * Frees this treeset memory and all of its depencencies except 
 * the elements contained unless specified otherwise by the 
 * free_elements flag.
 */
void set_destroy(TreeSet t, bool free_elements)
{
	_remove_nodes(t->root, free_elements);
	free(t);
}

void _apply(Node n, void (*f)(void*))
{
	if(n==NULL) return;

	_apply(n->sons[left], f);
	f(n->value);
	_apply(n->sons[right], f);
}

//TEMP DEBUG FUNCTIONS ---------------------------------
void apply(TreeSet t, void* f)
{
	_apply(t->root, (void (*)(void*)) f);
}
//------------------------------------------------------



















