/*
 *	drawfigure.c
 */

#include <stdio.h>

/*
 *
 */

#include "coord.h"
#include "tempfile.h"
#include "boundingbox.h"
#include "pic.h"
#include "drawfigure.h"

/*
 *
 */

void drawBoxPut ( char *box, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {

	tprintf (
		"\\put(%3.4f,%3.4f){\\%s(%3.4f,%3.4f)%s{\\shortstack%s{\n",
        curCoord.x,
		curCoord.y - curSize.y,
		box,
		curSize.x,
		curSize.y,
		curBoxPos,
		curPos );

    doText();

    tprintf ( "}}}\n" );
}

/*
 *
 */

void drawFramePut ( Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {

  drawBoxPut ( "framebox", curCoord, curSize, curBoxPos, curPos );

}

/*
 *
 */

void drawMakePut ( Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {

  drawBoxPut ( "makebox", curCoord, curSize, curBoxPos, curPos );

}

/*
 *
 */


void checkTextPicBoundsRng ( Coord curCoord, Coord curSize ) {

  checkPicBoundsRng (
					 curCoord.x,
					 curCoord.y-curSize.y,
					 curSize.x,
					 curSize.y
					 );
}

/*
 *
 */

void drawBox ( Coord curCoord, Coord curSize ) {

	checkTextPicBoundsRng ( curCoord, curSize );
}

/*
 *
 */

void drawTilt ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x+1./6.*curSize.y,
		       curCoord.y,
		       1,0,
		       curSize.x);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x-1./6.*curSize.y,
		       curCoord.y-curSize.y,
		       1,0,
		       curSize.x);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x-1./6.*curSize.y,
		       curCoord.y-curSize.y,
		       1,3,
		       curSize.y*1./3.);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x-1./6.*curSize.y+curSize.x,
		       curCoord.y-curSize.y,
		       1,3,
		       curSize.y*1./3.);

	/*
	 *
	 */

    checkPicBoundsRng (
        curCoord.x-1./6.*curSize.y,
        curCoord.y-curSize.y,
        curSize.x + 1./6.*curSize.y,
        curSize.y
    );

	/*
	 *
	 */

}

/*
 *
 */

void drawDrum ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	/* up */
	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)}\n",
		       curCoord.x+curSize.x/2.0,
		       curCoord.y-0.5,
		       curSize.x,1.0);
	/* down */
	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)[b]}\n",
		       curCoord.x+curSize.x/2.0,
		       curCoord.y-curSize.y+0.5,
		       curSize.x,1.0);
	/* left */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x,
		       curCoord.y-curSize.y+0.5,
		       0,1,
		       curSize.y-1.0);
	/* right */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x+curSize.x,
		       curCoord.y-curSize.y+0.5,
		       0,1,
		       curSize.y-1.0);

	/*
	 *
	 */

		checkPicBoundsRng (
						   curCoord.x,
						   curCoord.y-curSize.y-1.5,
						   curSize.x,
						   curSize.y+2.0
						   );

	/*
	 *
	 */
}

/*
 *
 */

void drawCall ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	/* up */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x,
		       curCoord.y,
		       1,0,
		       curSize.x);
	/* down */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x,
		       curCoord.y-curSize.y,
		       1,0,
		       curSize.x);
	/* left */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x,
		       curCoord.y-curSize.y,
		       0,1,
		       curSize.y);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x+0.1,
		       curCoord.y-curSize.y,
		       0,1,
		       curSize.y);
	/* right */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x+curSize.x,
		       curCoord.y-curSize.y,
		       0,1,
		       curSize.y);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       curCoord.x+curSize.x-0.1,
		       curCoord.y-curSize.y,
		       0,1,
		       curSize.y);

	/*
	 *
	 */

	checkTextPicBoundsRng ( curCoord, curSize );

	/*
	 *
	 */
}

/*
 *
 */

void drawOval ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)}\n",
		       curCoord.x+curSize.x/2,
		       curCoord.y-curSize.y/2,
		       curSize.x,
		       curSize.y );

	/*
	 *
	 */

	checkTextPicBoundsRng ( curCoord, curSize );

	/*
	 *
	 */

}

/*
 *
 */
