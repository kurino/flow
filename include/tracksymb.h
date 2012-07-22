/*
 * tracksymb.h
 */

#ifndef	_TRACKSYMB_H_
#define	_TRACKSYMB_H_	1

/*
 *
 */

/*
 *
 */

typedef enum {
	ARROW_SYMBOL = 0,
	LINE_SYMBOL = 1,
	NONE_SYMBOL = 2
} TrackSymb;

/*
 *
 */

extern	char	*trackSymbToString ( TrackSymb track );
extern	TrackSymb	stringToTrackSymb ( char *string );

/*
 *
 */

#endif

/*
 *
 */

