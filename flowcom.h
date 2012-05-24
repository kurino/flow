/*
 * flowcom.h
 */

#ifndef	_FLOWCOM_H_
#define	_FLOWCOM_H_	1

/*
 *	includes
 */

#include "bool.h"
#include "coord.h"
#include "thecommands.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef struct flowcom	{
	char		*name;		/* name of command */
	int			params;		/* number of params ( not used ? ) */
	Coord		size;		/* size of figure */
	Bool		hasText;	/* Does it have text argument ? */
	TheCommands	command;	/* code of command */
} FlowCom;

/*
 *	externs
 */

extern	FlowCom	*allocFlowCom ( char *name, int params, Coord size, Bool hasText, TheCommands command );
extern	void	freeFlowCom ( FlowCom *fp );
extern	void	printFlowCom ( FlowCom *fp );

/*
 *
 */

#endif

/*
 *
 */

