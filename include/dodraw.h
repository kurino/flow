/*
 * dodraw.h
 */

#ifndef	_DODRAW_H_
#define	_DODRAW_H_	1

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

/*
 *	externs
 */

extern	void	doDraw ( char *name, char *pList, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos );



extern	void putInnerCircle ( double cx, double cy, double r );
extern	void putInnerOval ( double cx, double cy, double rx, double ry );
extern	void putInnerBezier ( double p0x, double p0y, double p1x, double p1y, double p2x, double p2y );
extern	void putInnerText ( double px, double py, char *text );
extern	void putInnerLine ( double sx, double sy, double ex, double ey );
extern	void putInnerBox ( double sx, double sy, double ex, double ey );

/*
 *
 */

extern	void drawInnerLine ( Coord curCoord, Coord curSize, double sx, double sy, double ex, double ey );

/*
 *
 */

#endif

/*
 *
 */

