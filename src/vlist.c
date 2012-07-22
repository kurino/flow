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
#include "vfunc.h"
#include "vcell.h"
#include "vlist.h"

/*
 *
 *	VList
 *				  VCell
 *		 		+-------+	+-------+		+-------+
 *				|	* --+-->|	* --+- .. ->|	* --+--> NULL
 *				+-------+	+-------+		+-------+
 *				|		|	|		|		|		|
 *				+-------+	+-------+		+-------+
 *					^							^
 *					|							|
 *		+-------+	| top						| tail
 *		|	* --+---+							|
 *		+-------+								|
 *		|	* --+-------------------------------+
 *		+-------+
 *
 */

/*
 *
 */

VList	*allocVList ( VFunc *funcTable ) {
	VList	*ptr;

	if ( ( ptr = xalloc( VList ) ) != NULL ) {
		ptr -> table = funcTable;
		ptr -> top = NULL;
		ptr -> tail = NULL;
	}

	return ptr;
}

/*
 *
 */

void	freeVList ( VList *lp ) {

	if ( lp != NULL ) {
		if ( lp -> table != NULL )	{
			FreeFunc freeFunc = lp -> table -> free;

			if ( freeFunc != NULL ) {
				VCell	*cp;
				VCell	*np;

				for ( cp = lp -> top; cp != NULL; cp = np ) {
					np = cp -> next;
					freeVCell ( cp, freeFunc );
				}
			}
		}

		xfree ( lp );
	}

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

void	*findVList ( VList *lp, void *target ) {

	if ( lp != NULL ) {
		if ( lp -> table != NULL )	{
			CompareFunc compFunc = lp -> table -> compare;

			if ( compFunc != NULL ) {
				VCell	*cp;

				for ( cp = lp -> top; cp != NULL; cp = cp -> next ) {
					if ( !compFunc ( target, cp -> value ) ) {
						return cp -> value;
					}
				}
			}
		}
	}

	return NULL;
}

/*
 *
 */

void	printVList ( VList *lp, char *sep ) {

	if ( lp != NULL ) {
		if ( lp -> table != NULL )	{
			PrintFunc printFunc = lp -> table -> print;

			if ( printFunc != NULL ) {
				int		first = TRUE;
				VCell	*cp;

				for ( cp = lp -> top; cp != NULL; cp = cp -> next ) {
					if ( !first && sep != NULL ) {
						printf ( "%s", sep );
					}

					printVCell ( cp, printFunc );
					first = FALSE;
				}
			}
		}
	}
}

/*
 *
 */

int		isEmptyVList ( VList *lp ) {

	return lp -> top == NULL;
}

/*
 *
 */

void	*popVList ( VList *lp ) {
	void	*value = NULL;

	if ( lp != NULL ) {
		VCell	*cp = lp -> top;

		if ( cp != NULL ) {
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
