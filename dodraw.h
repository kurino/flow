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



extern	void putInnerCircle ( float cx, float cy, float r );
extern	void putInnerOval ( float cx, float cy, float rx, float ry );
extern	void putInnerBezier ( float p0x, float p0y, float p1x, float p1y, float p2x, float p2y );
extern	void putInnerText ( float px, float py, char *text );
extern	void putInnerLine ( float sx, float sy, float ex, float ey );
extern	void putInnerBox ( float sx, float sy, float ex, float ey );

/*
 *
 */

extern	void drawInnerLine ( Coord curCoord, Coord curSize, float sx, float sy, float ex, float ey );

/*
 *
 */

#endif

/*
 *
 */

