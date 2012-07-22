/*
 *	flowcom.c
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 *
 */

#include "xalloc.h"
#include "bool.h"
#include "coord.h"
#include "thecommands.h"
#include "flowcom.h"

/*
 *
 */

FlowCom	*allocFlowCom ( char *name, int params, Coord size, Bool hasText, TheCommands command ) {
	FlowCom	*ptr;

	if ( ( ptr = xalloc( FlowCom ) ) != NULL ) {
		ptr -> name = strdup ( name );
		ptr -> params = params;
		ptr -> hasText = hasText;
		ptr -> size = size;
		ptr -> command = command;
	}

	return ptr;
}

/*
 *
 */

void freeFlowCom ( FlowCom *fp ) {

	if ( fp != NULL )	{
		if ( fp -> name != NULL )	{
			xfree ( fp -> name );
		}
		xfree ( fp );
	}
}

/*
 *
 */

void	printFlowCom ( FlowCom *fp ) {

	if ( fp != NULL )	{
		printf ( "name=%s, params=%d, ",
				fp -> name,
				fp -> params );
		printCoord ( &fp -> size );
		printf ( ", hasText=%s", bool2str(fp->hasText) );
	}
}

/*
 *
 */
