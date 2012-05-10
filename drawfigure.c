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
#include "errout.h"
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

#define	TEX_INCLINATION_MAX	6

void drawChoice ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	int	i;
	int	xs = (int)curSize.x;
	int	ys = (int)curSize.y;

	/*
	 *
	 */

	for ( i = (xs > ys) ? xs : ys; i > 1; i-- ) {
		if ( (xs % i) == 0 && (ys % i) == 0 ) {
			xs /= i;
			ys /= i;
			i = ( xs > ys ) ? xs : ys;
	  	}
	}
    
	if ( xs > TEX_INCLINATION_MAX )	{
		errout ( W_ASPECT );
        xs = TEX_INCLINATION_MAX;
    }
    if ( ys > TEX_INCLINATION_MAX ) {
		errout ( W_ASPECT );
		ys = TEX_INCLINATION_MAX;
    }

	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      curCoord.x,
		      curCoord.y-curSize.y/2,
		      xs,ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      curCoord.x,
		      curCoord.y-curSize.y/2,
		      xs,-ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      curCoord.x+curSize.x,
		      curCoord.y-curSize.y/2,
		      -xs,-ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      curCoord.x+curSize.x,
		      curCoord.y-curSize.y/2,
		      -xs,ys,curSize.x/2
		      );

	/*
	 *
	 */

    checkPicBoundsRng (
        curCoord.x,
        curCoord.y - curSize.y,
        curSize.x,
        curSize.y
    );

	/*
	 *
	 */

}

/*
 *
 */

void drawSelect ( Coord curCoord, Coord curSize,
						char params0[],
						char params1[],
						char params2[],
						char params3[] ) {

	/*
	 *
	 */

	if ( params0[0] != '.' )	{
		tprintf ( "\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
						   curCoord.x+
						   curSize.x*0.65,
						   curCoord.y,
						   params0
						  );
	}
						   
	if ( params1[0] != '.' ) {
			tprintf ( "\\put(%3.4f,%3.4f){\\makebox(0,0)[rt]{%s}}\n",
						   curCoord.x,
						   curCoord.y-
						   curSize.y/2.*0.7,
						   params1
						  );
	}

	if ( params2[0] != '.' ) {
			tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
						   curCoord.x+
			   curSize.x,
						   curCoord.y-
			   curSize.y/2.*0.7,
						   params2
						  );
	}
						   
	if ( params3[0] != '.' ) {
		tprintf ( "\\put(%3.4f,%3.4f){\\makebox(0,0)[lb]{%s}}\n",
						   curCoord.x+
						   curSize.x*0.65,
						   curCoord.y-
						   curSize.y,
						   params3
						  );
	}

	/*
	 *
	 */

}

/*
 *
 */
