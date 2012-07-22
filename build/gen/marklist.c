/*
 *	marklist.c
 */

#include <string.h>

/*
 *
 */

#include "vfunc.h"
#include "vlist.h"
#include "mark.h"
#include "marklist.h"

/*
 *
 */

MarkList	*insertMarkList ( MarkList *lp, Mark *value ) {

	if ( value != NULL ) {
		return (MarkList *) insertVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

MarkList	*appendMarkList ( MarkList *lp, Mark *value ) {

	if ( value != NULL ) {
		return (MarkList *) appendVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

static	void	freeMarkFunc ( void *p ) {

	freeMark ( (Mark *)p );
}

static	void	printMarkFunc ( void *p ) {

	printMark( (Mark *)p );
}

static	int	compareMarkFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, ((Mark *)q) -> name );
}

/*
 *
 */

static	VFunc	*table = NULL;

/*
 *
 */

MarkList	*allocMarkList ( void ) {

	if ( table == NULL ) {
		table = allocVFunc ( freeMarkFunc, printMarkFunc, compareMarkFunc );
	}

	if ( table != NULL ) {
		return (MarkList *) allocVList ( table );
	}

	return NULL;

}

/*
 *
 */
