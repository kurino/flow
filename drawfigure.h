/*
 * drawfigure.h
 */

#ifndef	_DRAWFIGURE_H_
#define	_DRAWFIGURE_H_	1

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

extern	void drawBoxPut ( char *box, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos );
extern	void drawFramePut ( Coord curCoord, Coord curSize, char *curBoxPos, char *curPos );
extern	void drawMakePut ( Coord curCoord, Coord curSize, char *curBoxPos, char *curPos );

extern	void drawBox ( Coord curCoord, Coord curSize );
extern	void drawTilt ( Coord curCoord, Coord curSize );
extern	void drawDrum ( Coord curCoord, Coord curSize );
extern	void drawCall ( Coord curCoord, Coord curSize );
extern	void drawOval ( Coord curCoord, Coord curSize );
extern	void drawChoice ( Coord curCoord, Coord curSize );


/*
 *
 */

#endif

/*
 *
 */

