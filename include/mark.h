/*
 * mark.h
 */

#ifndef	_MARK_H_
#define	_MARK_H_	1

/*
 *	includes
 */

#include "coord.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef	struct	{
	char	*name;
	Coord	*coord;
	int		direc;
} Mark;

/*
 *	externs
 */

extern	Mark	*allocMark ( char *name, Coord *coord, int curDirec );
extern	void	freeMark ( Mark *mp );
extern	void	printMark ( Mark *mp );

/*
 *
 */

#endif

/*
 *
 */

