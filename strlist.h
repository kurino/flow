/*
 * strlist.h
 */

#ifndef	_STRLIST_H_
#define	_STRLIST_H_	1

/*
 *	includes
 */

#include "vcell.h"
#include "vlist.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	VList	StrList;

/*
 *	externs
 */

StrList	*allocStrList ( void );
void	freeStrList ( StrList *lp );
StrList	*insertStrList ( StrList *lp, char *line );
StrList	*appendStrList ( StrList *lp, char *line );
char	*findStrList ( StrList *lp, char *target );
void	printStrList ( StrList *lp, char *sep );

/*
 *
 */

#endif

/*
 *
 */

