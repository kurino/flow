/*
 *	atag.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "xalloc.h"
#include "errout.h"
#include "coord.h"
#include "atag.h"

/*
 *
 */

static ATag *curTag = NULL;

/*
 *
 */

void pushATag( Coord *sizePtr, Coord *posPtr ) {
	ATag *tempTag = xalloc( ATag );

	if ( tempTag != NULL ) {

        tempTag -> next = curTag;
		curTag = tempTag;

		curTag -> size = *sizePtr;
		curTag -> pos = *posPtr;

	} else {
		errout ( E_NO_MEMORY );
	}
}

/*
 *
 */

void popATag( Coord *sizePtr, Coord *posPtr ) {

	if ( curTag != NULL ) {
		ATag *tempTag = curTag;

        *sizePtr = curTag -> size;
        *posPtr = curTag -> pos;

        curTag = curTag -> next;

        xfree( tempTag );

	} else {
		errout ( E_TAG_STACK_EMPTY );
    }

}

/*
 *
 */
