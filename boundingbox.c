/*
 *	boundingbox.h
 */

#include "coord.h"
#include "boundingbox.h"

/*
 *
 */

#define	setMin(X,Y) if ( X > Y ) { X = Y; }
#define	setMax(X,Y) if ( X < Y ) { X = Y; }

/*
 *
 */

#define	setBCMin(B,C,X) setMin( B -> min.X, C -> X )
#define	setBCMax(B,C,X) setMax( B -> max.X, C -> X )

void checkBounds ( BoundingBox *b, Coord *c ) {

  setBCMin ( b, c, x );
  setBCMax ( b, c, x );
  setBCMin ( b, c, y );
  setBCMax ( b, c, y );

}

/*
 *
 */

#define	setBMin(B,X) setMin( B -> min.X, X )
#define	setBSMax(B,X,S) setMax( B -> max.X, (X+S) )

void checkBoundsRng(
    BoundingBox *b, 
    float x,
    float y,
    float sx,
    float sy
    ) {

  setBMin(b,x);
  setBSMax(b,x,sx);
  setBMin(b,y);
  setBSMax(b,y,sy);

}

/*
 *
 */
