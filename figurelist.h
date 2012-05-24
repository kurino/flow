/*
 * figurelist.h
 */

#ifndef	_FIGURELIST_H_
#define	_FIGURELIST_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	VList	FigureList;

/*
 *	externs
 */

extern	FigureList	*allocFigureList ( void );
extern	void	freeFigureList ( FigureList *lp );
extern	FigureList	*insertFigureList ( FigureList *lp, Figure *value );
extern	FigureList	*appendFigureList ( FigureList *lp, Figure *value );
extern	Figure	*findFigureList ( FigureList *lp, char *target );
extern	void	printFigureList ( FigureList *lp, char *sep );

/*
 *
 */

#endif

/*
 *
 */

