/*
 * figurelist.h
 */

#ifndef	_FIGURELIST_H_
#define	_FIGURELIST_H_	1

/*
 *	includes
 */

#include	"vlist.h"
#include	"figure.h"

/*
 *	constants
 */

#define	FigureList	VList

#define	freeFigureList(LP)			freeVList((VList *)(LP))
#define	findFigureList(LP,TARGET)	((Figure *)findVList((VList *)(LP),(void *)(TARGET)))
#define	printFigureList(LP,SEP)		printVList((VList *)(LP),SEP)
#define	popFigureList(LP)			((Figure *)popVList((VList *)(LP)))

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	FigureList	*allocFigureList ( void );
extern	FigureList	*insertFigureList ( FigureList *lp, Figure *value );
extern	FigureList	*appendFigureList ( FigureList *lp, Figure *value );

/*
 *
 */

#endif

/*
 *
 */

