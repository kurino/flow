/*
 *	vcell.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *	VCell
 *
 *		+-------+
 *		|	* --+---> next
 *		+-------+
 *		|	*	|
 *		+---+---+
 *			|
 *			v
 *		  value
 *
 */

#include "xalloc.h"
#include "vfunc.h"
#include "vcell.h"

/*
 *
 */

VCell	*allocVCell ( void *value ) {
	VCell	*ptr;

	if ( ( ptr = xalloc( VCell ) ) != NULL ) {
		ptr -> next = NULL;
		ptr -> value = value;
	}

	return ptr;
}

/*
 *
 */

void	applyVCell ( VCell *cp, ApplyFunc applyFunc ) {

	if ( cp != NULL )	{
		if ( cp -> value != NULL && applyFunc != NULL ) {
			applyFunc ( cp -> value );
		}
	}
}

/*
 *
 */

void	freeVCell ( VCell *cp, FreeFunc freeFunc ) {

	if ( cp != NULL )	{
		applyVCell ( cp, freeFunc );
		xfree ( cp );
	}
}

/*
 *
 */

void	printVCell ( VCell *cp, PrintFunc printFunc ) {

	applyVCell ( cp, printFunc );

}

/*
 *
 */
