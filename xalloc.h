/*
 * xalloc.h
 */

#ifndef	_XALLOC_H_
#define	_XALLOC_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

#define	xalloc(Type)	((Type *)malloc(sizeof(Type)))
#define	xfree(Ptr)		free(Ptr)

/*
 *	typedefs
 */

/*
 *	externs
 */

/*
 *
 */

#endif

/*
 *
 */

