/*
 * vpair.h
 */

#ifndef	_VPAIR_H_
#define	_VPAIR_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	vpair	{
	void	*src;
	void	*dst;
} VPair;

/*
 *	externs
 */

extern	VPair	*allocVPair ( void *srcValue, char *dstValue );
extern	void	freeVPair ( VPair *cp );
extern	void	printVPair ( VPair *cp );

/*
 *
 */

#endif

/*
 *
 */

