/*
 * vcell.h
 */

#ifndef	_VCELL_H_
#define	_VCELL_H_	1

/*
 *	includes
 */

#include "vfunc.h"

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
extern	void	applyVCell ( VCell *cp, ApplyFunc applyFunc );
extern	void	freeVCell ( VCell *cp, FreeFunc freeFunc );
extern	void	printVCell ( VCell *cp, PrintFunc printFunc );

/*
 *
 */

#endif

/*
 *
 */

