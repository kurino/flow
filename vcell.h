/*
 * vcell.h
 */

#ifndef	_VCELL_H_
#define	_VCELL_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	vcell	{
	struct	vcell	*next;
	void			*value;
} VCell;

/*
 *	externs
 */

extern	VCell	*allocVCell ( void *value );
extern	void	freeVCell ( VCell *cp, void (*freeFunc)( void * ) );
extern	void	printVCell ( VCell *cp, void (*printFunc)( void * ) );

/*
 *
 */

#endif

/*
 *
 */

