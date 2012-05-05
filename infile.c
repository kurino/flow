/*
 *	infile.c
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

/*
 *
 */

#include "eos.h"
#include "errout.h"
#include "infile.h"

/*
 *
 */

static	FILE	*inFile = NULL;  /* global infile infile streams */
static	char	*inFileName = NULL;
static	int		inputLine = 0;
static	char	*ungetline = NULL;

/*
 *
 */

void open_infile ( char *fileName ) {

	if ( fileName == NULL ) {
		inFile = stdin;
		inFileName = "stdin";
	} else {
		inFileName = fileName;
		if ( ( inFile = fopen ( fileName, "r" ) ) == NULL ) {
			errout ( E_OPEN_INPUT, fileName );
		}
	}

 	inputLine = 0;

}

/*
 *
 */

void unget_infile ( char *line ) {

	if ( ungetline == NULL ) {
		ungetline = strdup ( line );
	    inputLine--;
	} else {
		errout ( E_TOO_MANY_UNGET, line );
	}
}

/*
 *
 */

char	*readline_infile ( char *line, int size ) {
	char *ret;
	int l;

    inputLine++;
    line [ 0 ] = EOS;

	if ( ungetline != NULL ) {
		ret = strncpy ( line, ungetline, size );
		free ( ungetline );
		ungetline = NULL;
	} else if ( ( ret = fgets ( line, size, inFile ) ) != NULL ) {
		l = strlen ( line );
		if ( l > 0 && line[ l - 1 ] == '\n' ) {
			line[ l - 1 ] = EOS;
		}
	}

#ifdef DEBUG_PRINT
	fprintf ( stderr, "%d : %s\n", inputLine, line );
#endif

	return ret;
}

/*
 *
 */

void close_infile ( void ) {

  if ( inFile != NULL ) {
	if ( inFile != stdin ) {
	  fclose ( inFile );
	}
	inFile = NULL;
  }
}

/*
 *
 */

int	eof_infile ( void ) {

  return ( ungetline == NULL ) && feof ( inFile );
}

/*
 *
 */

int	get_input_line ( void ) {

	return inputLine;
}

/*
 *
 */
