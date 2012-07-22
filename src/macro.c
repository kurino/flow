/*
 *	macro.c
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 *
 */

#include "xalloc.h"
#include "strlist.h"
#include "macro.h"

/*
 *
 */

Macro	*allocMacro ( char *name, int argc, StrList *body ) {
	Macro	*ptr;

	if ( ( ptr = xalloc( Macro ) ) != NULL ) {
		ptr -> name = strdup ( name );
		ptr -> argc = argc;
		ptr -> body = body;
	}

	return ptr;
}

/*
 *
 */

void freeMacro ( Macro *fp ) {

	if ( fp != NULL )	{
		if ( fp -> name != NULL )	{
			xfree ( fp -> name );
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

void	printMacro ( Macro *fp ) {

	if ( fp != NULL )	{
		printf ( "name=%s, argc = %d, body=( ", fp -> name, fp -> argc );
		printStrList ( fp -> body, ", " );
		printf ( " )" );
	}
}

/*
 *
 */
