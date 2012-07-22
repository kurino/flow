/*
 *	macrolist.c
 */

#include <string.h>

/*
 *
 */

#include "vfunc.h"
#include "vlist.h"
#include "macro.h"
#include "macrolist.h"

/*
 *
 */

MacroList	*insertMacroList ( MacroList *lp, Macro *value ) {

	if ( value != NULL ) {
		return (MacroList *) insertVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

MacroList	*appendMacroList ( MacroList *lp, Macro *value ) {

	if ( value != NULL ) {
		return (MacroList *) appendVList ( (VList *)lp, (void *)value );
	}

	return NULL;
}

/*
 *
 */

static	void	freeMacroFunc ( void *p ) {

	freeMacro ( (Macro *)p );
}

static	void	printMacroFunc ( void *p ) {

	printMacro( (Macro *)p );
}

static	int	compareMacroFunc ( void *p, void *q ) {

	return strcmp ( (char *)p, ((Macro *)q) -> name );
}

/*
 *
 */

static	VFunc	*table = NULL;

/*
 *
 */

MacroList	*allocMacroList ( void ) {

	if ( table == NULL ) {
		table = allocVFunc ( freeMacroFunc, printMacroFunc, compareMacroFunc );
	}

	if ( table != NULL ) {
		return (MacroList *) allocVList ( table );
	}

	return NULL;

}

/*
 *
 */
