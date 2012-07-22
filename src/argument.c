/*
 *	argument.c
 */

#include <stdio.h>
#include <malloc.h>

/*
 *
 */

#include "eos.h"
#include "xalloc.h"
#include "vcell.h"
#include "vlist.h"
#include "token.h"
#include "argument.h"

/*
 *
 */

static	Argument	*setupArgument ( Argument *agp, char *line ) {
	StrList *slp = allocStrList();
	char	token[ TOKEN_SIZE ];
	int		i;

	if ( slp == NULL ) {
		return NULL;
	}

	agp -> argb = slp;

	for ( i = 0; ( line = getToken ( token, line ) ) != NULL; i++ ) {
		if ( appendStrList ( slp, token ) == NULL ) {
			return NULL;
		}
	}

	if ( ( agp -> argv = xnalloc( char *, i + 1 ) ) != NULL ) {
		VCell *vp = agp -> argb -> top;

		agp -> argc = i;

		for ( i = 0; i < agp -> argc; i++ ) {
			if ( vp == NULL ) {
				return NULL;
			}
			agp -> argv [ i ] = (char *)vp -> value;
			vp = vp -> next;
		}

		agp -> argv [ i ] = NULL;
	}

	return agp;
}

/*
 *
 */

Argument	*allocArgument ( char *line ) {
	Argument	*agp;

	if ( ( agp = xalloc( Argument ) ) != NULL ) {
		agp -> argv = NULL;
		agp -> argb = NULL;

		if ( setupArgument ( agp, line ) == NULL ) {
			freeArgument ( agp );
			agp = NULL;
		}
	}

	return agp;
}

/*
 *
 */

void	freeArgument ( Argument *agp ) {

	if ( agp != NULL ) {
		if ( agp -> argv != NULL )	{
			xfree ( agp -> argv );
		}

		if ( agp -> argb != NULL ) {
			freeStrList ( agp -> argb );
		}

		xfree ( agp );
	}

}

/*
 *
 */

void	printArgument ( Argument *agp, char *sep ) {

	if ( agp != NULL ) {
		printf ( "argc = %d\n", agp -> argc );

		if ( agp -> argv != NULL ) {
			int i;

			printf ( "argv :" );
			for ( i = 0; i < agp -> argc; i++ ) {
				printf ( " %s", agp -> argv[i] );
			}
			printf ( "\n" );
		}

		if ( agp -> argb != NULL ) {
			printf ( "argb :" );
			printStrList ( agp -> argb, sep );
			printf ( "\n" );
		}
	}
}

/*
 *
 */

char	*assingArgument ( char *buf, char *src, Argument *agp ) {
	int ch;
	char *p = buf;

	while ( ( ch = *src++ ) != EOS ) {
		if ( ch == FORMAT_CHAR ) {
			if ( *src != EOS ) {
				ch = *src++;
				if ( isdigit ( ch ) ) {
					int n = ch - '0' - 1;

					if ( n < agp -> argc ) {
						char *q = agp -> argv[ n ];

						while ( *q != EOS ) {
							*p++ = *q++;
						}
					}
				} else {
					*p++ = ch;
				}
			}
		} else {
			*p++ = ch;
		}
	}

	*p = EOS;

	return buf;
}

/*
 *
 */

