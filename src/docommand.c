/*
 *	docommand.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *
 */

#include "eos.h"
#include "bool.h"
#include "coord.h"
#include "flowcom.h"
#include "param.h"
#include "tracksymb.h"
#include "thecommands.h"
#include "direcs.h"
#include "atag.h"
#include "boundingbox.h"
#include "tempfile.h"
#include "errout.h"
#include "dotext.h"
#include "linethickness.h"
#include "pic.h"
#include "drawarrow.h"
#include "figure.h"
#include "token.h"
#include "domark.h"
#include "docommand.h"

/*
 *
 */

#define MAX_BOXES	2048  /* could not possibly have more than this */
#define	POS_SIZE	20

#define	MAX_PARAMS	10
#define	PARAM_LENGTH	80

/*
 *
 */

enum {
  PARAM_RIGHT = 0,
  PARAM_LEFT = 1,
  PARAM_THICK = 2,
  PARAM_THIN = 3,
  NOT_PARAM = 4
};

#define	strlcmp(X,Y)	strncmp(X,Y,strlen(Y))

static int parseArgument ( char *param, char *pList ) {
	static struct {
		char *name;
		int code;
	} tbl[] = {
		{	"right",	PARAM_RIGHT	},
		{	"left",		PARAM_LEFT	},
		{	"thick",	PARAM_THICK	},
		{	"thin",		PARAM_THIN	},
		{	NULL,		NOT_PARAM	}
	};
	int	i;

	sscanf ( pList, "%s", param );

	for ( i = 0; tbl[i].name != NULL; i++ ) {
		if ( !strlcmp( param, tbl[i].name ) ) {
			break;
		}
	}

	return tbl[i].code;
}

/*
 *
 */

