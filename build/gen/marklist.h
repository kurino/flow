/*
 * marklist.h
 */

#ifndef	_MARKLIST_H_
#define	_MARKLIST_H_	1

/*
 *	includes
 */

#include	"vlist.h"
#include	"mark.h"

/*
 *	constants
 */

#define	MarkList	VList

#define	freeMarkList(LP)			freeVList((VList *)(LP))
#define	findMarkList(LP,TARGET)	((Mark *)findVList((VList *)(LP),(void *)(TARGET)))
#define	printMarkList(LP,SEP)		printVList((VList *)(LP),SEP)
#define	popMarkList(LP)			((Mark *)popVList((VList *)(LP)))

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	MarkList	*allocMarkList ( void );
extern	MarkList	*insertMarkList ( MarkList *lp, Mark *value );
extern	MarkList	*appendMarkList ( MarkList *lp, Mark *value );

/*
 *
 */

#endif

/*
 *
 */

