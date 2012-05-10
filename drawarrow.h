/*
 * drawarrow.h
 */

#ifndef	_DRAWARROW_H_
#define	_DRAWARROW_H_	1

/*
 *	includes
 */

#include "direcs.h"
#include "coord.h"
#include "tracksymb.h"

/*
 *	constants
 */

#define	TRACK_OPT_ASTR	'*'
#define	TRACK_OPT_TRACK	'T'

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	void drawLine ( TrackSymb track, int astr, Coord pos, Direcs dir, float gap );
extern	void drawArrow ( TrackSymb track, Coord pos, Direcs dir, float gap );

/*
 *
 */

#endif

/*
 *
 */

