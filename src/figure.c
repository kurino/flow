/*
 *	figure.c
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 *
 */

#include "bool.h"
#include "xalloc.h"
#include "strlist.h"
#include "flowcom.h"
#include "figure.h"

/*
 *
 */

Figure	*allocFigure ( char *name, FlowCom *command, StrList *body ) {
	Figure	*ptr;

	if ( ( ptr = xalloc( Figure ) ) != NULL ) {
		ptr -> name = strdup ( name );
		ptr -> command = command;
		ptr -> body = body;
	}

	return ptr;
}

/*
 *
 */

void freeFigure ( Figure *fp ) {

	if ( fp != NULL )	{
		if ( fp -> name != NULL )	{
			xfree ( fp -> name );
		}
		if ( fp -> command != NULL )	{
			freeFlowCom ( fp -> command );
		}
		if ( fp -> body != NULL ) {
			freeStrList ( fp -> body );
		}
		xfree ( fp );
	}
}

/*
 *
 */

void	printFigure ( Figure *fp ) {

	if ( fp != NULL )	{
		printf ( "name=%s, flowcom=( ", fp -> name );
		printFlowCom ( fp -> command );
		printf ( " ), body=( " );
		printStrList ( fp -> body, ", " );
		printf ( " )" );
	}
}

/*
 *
 */
