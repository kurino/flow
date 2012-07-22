/*
 * coord.h
 */

#ifndef	_COORD_H_
#define	_COORD_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef struct {
	double	x;
	double	y;
} Coord;

/*
 *	externs
 */

extern	Coord	*allocCoord ( double x, double y );
extern	void	freeCoord ( Coord *mp );
extern	void	printCoord ( Coord *cp );

/*
 *
 */

#endif

/*
 *
 */
