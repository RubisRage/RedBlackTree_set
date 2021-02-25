#include <stdio.h> //DEBUG LIBRARY
#include <stdlib.h>
#include "private_treeset.h"


//STATIC FUNCTION DECLARATIONS
static void _remove_nodes(Node n, bool free_elements);
static Node _create_node(void* value);
static Node _bst_insertion(Node* root, cmpf_t cmp, void* e);
static void _restructure(TreeSet t, Node father);
static void _simple_rotation(TreeSet t, Node father, Node gf, bool leftcase);

void perrorx(const char* s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

/*
 * Creates a new TreeSet instance. 
 *
 * Arguments: 	cmp - Pointer refering the function used to 
 * 		compare the elements of the set. This
 *		function must have the following interface:
 *		int func(E,E) where E is the type of the 
 *		element. 
 *
 *		free_on_fail - Tells whether to free the passed
 * 		element on add fail. Mostly designed for type wrappers.
 */
TreeSet create_treeset(void* cmp, bool free_on_fail)
{
	TreeSet t = malloc(sizeof(_tree_set));
	if(t==NULL) perrorx("Not enough memory to create a new TreeSet. Aborting.");
	t->free_on_fail = free_on_fail;
	t->root = NULL;
	t->size = 0;
	t->cmp = (cmpf_t) cmp; 

	return t;
}


/*
 * Creates a new node initializated to contain the specified 
 * value.
 */
static Node _create_node(void* value)
{
	Node n = malloc(sizeof(_node));
	if(n==NULL) perrorx("Not enough memory to create a new node. Aborting.");
	n->father = NULL;
	n->sons[right] = n->sons[left] = NULL;
	n->color = RED;
	n->value = value;

	return n;
}

/*
 * Adds the element referenced by the passed pointer to this 
 * set if not already present, this function may modify the
 * tree's structure to maintain red-black trees properties.
 * Returns true if added, false other wise.
 */
bool set_add(TreeSet t, void* e)
{
	Node new = _bst_insertion(&t->root, t->cmp, e);
	if(new==NULL)
	{
		if(t->free_on_fail) free(e);
		return false;
	}

	if(new!=t->root && new->father->color==RED) _restructure(t, new);

	t->root->color = BLACK;
	t->size++;
	return true;
}


/*
 * Does the tree restructure to ensure that all properties are conserved and
 * thus kept in balance.
 */
static void _restructure(TreeSet t, Node son)
{
	char fcase;
	Node father = son->father;
	Node gf = father->father;
	//Store on fcase if father is right son(1) or left son(0)
	Node uncle = (fcase=(father==gf->sons[right]))? gf->sons[left]:gf->sons[right];

	if(uncle != NULL && uncle->color==RED)
	{
		father->color = uncle->color = BLACK;
		gf->color = RED;
		return;
	}

	/* Scase represents whether the son is his father's left/right son. It's value
	   equals one when son is right child. */
	char scase = (son==father->sons[right]);

	//if fcase != scase then it's left-right/right-left rotation case
	if(scase ^ fcase)
	{
		//Update successors
		father->sons[!(int)scase] = NULL;
		son->sons[(int)scase] = father;

		//Update predeccessors
		father->father = son;
		son->father = gf;

		_simple_rotation(t, son, gf, scase);
	}
	//simple left-left/right-right rotation case otherwise
	else
		_simple_rotation(t, father, gf, !scase);
}

/*
 * Performs a simple left-left or right-right rotation based on leftcase flag
 * value. This rotation consist of swapping father and grandfather positions 
 * in the structure where grandfather would then be father's left or right son
 * based on the kind of rotation. Father's and grandfather's colors are
 * interchanged.
 */
static void _simple_rotation(TreeSet t, Node father, Node gf, bool leftcase)
{
	
		//Swap colors
		father->color = BLACK;
		gf->color = RED;

		int branch = leftcase? left:right;

		//Perform rotation
		gf->sons[branch] = NULL;
		father->sons[!branch] = gf;

		//Get this subtree's root. It stays invariant after the transformation
		Node subroot = gf->father;

		//Update predecessors 
		father->father = subroot;
		gf->father = father;
		
		//Check if gf is root, needed to update father's predecessor.
		if(subroot==NULL)
			t->root = father;
		else
		{
			branch = subroot->sons[right]==gf? right:left;
			subroot->sons[branch] = father;
		}
}

/*
 * Implements basic binary search tree insertion. 
 */
static Node _bst_insertion(Node* root, cmpf_t cmp, void* e)
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
		current = next;
		c = cmp(current->value, e);

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


/*
 * Removes all elements from this set. If specified by the
 * free_elements flag the memory used by the elements is 
 * freed aswell.
 */
void set_clear(TreeSet t, bool free_elements)
{
	_remove_nodes(t->root, free_elements);
	t->root = NULL;
}

/*
 * Recursively removes every node from the tree. If
 * the free_elements flag is true then the memory 
 * allocated for the inserted values is also freed.
 */
static void _remove_nodes(Node n, bool free_elements)
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
	Node current = t->root;
	bool contained = false;

	while(current!=NULL && !contained)
	{
		int c = t->cmp(current->value, e);

		if(c > 0)
			current = current->sons[left];
		else if(c < 0)
			current = current->sons[right];
		else
			contained = true;
	}
	
	if(t->free_on_fail) 
		free(e);

	return contained;
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
	printf("color: %s (%ld) ", n->color==RED? "RED":"BLACK", (long)n);
	f(n->value);
	_apply(n->sons[right], f);
}

//TEMP DEBUG FUNCTIONS ---------------------------------
void apply(TreeSet t, void* f)
{
	_apply(t->root, (void (*)(void*)) f);
}
//------------------------------------------------------


