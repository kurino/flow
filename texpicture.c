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
#include "texpicture.h"

/*
 *
 */

void putSegmentPicture ( char *segment, double px, double py, int dx, int dy, double len ) {

	tprintf ( "\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
			  px, py, segment, dx, dy, len );

}

/*
 *
 */

void putLinePicture ( double px, double py, int dx, int dy, double len ) {

	putSegmentPicture ( "line", px, py, dx, dy, len );
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

void putVectorPicture ( double px, double py, int dx, int dy, double len ) {

	putSegmentPicture ( "vector", px, py, dx, dy, len );
}

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

void putBoxTextPicture ( double px, double py, char *box, double sx, double sy, char *boxPos, char *position ) {

	tprintf (
		"\\put(%3.4f,%3.4f){\\%s(%3.4f,%3.4f)%s{\\shortstack%s{\n",
        px, py, box, sx, sy, boxPos, position );

    doText();

    tprintf ( "}}}\n" );


}

/*
 *
 */
