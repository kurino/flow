/*
 *	token.c
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 *
 */

#include "eos.h"
#include "token.h"

/*
 *
 */

#define	isTokenChar( X )	( ( (X) != EOS ) && ( !isspace(X) ) )

/*
 *
 */

char *skipSpace ( char *ptr ) {

	while ( isspace ( *ptr ) ) {
		ptr++;
	}

	return ptr;
}

/*
 *
 */

char	*getToken ( char *word, char *line ) {
	char *dst = word;

	line = skipSpace ( line );

	if ( *line == EOS ) {
		return NULL;
	}

	while ( isTokenChar( *line ) ) {
		*dst++ = *line++;
	}

	*dst = EOS;

//	fprintf ( stderr, "Token: %s - %s\n", word, line );

	return line;
}

/*
 *
 */

char *skipToken ( char *ptr ) {

	ptr = skipSpace ( ptr );
	while ( isTokenChar( *ptr ) ) {
		ptr++;
	}

	return ptr;
}

/*
 *
 */

char	*getLastText ( char *word, char *line ) {
	char *q = NULL;
	char *p = word;
	int	ch;

	line = skipSpace ( line );

	while ( ( ch = (*p++ = *line++) ) != EOS ) {
		if ( isspace ( ch ) ) {
			if ( q == NULL ) {
				q = p;
			}
		} else {
			q = NULL;
		}
	}

	if ( q != NULL ) {
		*q = EOS;	/* remove tail space */
	}

	return word;
}

/*
 *
 */

