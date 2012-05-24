/*
 *	strlist.c
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 *
 */

#include "vlist.h"
#include "strlist.h"

/*
 *
 */

StrList	*allocStrList ( void ) {

  return (StrList *) allocVList();
}

/*
 *
 */

void	freeStrList ( StrList *lp ) {

	freeVList ( (VList *)lp, free );
}


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

static	int	compareStrFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, (char *)q );
}

char	*findStrList ( StrList *lp, char *target ) {

  return (char *)findVList ( (VList *)lp, (void *)target, compareStrFunc );
}

/*
 *
 */

static	void	printStrFunc ( void *p ) {

  printf ( "%s", (char *)p );
}

void	printStrList ( StrList *lp, char *sep ) {

	printVList ( (VList *)lp, printStrFunc, sep );
}

/*
 *
 */