int doCommand ( FlowCom *comPtr, Param comArg ) {

	/*
	output the LaTeX bits for this command, updating the coords, Coord list
	etc. as required
	*/

	/* state / position tracking variables */

	static Coord coords[ MAX_BOXES ] = {
		{	0,	0	}
	};  /* just initialise first coord */
	static int curCoord = 0;

	static int curTrack = ARROW_SYMBOL;
	static int curDirec = DOWN_DIR;

	static Coord curScale = {	1.,	1.	};
	static Coord curSize = {	0.,	0.	};

	static char curPos[ POS_SIZE ] = "[c]";
	static char curBoxPos[ POS_SIZE ] = "[c]";

	static double trackX = 1.;
	static double trackY = 1.;

	static double vertGap = 1.;
	static double horzGap = 1.;

	/*
	 *
	 */

    static int init = FALSE;

	/*
	 *
	 */

    char params[ MAX_PARAMS ][ PARAM_LENGTH ];
    double dimen = 0.;
	double x,y,x1,y1;
    Coord t;
    Coord s;
	char leader[ SPACEING_LENGTH ];
	char tailer[ SPACEING_LENGTH ];
	TheCommands	curCommand;
	char *pList = comArg;

	int nParam = 0;
	int dFlag = 0;

    params[ 0 ][ 0 ] = EOS;  /* so Up / Down / Left / Right can find *'s for line drawing */

	switch ( comPtr -> command ) {
	case CHOICE:
		if ( sscanf(pList,"%s %s %s %s %lf %lf",
				params[0],
			    params[0],
			    params[0],
			    params[0],
				&x,&y) == 6 ) {
			comPtr -> size.x = x;
			comPtr -> size.y = y;
		}
		dFlag = 1;
		nParam = 2;
		break;
	case FIGURE:
		/*
		if ( sscanf(pList,"%s %lf %lf",
	   				params[0],
 				&x,&y) == 3 ) {
			comPtr -> size.x = x;
			comPtr -> size.y = y;
			nParam = 2;
		}
		//		fprintf ( stderr, "%s, %f, %f\n", params[0], x, y );
		*/
		dFlag = 1;
		nParam = 2;
		break;
    case COMMENT:
		break;
	case DRAW:
		dFlag = 1;
		nParam = 2;
		break;
	default:
		if ( comPtr -> hasText ) {
			if ( sscanf(pList,"%lf %lf",&x,&y) == 2 ) {
				comPtr -> size.x = x;
				comPtr -> size.y = y;
			}
		}
		dFlag = 1;
		nParam = 2;
		break;
	}

    if ( !init && curSize.x == 0. && curSize.y == 0. ) {
		curSize.x = comPtr -> size.x * curScale.x;
		curSize.y = comPtr -> size.y * curScale.y;
    }

    if ( init && ( comPtr -> size.x != 0 || comPtr -> size.y != 0 ) ) {

		switch ( curDirec ) {
	    case RIGHT_DIR:
		case DOWN_DIR:
		case LEFT_DIR:
		case UP_DIR:
			switch ( curDirec ) {
		    case RIGHT_DIR:
				dimen = horzGap;
				t.x = coords[ curCoord ].x + curSize.x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = horzGap;
				s.y = comPtr -> size.y * curScale.y / 2;
				break;

			case DOWN_DIR:
				dimen = vertGap;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y - curSize.y;
				s.x = - comPtr -> size.x * curScale.x / 2;
				s.y = - vertGap;
				break;

			case LEFT_DIR:
				dimen = horzGap;
				t.x = coords[ curCoord ].x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = - comPtr -> size.x * curScale.x - horzGap;
				s.y =   comPtr -> size.y * curScale.y / 2;
				break;

			case UP_DIR:
				dimen = vertGap;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y;
				s.x = - comPtr -> size.x * curScale.x / 2;
				s.y =   comPtr -> size.y * curScale.y + vertGap;
				break;

			}

			drawArrow ( curTrack, t, curDirec, dimen );

			checkPicBounds ( &t );

			coords[ curCoord + 1 ].x = t.x + s.x;
			coords[ curCoord + 1 ].y = t.y + s.y;

			checkPicBounds ( coords + curCoord + 1 );

		    break;

		default:
			break;
		}

		curCoord++;

		curSize.x = comPtr -> size.x * curScale.x;
		curSize.y = comPtr -> size.y * curScale.y;

	}

	/* dump command */

	if ( dFlag == 1 ) {
		tprintf ( "%%%s", comPtr -> name );
		if ( nParam == 2 ) {
			tprintf ( " %f,%f",
				comPtr -> size.x,
				comPtr -> size.y );
		}
		tprintf ( "\n" );
	}

	/* do command */

    switch ( curCommand = comPtr -> command ) {

    case SKIP:
		if ( sscanf ( pList, "%lf %lf %lf %lf", &x, &y, &x1, &y1 ) == 4 ) {
		    vertGap = y;
		    horzGap = x;
		    trackX = x1;
		    trackY = y1;
		}
		break;

    case TXT_POS:
		curPos[ 0 ] = curBoxPos[ 0 ] = leader[ 0 ] = tailer[ 0 ] = EOS;
		sscanf ( pList, "%s %s %s %s", curPos, curBoxPos, leader, tailer );
		setSpace ( leader, tailer );
		break;

    case BOX:
		init = TRUE;

		drawFramePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawBox ( coords[curCoord], curSize );

		break;

    case TILT:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawTilt ( coords[curCoord], curSize );

		break;

    case DRUM:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawDrum ( coords[curCoord], curSize );

		if ( *pList != EOS ) {
			char *p = skipToken ( skipToken ( pList ) );	/* skip 2 params */

			if ( *p != EOS ) {
				getLastText ( params[0], p );
				drawTitleText ( coords[curCoord], curSize, params[0] );
			}
		}

		break;

    case CALL:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawCall ( coords[curCoord], curSize );

		break;

    case TEXT:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawBox ( coords[curCoord], curSize );

		break;

    case OVAL:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawOval ( coords[curCoord], curSize );

		break;

    case CHOICE:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawChoice ( coords[curCoord], curSize );

		params[0][0] = '.';
		params[1][0] = '.';
		params[2][0] = '.';
		params[3][0] = '.';

        sscanf ( pList, "%s %s %s %s",
			params[0], params[1], params[2], params[3] );

		drawSelect ( coords[curCoord], curSize,
			params[0], params[1], params[2], params[3] );

        break;

    case SET_TRACK:
        sscanf ( pList, "%s", params[ 0 ] );

		curTrack = stringToTrackSymb ( params[ 0 ] );

        break;

    case SET_WIDTH:
		switch ( parseArgument ( params[ 0 ], pList ) ) {
		case PARAM_THICK:
			set_linelinethickness ( LINE_WIDTH_THICK );
			break;
		case PARAM_THIN:
			set_linelinethickness ( LINE_WIDTH_THIN );
			break;
		default:		
			set_linelinethickness ( atof ( params [ 0 ] ) );
			break;
		}
        break;

    case SCALE:
        sscanf ( pList, "%lf %lf", &curScale.x, &curScale.y );
        break;

    case TAG:
		pushATag ( &curSize, coords + curCoord );
        break;

    case TO_TAG:
		popATag ( &curSize, coords + curCoord );
        break;

		/* Direction */
    case TURN:
		pList = skipSpace ( pList );

		switch ( parseArgument ( params[ 0 ], pList ) ) {
		case PARAM_RIGHT:
			curCommand = dir2command(turnDirecRight(curDirec));
			pList = skipToken ( pList );
			break;
		case PARAM_LEFT:
			curCommand = dir2command(turnDirecLeft(curDirec));
			pList = skipToken ( pList );
			break;
		default:
			curCommand = dir2command(turnDirecRight(curDirec));
			break;
		}
		params[ 0 ][ 0 ] = EOS;

		// break;
    case RIGHT:
    case DOWN:
    case LEFT:
    case UP:

		curDirec = command2dir(curCommand);

				/* if argments exists */
		if ( sscanf ( pList, "%lf %19s", &dimen, params[0] ) >= 1 ) {
			init = TRUE;

			switch ( curCommand ) {
			case RIGHT:
				dimen *= trackX;
				t.x = coords[ curCoord ].x + curSize.x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = dimen;
				s.y = 0;
				break;

			case DOWN:
				dimen *= trackY;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y - curSize.y;
				s.x = - comPtr -> size.x / 2;
				s.y = - dimen;
				break;

			case LEFT:
				dimen *= trackX;
				t.x = coords[ curCoord ].x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = - dimen;
				s.y = 0;
				break;

			case UP:
				dimen *= trackY;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y;
				s.x = - comPtr -> size.x / 2;
				s.y = dimen;
				break;
			}

			drawLine ( curTrack, params[0][0], t, curDirec, dimen );

			coords[ curCoord + 1 ].x = t.x + s.x;
			coords[ curCoord + 1 ].y = t.y + s.y;

			curCoord++;

			curSize = comPtr -> size;
		}

        checkPicBounds ( coords + curCoord );
		break;

    case FIGURE:
		doFigure ( pList );
		break;

    case DRAW:
		init = TRUE;
		doDraw ( comPtr -> name, pList, coords[ curCoord ], curSize, curBoxPos, curPos );
		break;

	case MARK:
		doMark ( pList, coords + curCoord, curDirec );
		break;

	case GO:
		doGo ( pList, coords + curCoord, curDirec );
		break;

    case COMMENT:
		break;

    default:
		errout ( E_UNKNOWN_COMMAND, comPtr -> command );
        return 0;
    }
    
    if ( comPtr -> command != SCALE ) {
		curScale.x = curScale.y = 1.;
	}

    return 1;
}

/*
 *
 */
