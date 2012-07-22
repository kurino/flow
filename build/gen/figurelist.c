/*
 *	figurelist.c
 */

#include <string.h>

/*
 *
 */

#include "vfunc.h"
#include "vlist.h"
#include "figure.h"
#include "figurelist.h"

/*
 *
 */

FigureList	*insertFigureList ( FigureList *lp, Figure *value ) {

	if ( value != NULL ) {
		return (FigureList *) insertVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

FigureList	*appendFigureList ( FigureList *lp, Figure *value ) {

	if ( value != NULL ) {
		return (FigureList *) appendVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

static	void	freeFigureFunc ( void *p ) {

	freeFigure ( (Figure *)p );
}

static	void	printFigureFunc ( void *p ) {

	printFigure( (Figure *)p );
}

static	int	compareFigureFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, ((Figure *)q) -> name );
}

/*
 *
 */

static	VFunc	*table = NULL;

/*
 *
 */

FigureList	*allocFigureList ( void ) {

	if ( table == NULL ) {
		table = allocVFunc ( freeFigureFunc, printFigureFunc, compareFigureFunc );
	}

	if ( table != NULL ) {
		return (FigureList *) allocVList ( table );
	}

	return NULL;

}

/*
 *
 */
