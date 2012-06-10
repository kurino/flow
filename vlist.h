/*
 * vlist.h
 */

#ifndef	_VLIST_H_
#define	_VLIST_H_	1

/*
 *	includes
 */

#include "vcell.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	vlist	{
	VCell	*top;
	VCell	*tail;
} VList;

/*
 *	externs
 */

extern	VList	*allocVList ( void );
extern	void	freeVList ( VList *lp, void (*freeFunc)( void * ) );
extern	VList	*insertVList ( VList *lp, void *value );
extern	VList	*appendVList ( VList *lp, void *value );
extern	void	*findVList ( VList *lp, void *target, int (*compFunc)(void *, void *) );
extern	void	printVList ( VList *lp, void (*printFunc)(void *), char *sep );

/*
 *
 */

extern	void	*popVList ( VList *lp );	/* remove top value */

/*
 *
 */

#endif

/*
 *
 */

