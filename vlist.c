/*
 *	vlist.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "bool.h"
#include "xalloc.h"
#include "vcell.h"
#include "vlist.h"

/*
 *
 */

VList	*allocVList ( void ) {
	VList	*ptr;

	if ( ( ptr = xalloc( VList ) ) != NULL ) {
	  ptr -> top = NULL;
	  ptr -> tail = NULL;
	}

	return ptr;
}

/*
 *
 */

void	freeVList ( VList *lp, void (*freeFunc)( void * ) ) {
	VCell	*cp;
	VCell	*np;

	if ( lp != NULL ) {
		for ( cp = lp -> top; cp != NULL; cp = np ) {
			np = cp -> next;
			freeVCell ( cp, freeFunc );
		}
		xfree ( lp );
	}

}

/*
 *
 */

void	*popVList ( VList *lp ) {
	VCell	*cp;
	void	*value = NULL;

	if ( lp != NULL ) {
		if ( ( cp = lp -> top ) != NULL ) {
			value = cp -> value;
			if ( ( lp -> top = cp -> next ) == NULL ) {
				lp -> tail = NULL;
			}
			xfree ( cp );
		}
	}

	return value;
}

/*
 *
 */

VList	*insertVList ( VList *lp, void *value ) {
	VCell	*cp = allocVCell ( value );

	if ( cp == NULL ) {
		return NULL;
	}

	cp -> next = lp -> top;
	lp -> top = cp;

	if ( lp -> tail == NULL ) {
		lp -> tail = cp;
	}

	return lp;
}

/*
 *
 */

VList	*appendVList ( VList *lp, void *value ) {
	VCell	*cp = allocVCell ( value );

	if ( cp == NULL ) {
		return NULL;
	}

	if ( lp -> tail == NULL ) {
		lp -> top = cp;
	} else {
		lp -> tail -> next = cp;
	}

	lp -> tail = cp;
	cp -> next = NULL;

	return lp;
}

/*
 *
 */

void	*findVList ( VList *lp, void *target, int (*compFunc)(void *, void *) ) {
	VCell	*cp;

	for ( cp = lp -> top; cp != NULL; cp = cp -> next ) {
		if ( !compFunc ( target, cp -> value ) ) {
			return cp -> value;
		}
	}

	return NULL;
}

/*
 *
 */

void	printVList ( VList *lp, void (*printFunc)(void *), char *sep ) {
	VCell	*cp;
	int		first = TRUE;

	if ( printFunc != NULL ) {
		for ( cp = lp -> top; cp != NULL; cp = cp -> next ) {
			if ( !first && sep != NULL ) {
				printf ( "%s", sep );
			}
			printVCell ( cp, printFunc );
			first = FALSE;
		}
	}
}

/*
 *
 */
