#include <stdbool.h>
#include <stddef.h>

/*
 * Type definition of a struct pointer encapsulating the set
 * structure.
 */
typedef struct _tree_set* TreeSet;

//TEMP DEBUG FUNCTIONS ---------------------------------
void apply(TreeSet, void*);
//------------------------------------------------------


/*
 * Creates a new TreeSet instance. 
 *
 * Arguments: 	cmp - Pointer refering the function used to 
 * 		used to compare the elements of the set. This
 *		function must have the following interface:
 *		int func(E,E) where E is the type of the 
 *		element. 
 */
TreeSet create_treeset(void* cmp);


/*
 * Adds the element referenced by the passed pointer to this 
 * set if not already present. Returns true if added, false
 * other wise.
 */
bool set_add(TreeSet, void*);



/*
 * Removes all elements from this set. If specified by the 
 * free_elements flag the memory used by the elements is 
 * freed aswell.
 */
void set_clear(TreeSet, bool free_elements);


/*
 * Checks for the presence of the specified element. The cmp 
 * function is used to check for equality. Returns true if 
 * contained, false otherwise.
 */
bool set_contains(TreeSet,void*);


/*
 * Checks if the specified set is empty. Returns true if 
 * it contains no elements, false otherwise.
 */
bool set_is_empty(TreeSet);


/*
 * Returns the number of elements in this set.
 */
size_t set_size(TreeSet);


/*
 * Frees this treeset memory and all of its depencencies except 
 * the elements contained unless specified otherwise by the 
 * free_elements flag.
 */
void set_destroy(TreeSet, bool free_elements); 














