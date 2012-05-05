/*
 *	linethickness.c
 */

#include <stdio.h>

/*
 *
 */

#include "tempfile.h"
#include "linethickness.h"

/*
 *
 */

/*
 *
 */

static	double CurWidth = LINE_WIDTH_THICK;
static	double NormalWidth = LINE_WIDTH_THICK;

/*
 *
 */

void set_linelinethickness ( double width ) {

	if ( width <= 0.0 ) {
		CurWidth = NormalWidth;
	} else {
		CurWidth = width;
	}
}

/*
 *
 */

void push_linethickness ( void ) {

	if ( CurWidth != NormalWidth ) {

		tprintf ( "\\linethickness{%fpt}\n", CurWidth );
	}

}

void pop_linethickness ( void ) {

	if ( CurWidth != NormalWidth ) {

		tprintf ( "\\linethickness{%fpt}\n", NormalWidth );
	}
}



/*
 *
 */
