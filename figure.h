/*
 * figure.h
 */

#ifndef	_FIGURE_H_
#define	_FIGURE_H_	1

/*
 *	includes
 */

#include "bool.h"
#include "strlist.h"
#include "flowcom.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	{
	char	*name;
	FlowCom	*command;
	StrList	*body;
} Figure;

/*
 *	externs
 */

extern	Figure	*allocFigure ( char *name, FlowCom *command, StrList *body );
extern	void	freeFigure ( Figure *fp );
extern	void	printFigure ( Figure *fp );

/*
 *
 */

#endif

/*
 *
 */

