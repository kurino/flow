/*
 *	texpicture.c
 *		cf.
 *			http://www.biwako.shiga-u.ac.jp/sensei/kumazawa/tex/picture.html
 */

#include <stdio.h>

/*
 *
 */

#include "tempfile.h"
#include "tracksymb.h"
#include "texpicture.h"

/*
 *
 */

void putOvalPartsPicture ( double cx, double cy, double rx, double ry, char *position ) {

	tprintf ( "\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)%s}\n",
			  cx, cy, rx, ry, position );

}

/*
 *
 */

void putOvalPicture ( double cx, double cy, double rx, double ry ) {

	putOvalPartsPicture ( cx, cy, rx, ry, "" );
}

/*
 *
 */

void putTextPicture ( double px, double py, char *pos, char *text ) {

	tprintf ( "\\put(%3.4f,%3.4f){\\makebox(0,0)%s{%s}}\n",
			  px, py, pos, text );

}

/*
 *
 */

static void putBoxTextPictureHead ( double px, double py, char *box, double sx, double sy, char *boxPos, char *position ) {

	tprintf (
		"\\put(%3.4f,%3.4f){\\%s(%3.4f,%3.4f)%s{\\shortstack%s{\n",
        px, py, box, sx, sy, boxPos, position );
}

static void putBoxTextPictureTail ( void ) {

    tprintf ( "}}}\n" );
}

/*
 *
 */

void putBoxTextPicture ( double px, double py, char *box, double sx, double sy, char *boxPos, char *position ) {

	putBoxTextPictureHead ( px, py, box, sx, sy, boxPos, position );

    doText();

	putBoxTextPictureTail();

}

/*
 *
 */

void putBoxTitlePicture ( double px, double py, double sx, double sy, char *title ) {

	putBoxTextPictureHead ( px, py, "makebox", sx, sy, "[c]", "[c]" );

	tprintf ( "%s\n", title );

	putBoxTextPictureTail();

}

/*
 *
 */

void putCirclePicture ( double cx, double cy, double r ) {

	tprintf ( "\\put(%3.4f,%3.4f){\\circle{%3.4f}}\n",
			  cx, cy, r );

}

/*
 *
 */

void putBezierPicture ( double p0x, double p0y, double p1x, double p1y, double p2x, double p2y ) {

	tprintf ( "\\qbezier(%3.4f,%3.4f)(%3.4f,%3.4f)(%3.4f,%3.4f)\n",
			  p0x, p0y, p1x, p1y, p2x, p2y );

}

/*
 *
 */

void putSegmentPicture ( char *segment, double px, double py, int dx, int dy, double len ) {

	tdprintf ( "[Segment] (%f,%f)[%d,%d]{%lf}\n", px, py, dx, dy, len );

	if ( len < 0 ) {
//		dx = -dx;
//		dy = -dy;
		len = - len;
		if ( dx == 0 ) {
			dy = -dy;
		}
	}

	tprintf ( "\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
			  px, py, segment, dx, dy, len );

}

/*
 *
 */

void putHorizontalSegmentPicture ( TrackSymb type, double px, double py, double len ) {

	putSegmentPicture ( trackSymbToString ( type ), px, py, 1, 0, len );
}

/*
 *
 */

void putVerticalSegmentPicture ( TrackSymb type, double px, double py, double len ) {

	putSegmentPicture ( trackSymbToString ( type ), px, py, 0, 1, len );
}

/*
 *
 */

void putLinePicture ( double px, double py, int dx, int dy, double len ) {

	putSegmentPicture ( trackSymbToString ( LINE_SYMBOL ), px, py, dx, dy, len );
}

/*
 *
 */

void putVectorPicture ( double px, double py, int dx, int dy, double len ) {

  putSegmentPicture ( trackSymbToString ( ARROW_SYMBOL ), px, py, dx, dy, len );
}

/*
 *
 */

void putHorizontalLinePicture ( double px, double py, double len ) {

	putLinePicture ( px, py, 1, 0, len );
}

/*
 *
 */

void putVerticalLinePicture ( double px, double py, double len ) {

	putLinePicture ( px, py, 0, 1, len );
}

/*
 *
 */

void putHorizontalVectorPicture ( double px, double py, double len ) {

	putVectorPicture ( px, py, 1, 0, len );
}

/*
 *
 */

void putVerticalVectorPicture ( double px, double py, double len ) {

	putVectorPicture ( px, py, 0, 1, len );
}

/*
 *
 */
