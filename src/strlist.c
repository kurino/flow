/*
 *	strlist.c
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 *
 */

#include "vfunc.h"
#include "vlist.h"
#include "strlist.h"

/*
 *
 */

StrList	*insertStrList ( StrList *lp, char *line ) {
	char *value = strdup ( line );

	if ( value != NULL ) {
		return (StrList *) insertVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

StrList	*appendStrList ( StrList *lp, char *line ) {
	char *value = strdup ( line );

	if ( value != NULL ) {
		return (StrList *) appendVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

void	removeTopStrList ( StrList *lp ) {
	char *str = popStrList ( lp );	

	if ( str != NULL ) {
		free ( str );
	}
}

/*
 *
 */

static	void	printStrFunc ( void *p ) {

  printf ( "%s", (char *)p );
}

static	int	compareStrFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, (char *)q );
}

/*
 *
 */

static	VFunc	*table = NULL;

/*
 *
 */

StrList	*allocStrList ( void ) {

	if ( table == NULL ) {
		table = allocVFunc ( free, printStrFunc, compareStrFunc );
	}

	if ( table != NULL ) {
		return (StrList *) allocVList( table );
	}

	return NULL;
}

/*
 *
 */
