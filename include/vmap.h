/*
 * vmap.h
 */

#ifndef	_VMAP_H_
#define	_VMAP_H_	1

/*
 *	includes
 */

#include "vpair.h"
#include "vfunc.h"
#include "vlist.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	vmap	{
	VFunc	*srcFunc;
	VFunc	*dstFunc;
	VList	*list;
} VMap;

/*
 *	externs
 */

extern	VMap	*allocVMap ( VFunc *srcFunc, VFunc *dstFunc );
extern	void	freeVMap ( VMap *cp );
extern	void	printVMap ( VMap *cp );

/*
 *
 */

#endif

/*
 *
 */

