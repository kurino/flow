/*
 *	drawfigure.c
 */

#include <stdio.h>

/*
 *
 */

#include "coord.h"
#include "boundingbox.h"
#include "pic.h"
#include "errout.h"
#include "texpicture.h"
#include "dodraw.h"
#include "drawfigure.h"

/*
 *
 */

void drawBoxPut ( char *box, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {

	putBoxTextPicture (
        curCoord.x,
		curCoord.y - curSize.y,
		box,
		curSize.x,
		curSize.y,
		curBoxPos,
		curPos );

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
					curCoord.y - curSize.y,
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

#define	TILT_GRADIENTS	3
#define	TILT_INVERSE_GRADIENTS	(1./(double)TILT_GRADIENTS)
#define	TILT_INVERSE_GRADIENTS_HALF	(TILT_INVERSE_GRADIENTS/2.0)

void drawTilt ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	/* up */
	putHorizontalLinePicture (
				curCoord.x + TILT_INVERSE_GRADIENTS_HALF * curSize.y,
				curCoord.y,
				curSize.x );

	/* down */
	putHorizontalLinePicture (
				curCoord.x - TILT_INVERSE_GRADIENTS_HALF * curSize.y,
				curCoord.y - curSize.y,
				curSize.x );

	/* left */
	putLinePicture (
				curCoord.x - TILT_INVERSE_GRADIENTS_HALF * curSize.y,
				curCoord.y - curSize.y,
				1, TILT_GRADIENTS,
				curSize.y * TILT_INVERSE_GRADIENTS );

	/* right */
	putLinePicture (
				curCoord.x - TILT_INVERSE_GRADIENTS_HALF * curSize.y + curSize.x,
				curCoord.y - curSize.y,
				1, TILT_GRADIENTS,
				curSize.y * TILT_INVERSE_GRADIENTS );

	/*
	 *
	 */

    checkPicBoundsRng (
		curCoord.x - TILT_INVERSE_GRADIENTS_HALF * curSize.y,
		curCoord.y - curSize.y,
		curSize.x + TILT_INVERSE_GRADIENTS_HALF * curSize.y,
		curSize.y
    );

	/*
	 *
	 */

}

/*
 *
 */

#define	DRUM_HIGHT		(1.0)
#define	DRUM_HIGHT_HALF	(DRUM_HIGHT/2.0)

void drawDrum ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	/* up */
	putOvalPicture(
				curCoord.x + curSize.x / 2.0,
				curCoord.y - DRUM_HIGHT_HALF,
				curSize.x, DRUM_HIGHT );

	/* down */
	putOvalPartsPicture (
				curCoord.x + curSize.x / 2.0,
				curCoord.y - curSize.y + DRUM_HIGHT_HALF,
				curSize.x, DRUM_HIGHT, "[b]" );

	/* left */
	putVerticalLinePicture (
				curCoord.x,
				curCoord.y - curSize.y + DRUM_HIGHT_HALF,
				curSize.y - DRUM_HIGHT );

	/* right */
	putVerticalLinePicture (
				curCoord.x + curSize.x,
				curCoord.y - curSize.y + DRUM_HIGHT_HALF,
				curSize.y - DRUM_HIGHT );

	/*
	 *
	 */

		checkPicBoundsRng (
						   curCoord.x,
						   curCoord.y - curSize.y - DRUM_HIGHT_HALF * 3.0,
						   curSize.x,
						   curSize.y + DRUM_HIGHT * 2.0
						   );

	/*
	 *
	 */
}

/*
 *
 */

#define	CALL_THICK	0.1

void drawCall ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	/* up */
	putHorizontalLinePicture (
				curCoord.x,
				curCoord.y,
				curSize.x );

	/* down */
	putHorizontalLinePicture (
				curCoord.x,
				curCoord.y - curSize.y,
				curSize.x );

	/* left */
	putVerticalLinePicture (
				curCoord.x,
				curCoord.y - curSize.y,
				curSize.y );

	putVerticalLinePicture (
				curCoord.x + CALL_THICK,
				curCoord.y - curSize.y,
				curSize.y );

	/* right */
	putVerticalLinePicture (
				curCoord.x + curSize.x,
				curCoord.y - curSize.y,
				curSize.y );

	putVerticalLinePicture (
				curCoord.x + curSize.x - CALL_THICK,
				curCoord.y - curSize.y,
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

void drawOval ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

	putOvalPicture (
				curCoord.x + curSize.x / 2,
				curCoord.y - curSize.y / 2,
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

void drawChoice ( Coord curCoord, Coord curSize ) {

	/*
	 *
	 */

  /*
	int	i;
	int	xs = (int)curSize.x;
	int	ys = (int)curSize.y;
  */
	/*
	 *
	 */
  /*
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

	putLinePicture (
		      curCoord.x,
		      curCoord.y - curSize.y / 2,
		      xs, ys, curSize.x / 2
		      );

	putLinePicture (
		      curCoord.x,
		      curCoord.y-curSize.y / 2,
		      xs, -ys, curSize.x / 2
		      );

	putLinePicture (
		      curCoord.x + curSize.x,
		      curCoord.y - curSize.y/2,
		      -xs, -ys, curSize.x / 2
		      );

	putLinePicture (
		      curCoord.x + curSize.x,
		      curCoord.y - curSize.y/2,
		      -xs, ys, curSize.x / 2
		      );
  */

  putInnerLine (
		      curCoord.x,
		      curCoord.y - curSize.y / 2,

			  curCoord.x + curSize.x / 2,
		      curCoord.y
				);

  putInnerLine (
		      curCoord.x,
		      curCoord.y - curSize.y / 2,

			  curCoord.x + curSize.x / 2,
		      curCoord.y - curSize.y
		      );

  putInnerLine (
		      curCoord.x + curSize.x,
		      curCoord.y - curSize.y / 2,

		      curCoord.x + curSize.x / 2,
		      curCoord.y - curSize.y
		      );

  putInnerLine (
		      curCoord.x + curSize.x,
		      curCoord.y - curSize.y / 2,

		      curCoord.x + curSize.x / 2,
		      curCoord.y
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
		putTextPicture (
						curCoord.x +
						curSize.x * 0.65,
						curCoord.y,
						"[lt]",
						params0
						);
	}
							
	if ( params1[0] != '.' ) {
		putTextPicture (
						curCoord.x,
						curCoord.y-
						curSize.y / 2. * 0.7,
						"[rt]",
						params1
						);
	}

	if ( params2[0] != '.' ) {
		putTextPicture (
						curCoord.x +
						curSize.x,
						curCoord.y-
						curSize.y / 2. * 0.7,
						"[lt]",
						params2
						);
	}
							
	if ( params3[0] != '.' ) {
		putTextPicture (
						curCoord.x +
						curSize.x * 0.65,
						curCoord.y -
						curSize.y,
						"[lb]",
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

void drawTitleText ( Coord curCoord, Coord curSize, char *title ) {

	putBoxTitlePicture ( curCoord.x, curCoord.y - 1.0, curSize.x, 1.0, title );

}

/*
 *
 */
