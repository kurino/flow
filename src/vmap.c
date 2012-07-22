/*
 *	vmap.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *	VMap
 *
 *		+-------+
 *		|	* --+---> src
 *		+-------+
 *		|	* --+---> dst
 *		+-------+
 *
 */

#include "xalloc.h"
#include "vfunc.h"
#include "vpair.h"
#include "vlist.h"
#include "vmap.h"

/*
 *
 */

extern	VMap	*allocVMap ( VFunc *srcFunc, VFunc *dstFunc ) {
	VMap	*ptr;
	VList	*listPtr;

	if ( ( listPtr = allocVList() ) ) != NULL ) {
		if ( ( ptr = xalloc( VMap ) ) != NULL ) {
			ptr -> srcFunc = srcFunc;
			ptr -> dstFunc = dstFunc;
			ptr -> list = listPtr;

			return ptr;
		}
		freeVList ( listPtr );
	}

	return NULL;
}

/*
 *
 */

static	void	applyFreeFunction ( void *ptr, void (*freeFunc)(void *) ) {

	if ( ptr != NULL & freeFunc != NULL ) {
		freeFunc ( ptr );
	}

}

static	void	freeVPairValues ( VPair *vpp,
								  void (*freeSrcFunc)(void *),
								  void (*freeDstFunc)(void *) ) {

	applyFreeFunction ( vpp -> src, freeSrcFunc );
	applyFreeFunction ( vpp -> dst, freeDstFunc );

}

void	freeVMap ( VMap *cp ) {

	if ( cp != NULL )	{
		xfree ( cp );
	}
}

/*
 *
 */

void	printVMap ( VMap *cp, void (*printSrcFunc)( void * ), void (*printDstFunc)( void * ) ) {

	if ( cp != NULL )	{
		if ( cp -> src != NULL && printSrcFunc != NULL ) {
			printSrcFunc ( cp -> src );
		}
		if ( cp -> dst != NULL && printDstFunc != NULL ) {
			printDstFunc ( cp -> dst );
		}
		xfree ( cp );
	}
}

/*
 *
 */
