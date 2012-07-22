/*
 *	dofigure.c
 */

#include <stdio.h>
#include <ctype.h>

/*
 *
 */

#include "eos.h"
#include "infile.h"
#include "strlist.h"
#include "figure.h"
#include "figurelist.h"
#include "thecommands.h"
#include "flowcom.h"
#include "token.h"
#include "dofigure.h"

/*
 *
 */

/*
 *
 */

static	FigureList	*top = NULL;

/*
 *
 */

#define	NAME_SIZE	128
#define	FLAG_SIZE	16

void	doFigure ( char *pList ) {
	char	name[ NAME_SIZE ];
	int		params;
	char	flag[ FLAG_SIZE ];
	Coord	size;
	char	line[ LINE_LEN ];
	StrList	*slp = allocStrList();
    int		l;

	sscanf ( pList, "%s %lf %lf %s %d", name, &size.x, &size.y, flag, &params );

	while ( readline_infile ( line, LINE_LEN ) != NULL ) {
		if ( isspace ( line[ 0 ] ) ) {
			appendStrList ( slp, line + 1 );
		} else {
			unget_infile ( line );
			break;
		}
	}

	if ( top == NULL ) {
		top = allocFigureList();
	}

	insertFigureList (
		top,
		allocFigure (
			name, 
			allocFlowCom ( name, params, size, str2bool(flag), DRAW ),
			slp
		)
	 );

}

/*
 *
 */

void	dumpFigure( void ) {

	if ( top != NULL ) {
		printFigureList ( top, "\n" );
	}

}

/*
 *
 */

Figure	*findFigure ( char *name ) {
	Figure	*find = NULL;

	if ( top != NULL ) {
		find = findFigureList ( top, name );
	}

	return find;
}

/*
 *
 */

FlowCom	*getFigureCommand ( char *name ) {
	Figure	*find = findFigure ( name );

	if ( find != NULL ) {
		return find -> command;
	}

	return NULL;
}

/*
 *
 */

