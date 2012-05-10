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
#include "drawarrow.h"

/*
 *
 */

void drawLine ( TrackSymb track, int astr, Coord pos, Direcs dir, float gap ) {
	/*					UpD,	DownD,	LeftD,	RightD	*/
	static int dxtab[] = {	 0,		 0,		-1,		1	};
	static int dytab[] = {	 1,		-1,		 0,		0	};
						  /*	ArrowS,		LineS,	NoneS	*/
	static char *str[] = {	"vector",	"line",	"none"	};

	if ( track != NoneS )	{
		char *trackStr;
		int dx = dxtab [ dir ];
		int dy = dytab [ dir ];

		switch ( astr ) {
		case TRACK_OPT_TRACK:
			trackStr = str [ track ];
			break;
		case TRACK_OPT_ASTR:
			trackStr = str [ ArrowS ];
			break;
		default:
			trackStr = str [ LineS ];
			break;
		}

		push_linethickness();
		tprintf ( "\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
				  		pos.x,
						pos.y,
						trackStr,
						dx,dy,
				  		gap );
		pop_linethickness();
	}

}

/*
 *
 */

void drawArrow ( TrackSymb track, Coord pos, Direcs dir, float gap ) {

	drawLine ( track, TRACK_OPT_TRACK, pos, dir, gap );
}

/*
 *
 */
