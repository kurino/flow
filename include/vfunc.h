/*
 * vfunc.h
 */

#ifndef	_VFUNC_H_
#define	_VFUNC_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	void (*ApplyFunc)( void * );

#define	FreeFunc	ApplyFunc
#define	PrintFunc	ApplyFunc

typedef	int (*CompareFunc)( void *, void * );

/*
 *
 */

typedef	struct	vfunc	{
	FreeFunc	free;
	PrintFunc	print;
	CompareFunc	compare;
} VFunc;

/*
 *	externs
 */


extern	VFunc	*allocVFunc (
							 FreeFunc freeFunc,
							 PrintFunc printFunc,
							 CompareFunc compareFunc
							 );

extern	void	freeVfunc ( VFunc *cp );

/*
 *
 */

#endif

/*
 *
 */

