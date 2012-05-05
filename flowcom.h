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

typedef struct {
	char		*name;
	int			params;
	Coord		size;
	Bool		hasText;
	TheCommands	command;
} FlowCom;

/*
 *	externs
 */

/*
 *
 */

#endif

/*
 *
 */

