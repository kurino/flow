/*
 *	vpair.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *	VPair
 *
 *		+-------+
 *		|	* --+---> src
 *		+-------+
 *		|	* --+---> dst
 *		+-------+
 *
 */

#include "xalloc.h"
#include "vpair.h"

/*
 *
 */

VPair	*allocVPair ( void *srcValue, void *dstValue ) {
	VPair	*ptr;

	if ( ( ptr = xalloc( VPair ) ) != NULL ) {
		ptr -> src = srcValue;
		ptr -> dst = dstValue;
	}

	return ptr;
}

/*
 *
 */

void	freeVPair ( VPair *cp, FreeFunc freeSrcFunc, FreeFunc freeDstFunc ) {

	if ( cp != NULL )	{
		if ( cp -> src != NULL && freeSrcFunc != NULL ) {
			freeSrcFunc ( cp -> src );
		}
		if ( cp -> dst != NULL && freeDstFunc != NULL ) {
			freeDstFunc ( cp -> dst );
		}
		xfree ( cp );
	}
}

/*
 *
 */

void	printVPair ( VPair *cp, PrintFunc printSrcFunc, PrintFunc printDstFunc ) {

	if ( cp != NULL )	{
		if ( cp -> src != NULL && printSrcFunc != NULL ) {
			printSrcFunc ( cp -> src );
		}
		if ( cp -> dst != NULL && printDstFunc != NULL ) {
			printDstFunc ( cp -> dst );
		}
	}
}

/*
 *
 */
