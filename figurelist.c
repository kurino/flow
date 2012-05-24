/*
 *	figurelist.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "vlist.h"
#include "figure.h"
#include "figurelist.h"

/*
 *
 */

FigureList	*allocFigureList ( void ) {

  return (FigureList *) allocVList();
}

/*
 *
 */

static void freeFigureFunc ( void *p ) {

	freeFigure ( (Figure *) p );
}

void	freeFigureList ( FigureList *lp ) {

	freeVList ( (VList *)lp, freeFigureFunc );
}


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

static	int	compareFigureFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, ((Figure *)q) -> name );
}

Figure	*findFigureList ( FigureList *lp, char *target ) {

	return (Figure *)findVList ( (VList *)lp, (void *)target, compareFigureFunc );
}

/*
 *
 */

static	void	printFigureFunc ( void *p ) {

	printFigure( (Figure *)p );
}

void	printFigureList ( FigureList *lp, char *sep )	{

	printVList ( (VList *)lp, printFigureFunc, sep );
}

/*
 *
 */

