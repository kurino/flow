/*
 *	tempfile.c
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
 *
 */

#include "errout.h"
#include "boundingbox.h"
#include "applaypicwrapper.h"
#include "tempfile.h"

/*
 *
 */

#define	TEMP_FILE_LENGTH	80

/*
 *
 */

static	FILE	*outFile = NULL;  				/* global tempfile streams */
static	char	tmpfileName [ TEMP_FILE_LENGTH ] = "flow";

/*
 *
 */

void open_tempfile ( void ) {

#ifdef KURINO
	mkstemp ( tmpfileName );
#else
    tmpnam ( tmpfileName );
#endif

#ifdef DEBUG_PRINT
	fprintf ( stderr, "tmepfile=(%s)\n", tmpfileName );
#endif

	if ( ( outFile = fopen ( tmpfileName, "w" ) ) == NULL ) {
		errout ( E_OPEN_TEMPFILE, tmpfileName );
	}
}

/*
 *
 */

void close_tempfile ( void ) {

  if ( outFile != NULL ) {
	  fclose ( outFile );
	  outFile = NULL;
  }
}

/*
 *
 */

void remove_tempfile ( void ) {

    remove ( tmpfileName );
}

/*
 *
 */


void apply_tempfile ( BoundingBox pic, char *outName ) {
	FILE *ifp;
	FILE *ofp;

	if ( ( ifp = fopen ( tmpfileName, "r" ) ) == NULL ) {
		errout ( E_OPEN_TEMPFILE, tmpfileName );
	}

	if ( outName == NULL ) {
	  ofp = stdout;
	} else if ( ( ofp = fopen ( outName, "w" ) ) == NULL ) {
	  errout ( E_OPEN_OUTPUT, outName );
	}

    applyPicWrapper ( ifp, ofp, pic );

    if ( ofp != stdout ) {
		fclose ( ofp );
	}
    fclose ( ifp );

}

/*
 *
 */

void tprintf ( char *fmt, ... ) {
	va_list ap;

	if ( outFile == NULL ) {
		errout ( E_TEMPFILE_NOT_OPENED );
	} else {
		va_start ( ap, fmt );
		vfprintf ( outFile, fmt, ap );
		va_end( ap );
	} 

}


/*
 *
 */
