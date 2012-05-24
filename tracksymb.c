/*
 *	tracksymb.c
 */

#include <stdio.h>
#include <string.h>

/*
 *
 */

#include "tracksymb.h"

/*
 *
 */

/*
 *
 */

static char *str[] = {
	  /*	ARROW_SYMBOL,	LINE_SYMBOL,	NONE_SYMBOL	*/
			"vector",		"line",			"none"
};

/*
 *
 */

char	*trackSymbToString ( TrackSymb track ) {

	if ( track < ARROW_SYMBOL || NONE_SYMBOL < track ) {
		track = ARROW_SYMBOL;
	}

	return str [ track ];
}

/*
 *
 */

TrackSymb	stringToTrackSymb ( char *string ) {
	TrackSymb track;

	for ( track = ARROW_SYMBOL; track <= NONE_SYMBOL; track++ ) {
		if ( !strcmp ( string, str [ track ] ) ) {
			break;
		}
	}

	return track;
}

/*
 *
 */
