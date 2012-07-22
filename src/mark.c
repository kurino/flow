/*
 *	mark.c
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
 *
 */

#include "xalloc.h"
#include "coord.h"
#include "mark.h"

/*
 *
 */

Mark	*allocMark ( char *name, Coord *coord, int curDirec ) {
	Mark	*ptr;

	if ( ( ptr = xalloc( Mark ) ) != NULL ) {
		ptr -> name = strdup ( name );
		ptr -> coord = coord;
		ptr -> direc = curDirec;
	}

	return ptr;
}

/*
 *
 */

void freeMark ( Mark *mp ) {

	if ( mp != NULL )	{
		if ( mp -> name != NULL )	{
			xfree ( mp -> name );
		}
		if ( mp -> coord != NULL ) {
			freeCoord ( mp -> coord );
		}
		xfree ( mp );
	}
}

/*
 *
 */

void	printMark ( Mark *mp ) {

	if ( mp != NULL )	{
		printf ( "name=%s, coord=( ", mp -> name );
		printCoord ( mp -> coord );
		printf ( " )" );
	}
}

/*
 *
 */
