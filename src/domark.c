/*
 *	domark.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 *
 */

#include "eos.h"
#include "token.h"
#include "coord.h"
#include "integer.h"

#include "param.h"
#include "flowcom.h"
#include "getcommand.h"

#include "mark.h"
#include "marklist.h"
#include "domark.h"

/*
 *
 */

#define	MARKING_DEBUG	0

#if	MARKING_DEBUG

#define	MARK( CC )	marking ( CC -> x, CC -> y )

static void marking ( double x, double y ) {
  char line[ 100 ];

  sprintf ( line, "\\put(%f,%f){\\oval(0.3000,0.30000)}%%%%\n", x, y );
  tprintf ( line );
  sprintf ( line, "\\put(%f,%f){\\oval(0.5000,0.50000)}%%%%\n", x, y );
  tprintf ( line );

}

#else

#define	MARK( CC )

#endif

/*
 *
 */

static	MarkList	*table = NULL;

/*
 *
 */

void	doMark ( char *pline, Coord *curCoord, int curDirec ) {
	char	token[ TOKEN_SIZE ];

	MARK( curCoord );

	if ( ( pline = getToken ( token, pline ) ) != NULL ) {

	  if ( table == NULL ) {
		table = allocMarkList();
	  }

	  if ( table != NULL ) {
		appendMarkList ( table, allocMark ( token, allocCoord ( curCoord -> x, curCoord -> y ), curDirec ) );
	  }
	}
}

/*
 *
 */

void	doGo ( char *pline, Coord *curCoord, int curDirec ) {
	char	token[ TOKEN_SIZE ];

	MARK( curCoord );

	if ( ( pline = getToken ( token, pline ) ) != NULL ) {
	  if ( table != NULL ) {
		Mark *mp = findMarkList ( table, token );
		if ( mp != NULL ) {
		    Param	params;
		    FlowCom	*comPtr = NULL;
			char line[ 100 ];
			double skip = 4.0;

			int dx = doubleToInt100 ( mp -> coord -> x - curCoord -> x );
			int dy = doubleToInt100 ( mp -> coord -> y - curCoord -> y );

			pline = skipSpace ( pline );

			if ( *pline == '.' || isdigit ( *pline ) ) {
				pline = getToken ( token, pline );
				skip = atof ( token );
			}

			if ( dx == 0 ) {
				if ( dy > 0 ) {
					sprintf ( line, "Left %f", skip );
					dx = doubleToInt100(skip);
				} else {	
					sprintf ( line, "Right %f", skip );
					dx = -doubleToInt100(skip);
				}
				comPtr = getCommand ( line, params );
				doCommand ( comPtr, params );
			}

			if ( dy > 0 ) {
				sprintf ( line, "Up %f", int100ToDouble (dy) );
			} else {
				sprintf ( line, "Down %f", int100ToDouble (-dy) );
			}

			comPtr = getCommand ( line, params );
			doCommand ( comPtr, params );

			if ( ( pline = getToken ( token, pline ) ) != NULL ) {
				if ( *token == '*' ) {
					token[1] = EOS;
				} else {
					token[0] = EOS;
				}
			} else {
				token[0] = EOS;
			}

			if ( dx > 0 ) {
				sprintf ( line, "Right %f %s", int100ToDouble (dx), token );
			} else {
				sprintf ( line, "Left %f %s", int100ToDouble (-dx), token );
			}

			comPtr = getCommand ( line, params );
			doCommand ( comPtr, params );
		}
	  }
	}
}

/*
 *
 */
