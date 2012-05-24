/*
 * texpicture.h
 */

#ifndef	_TEXPICTURE_H_
#define	_TEXPICTURE_H_	1

/*
 *	includes
 */

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

extern	void putSegmentPicture ( char *segment, double px, double py, int dx, int dy, double len );
extern	void putLinePicture ( double px, double py, int dx, int dy, double len );

extern	void putHorizontalLinePicture ( double px, double py, double len );
extern	void putVerticalLinePicture ( double px, double py, double len );

extern	void putVectorPicture ( double px, double py, int dx, int dy, double len );

extern	void putOvalPartsPicture ( double cx, double cy, double rx, double ry, char *position );

extern	void putOvalPicture ( double cx, double cy, double rx, double ry );

extern	void putTextPicture ( double px, double py, char *pos, char *text );

extern	void putBoxTextPicture ( double px, double py, char *box, double sx, double sy, char *boxPos, char *position );

/*
 *
 */

#endif

/*
 *
 */

