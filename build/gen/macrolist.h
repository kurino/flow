/*
 * macrolist.h
 */

#ifndef	_MACROLIST_H_
#define	_MACROLIST_H_	1

/*
 *	includes
 */

#include	"vlist.h"
#include	"macro.h"

/*
 *	constants
 */

#define	MacroList	VList

#define	freeMacroList(LP)			freeVList((VList *)(LP))
#define	findMacroList(LP,TARGET)	((Macro *)findVList((VList *)(LP),(void *)(TARGET)))
#define	printMacroList(LP,SEP)		printVList((VList *)(LP),SEP)
#define	popMacroList(LP)			((Macro *)popVList((VList *)(LP)))

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	MacroList	*allocMacroList ( void );
extern	MacroList	*insertMacroList ( MacroList *lp, Macro *value );
extern	MacroList	*appendMacroList ( MacroList *lp, Macro *value );

/*
 *
 */

#endif

/*
 *
 */

