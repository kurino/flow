/*
 *	vfunc.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "xalloc.h"
#include "vfunc.h"

/*
 *
 */

VFunc	*allocVFunc (
					FreeFunc freeFunc,
					PrintFunc printFunc,
					CompareFunc compareFunc
						 )	{
	VFunc	*ptr;

	if ( ( ptr = xalloc( VFunc ) ) != NULL ) {
		ptr -> free = freeFunc;
		ptr -> print = printFunc;
		ptr -> compare = compareFunc;
	}

	return ptr;
}

/*
 *
 */

void	freeVfunc ( VFunc *cp ) {

	if ( cp != NULL )	{
		xfree ( cp );
	}
}

/*
 *
 */
