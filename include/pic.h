/*
 * pic.h
 */

#ifndef	_PIC_H_
#define	_PIC_H_	1

/*
 *	includes
 */

#include "coord.h"
#include "boundingbox.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	BoundingBox	getPic ( void );
extern	void		checkPicBounds ( const Coord *c );
extern	void		checkPicBoundsRng ( double x, double y, double sx, double sy );

/*
 *
 */

#endif

/*
 *
 */

