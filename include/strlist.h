/*
 * strlist.h
 */

#ifndef	_STRLIST_H_
#define	_STRLIST_H_	1

/*
 *	includes
 */

#include "vlist.h"

/*
 *	constants
 */

#define	StrList	VList

#define	freeStrList(LP)			freeVList((VList *)(LP))
#define	findStrList(LP,TARGET) ((char *)findVList((VList *)(LP),(void *)(TARGET)))
#define	printStrList(LP,SEP)	printVList((VList *)(LP),SEP)
#define	popStrList(LP)			((char *)popVList((VList *)(LP)))

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	StrList	*allocStrList ( void );
extern	StrList	*insertStrList ( StrList *lp, char *line );
extern	StrList	*appendStrList ( StrList *lp, char *line );

/*
 *
 */

extern	void	removeTopStrList ( StrList *lp );

/*
 *
 */

#endif

/*
 *
 */

