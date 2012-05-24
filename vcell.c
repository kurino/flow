/*
 *	vcell.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "xalloc.h"
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

void	freeVCell ( VCell *cp, void (*freeFunc)( void * ) ) {

	if ( cp != NULL )	{
	  if ( cp -> value != NULL && freeFunc != NULL ) {
		freeFunc ( cp -> value );
	  }
	  xfree ( cp );
	}
}

/*
 *
 */

void	printVCell ( VCell *cp, void (*printFunc)( void * ) ) {

	if ( cp != NULL )	{
		if ( cp -> value != NULL && printFunc != NULL ) {
			printFunc ( cp -> value );
		}
	}
}

/*
 *
 */
