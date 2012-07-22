/*
 *	coord.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "xalloc.h"
#include "coord.h"

/*
 *
 */

Coord	*allocCoord ( double x, double y ) {
	Coord	*ptr;

	if ( ( ptr = xalloc( Coord ) ) != NULL ) {
		ptr -> x = x;
		ptr -> y = y;
	}

	return ptr;
}

/*
 *
 */

void freeCoord ( Coord *cp ) {

	if ( cp != NULL )	{
		xfree ( cp );
	}
}

/*
 *
 */

void	printCoord ( Coord *cp ) {

	if ( cp != NULL )	{
		printf ( "(%f,%f)", cp -> x, cp -> y );
	}
}

/*
 *
 */
