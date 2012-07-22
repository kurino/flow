/*
 * boundingbox.h
 */

#ifndef	_BOUNDINGBOX_H_
#define	_BOUNDINGBOX_H_	1

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

typedef struct {
	Coord	min;
	Coord	max;
} BoundingBox;

/*
 *	externs
 */

extern void checkBounds ( BoundingBox *b, const Coord *c );

extern void checkBoundsRng(
    BoundingBox *b, 
    double x,
    double y,
    double sx,
    double sy
);


/*
 *
 */

#endif

/*
 *
 */

