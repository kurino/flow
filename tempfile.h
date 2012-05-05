/*
 * tempfile.h
 */

#ifndef	_TEMPFILE_H_
#define	_TEMPFILE_H_	1

/*
 *	includes
 */

#include "boundingbox.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	void open_tempfile ( void );
extern	void close_tempfile ( void );
extern	void remove_tempfile ( void );
extern	void apply_tempfile ( BoundingBox pic, char *outName );

extern	void tprintf ( char *fmt, ... );

/*
 *
 */

#endif

/*
 *
 */

