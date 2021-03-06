/*
 * atag.h
 */

#ifndef	_ATAG_H_
#define	_ATAG_H_	1

/*
 *	includes
 */

#include	"coord.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

typedef struct ATAG {
	Coord			pos;
	Coord			size;
	struct	ATAG	*next;
} ATag;

/*
 *	externs
 */

extern	void pushATag ( Coord *sizePtr, Coord *posPtr );
extern	void popATag ( Coord *sizePtr, Coord *posPtr );

/*
 *
 */

#endif

/*
 *
 */

