/*
 * macro.h
 */

#ifndef	_MACRO_H_
#define	_MACRO_H_	1

/*
 *	includes
 */

#include "strlist.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	{
	char	*name;
	int		argc;
	StrList	*body;
} Macro;

/*
 *	externs
 */

extern	Macro	*allocMacro ( char *name, int argc, StrList *body );
extern	void	freeMacro ( Macro *fp );
extern	void	printMacro ( Macro *fp );

/*
 *
 */

#endif

/*
 *
 */

