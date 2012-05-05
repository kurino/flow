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

extern void checkBounds ( BoundingBox *b, Coord *c );

extern void checkBoundsRng(
    BoundingBox *b, 
    float x,
    float y,
    float sx,
    float sy
);


/*
 *
 */

#endif

/*
 *
 */

