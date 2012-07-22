/*
 * argument.h
 */

#ifndef	_ARGUMENT_H_
#define	_ARGUMENT_H_	1

/*
 *	includes
 */

#include "strlist.h"

/*
 *	constants
 */

#define	ARG_LINE	1024
#define	FORMAT_CHAR	'%'

/*
 *	typedefs
 */

typedef	struct	{
  int argc;
  char **argv;
  StrList *argb;
} Argument;

/*
 *	externs
 */

extern	Argument	*allocArgument ( char *line );
extern	void		freeArgument ( Argument *agp );
extern	void		printArgument ( Argument *agp, char *sep );
extern	char		*assingArgument ( char *buf, char *src, Argument *agp );

/*
 *
 */

#endif

/*
 *
 */
