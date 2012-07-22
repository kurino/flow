/*
 *	infile.c
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>

/*
 *
 */

#include "eos.h"
#include "errout.h"
#include "xalloc.h"
#include "strlist.h"
#include "argument.h"
#include "infile.h"

/*
 *
 */

static	FILE	*inFile = NULL;  /* global infile infile streams */
static	char	*inFileName = NULL;
static	int		inputLine = 0;
static	int		macroLine = -1;
static	StrList	*ungetList = NULL;

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
	macroLine = -1;

}

/*
 *
 */

void unget_infile ( char *line ) {

	if ( ungetList == NULL ) {
		ungetList = allocStrList();
	}

	if ( ungetList != NULL ) {
		insertStrList ( ungetList, line );
		if ( macroLine >= 0 ) {
			macroLine++;
		} else {
		    inputLine--;
		}
	} else {
		errout ( E_TOO_MANY_UNGET, line );	//@@@
	}
}

/*
 *
 */

static void	insert_infile_sub ( VCell *vcp, Argument *agp ) {


	if ( vcp != NULL ) {
		char	strbuf[ ARG_LINE ];

		insert_infile_sub ( vcp -> next, agp );
		unget_infile ( assingArgument ( strbuf, (char *)vcp -> value, agp ) );

		macroLine++;
	}

}

void insert_infile ( StrList *slp, Argument *agp ) {

	if ( slp != NULL ) {
		if ( macroLine < 0 ) {
			macroLine = 0;
		}
		insert_infile_sub ( slp -> top, agp );
	}
}

/*
 *
 */

char	*readline_infile ( char *line, int size ) {
	char *ret;
	int l;

	if ( macroLine > 0 ) {
		macroLine--;
	} else {
		macroLine = -1;
	    inputLine++;
	}

    line [ 0 ] = EOS;

	if ( ungetList != NULL && ungetList -> top != NULL ) {
		char *ptr = popStrList ( ungetList );
		ret = strncpy ( line, ptr, size );
		xfree ( ptr );
	} else {
		while ( ( ret = fgets ( line, size, inFile ) ) != NULL ) {
			l = strlen ( line );

			if ( l > 0 && line [ l - 1 ] == '\n' ) {
				line [ --l ] = EOS;			// remove NewLine
			}

			while ( l > 0 && isspace ( line[ l - 1 ] ) ) {
				l--;
			}

			// remove spaces at end of line
			//	line [ l ] = EOS;	// add then

			if ( l > 0 ) {
				break;
			}

			// here, this line is ``space line'', so remove it
			// But .. ? (2012/05/26 +k-0.06)

			//			line [ l ] = EOS;		// remove it
		    inputLine++;
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

  return ( ( ungetList == NULL ) || ( ungetList -> top == NULL ) ) && feof ( inFile );
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
