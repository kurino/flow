/*
 * vlist.h
 */

#ifndef	_VLIST_H_
#define	_VLIST_H_	1

/*
 *	includes
 */

#include "vfunc.h"
#include "vcell.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	vlist	{
	VFunc	*table;
	VCell	*top;
	VCell	*tail;
} VList;

/*
 *	externs
 */

extern	VList	*allocVList ( VFunc *funcTable );
extern	void	freeVList ( VList *lp );
extern	VList	*insertVList ( VList *lp, void *value );
extern	VList	*appendVList ( VList *lp, void *value );
extern	void	*findVList ( VList *lp, void *target );
extern	void	printVList ( VList *lp, char *sep );

/*
 *	for Stack
 */

extern	int		isEmptyVList ( VList *lp );
extern	void	*popVList ( VList *lp );	/* remove top value */

/*
 *
 */

#endif

/*
 *
 */
