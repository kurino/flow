/*
 * texpicture.h
 */

#ifndef	_TEXPICTURE_H_
#define	_TEXPICTURE_H_	1

/*
 *	includes
 */

#include "tracksymb.h"

/*
 *	constants
 */

#define	TEX_INCLINATION_MAX	6

/*
 *	typedefs
 */

/*
 *	externs
 */

void putSegmentPicture ( char *segment, double px, double py, int dx, int dy, double len );

/*
 *
 */

extern	void putOvalPartsPicture ( double cx, double cy, double rx, double ry, char *position );

extern	void putOvalPicture ( double cx, double cy, double rx, double ry );

extern	void putTextPicture ( double px, double py, char *pos, char *text );

extern	void putBoxTextPicture ( double px, double py, char *box, double sx, double sy, char *boxPos, char *position );

extern	void putCirclePicture ( double cx, double cy, double r );
extern	void putBezierPicture ( double p0x, double p0y, double p1x, double p1y, double p2x, double p2y );

/*
 *
 */

extern	void putBoxTitlePicture ( double px, double py, double sx, double sy, char *title );


extern	void putLinePicture ( double px, double py, int dx, int dy, double len );
extern	void putVectorPicture ( double px, double py, int dx, int dy, double len );

extern	void putHorizontalLinePicture ( double px, double py, double len );
extern	void putVerticalLinePicture ( double px, double py, double len );

/*
 *
 */

#endif

/*
 *
 */

