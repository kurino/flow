/*
 *	drawarrow.c
 */

#include <stdio.h>

/*
 *
 */

#include "linethickness.h"
#include "direcs.h"
#include "coord.h"
#include "tracksymb.h"
#include "texpicture.h"
#include "drawarrow.h"

/*
 *
 */

void drawLine ( TrackSymb track, int astr, Coord pos, Direcs dir, double gap ) {
	/*						UP_DIR,	RIGHT_DIR,	DOWN_DIR,	LEFT_DIR	*/
	static int dxtab[] = {	 0,		 1,			 0,			-1	};
	static int dytab[] = {	 1,		 0,			-1,		 	 0	};

	if ( track != NONE_SYMBOL )	{
		char *trackStr;
		int dx = dxtab [ dir ];
		int dy = dytab [ dir ];

		switch ( astr ) {
		case TRACK_OPT_TRACK:
			trackStr = trackSymbToString ( track );
			break;
		case TRACK_OPT_ASTR:
			trackStr = trackSymbToString ( ARROW_SYMBOL );
			break;
		default:
			trackStr = trackSymbToString ( LINE_SYMBOL );
			break;
		}

		push_linethickness();
		putSegmentPicture (
						trackStr,
				  		pos.x,
						pos.y,
						dx,dy,
				  		gap );
		pop_linethickness();
	}

}

/*
 *
 */

void drawArrow ( TrackSymb track, Coord pos, Direcs dir, double gap ) {

	drawLine ( track, TRACK_OPT_TRACK, pos, dir, gap );
}

/*
 *
 */
