/*
 *	pic.c
 */

#include <stdio.h>

/*
 *
 */

#include "coord.h"
#include "boundingbox.h"
#include "pic.h"

/*
 *
 */

static	BoundingBox pic = {{0,0},{0,0}};

/*
 *
 */

BoundingBox	getPic ( void ) {

	return pic;
}

/*
 *
 */

void	checkPicBounds ( const Coord *c ) {

	checkBounds ( &pic, c );
}


/*
 *
 */

void    checkPicBoundsRng(
    float x,
    float y,
    float sx,
    float sy
						  ) {

  checkBoundsRng ( &pic, x, y, sx, sy );

}
