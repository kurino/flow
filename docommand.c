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
#include "xalloc.h"
#include "figure.h"
#include "token.h"
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

/* state / position tracking variables */

static Coord coords[ MAX_BOXES ] = {
	{	0,	0	}
};  /* just initialise first coord */
static int curCoord = 0;
static int curTrack = ARROW_SYMBOL;
static int curDirec = DOWN_DIR;
static Coord curScale = {	1.,	1.	};
static Coord curSize = {	0.,	0.	};
static ATag *curTag = NULL;
static char curPos[ POS_SIZE ] = "[c]";
static char curBoxPos[ POS_SIZE ] = "[c]";

static float trackX = 1.;
static float trackY = 1.;

static float vertGap = 1.;
static float horzGap = 1.;

/*
 *
 */

int doCommand ( FlowCom *comPtr, Param comArg ) {
/*
output the LaTeX bits for this command, updating the coords, Coord list
etc. as required
*/

    static int init = FALSE;
    ATag *tempTag;
    char params[ MAX_PARAMS ][ PARAM_LENGTH ];
    float dimen,x,y,x1,y1;
    Coord t;
    Coord s;
	char leader[ SPACEING_LENGTH ];
	char tailer[ SPACEING_LENGTH ];
	TheCommands	curCommand;
	char *pList = comArg;

    dimen = 0.;

    params[ 0 ][ 0 ] = EOS;  /* so Up / Down / Left / Right can find *'s for line drawing */

    if ( comPtr -> hasText && comPtr -> command != DRAW ) {
		if (( comPtr -> command != CHOICE && sscanf(pList,"%f %f",&x,&y) == 2) ||
		    ( comPtr -> command == CHOICE && sscanf(pList,"%s %s %s %s %f %f",
				       params[0],
				       params[0],
				       params[0],
				       params[0],
				       &x,&y) == 6)) {
	    	comPtr -> size.x = x;
		    comPtr -> size.y = y;
		}
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

	tprintf ( "%%%s %f,%f\n",
		comPtr -> name,
		comPtr -> size.x,
		comPtr -> size.y );

	/* do command */

    switch ( curCommand = comPtr -> command ) {

    case SKIP:
		if ( sscanf ( pList, "%f %f %f %f", &x, &y, &x1, &y1 ) == 4 ) {
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
        sscanf ( pList, "%s", params[ 0 ] );

		if ( !strcmp ( "thick", params [ 0 ] ) ) {
			set_linelinethickness ( LINE_WIDTH_THICK );
		} else if ( !strcmp ( "thin", params [ 0 ] ) ) {
			set_linelinethickness ( LINE_WIDTH_THIN );
		} else {
			set_linelinethickness ( atof ( params [ 0 ] ) );
		}
        break;

    case SCALE:
        sscanf ( pList, "%f %f", &curScale.x, &curScale.y );
        break;

    case TAG:
        tempTag = xalloc( ATag );
        tempTag -> size.x = curSize.x;
        tempTag -> size.y = curSize.y;
        tempTag -> pos.x = coords[ curCoord ].x;
        tempTag -> pos.y = coords[ curCoord ].y;
        tempTag -> next = curTag;
		curTag = tempTag;
        break;

    case TO_TAG:
    
        if ( curTag == NULL ) {
		  	errout ( E_TAG_STACK_EMPTY );
			break;
        }

        tempTag = curTag;

        curSize.x = tempTag -> size.x;
        curSize.y = tempTag -> size.y;
        coords[ curCoord ].x = tempTag -> pos.x;
        coords[ curCoord ].y = tempTag -> pos.y;

        curTag = tempTag -> next;

        xfree( tempTag );

        break;

		/* Direction */
    case TURN:
		pList = skipSpace ( pList );
		sscanf ( pList, "%s", params[ 0 ] );
		if ( !strncmp ( params[ 0 ], "right", strlen ( "right" ) ) ) {
		  curCommand = RIGHT;
		  pList = skipToken ( pList );
		} else if ( !strncmp ( params[ 0 ], "left", strlen ( "left" ) ) ) {
		  curCommand = LEFT;
		  pList = skipToken ( pList );
		} else {
		  curCommand = RIGHT;
		}

		switch ( curCommand ) {
	    case RIGHT:
			switch ( curDirec ) {
	    	case RIGHT_DIR:
				curCommand = DOWN;
				break;
			case DOWN_DIR:
				curCommand = LEFT;
				break;
			case LEFT_DIR:
				curCommand = UP;
				break;
			case UP_DIR:
				curCommand = RIGHT;
				break;
			}
			break;
	    case LEFT:
			switch ( curDirec ) {
	    	case RIGHT_DIR:
				curCommand = UP;
				break;
			case DOWN_DIR:
				curCommand = RIGHT;
				break;
			case LEFT_DIR:
				curCommand = DOWN;
				break;
			case UP_DIR:
				curCommand = LEFT;
				break;
			}
		}
		// break;
    case RIGHT:
    case DOWN:
    case LEFT:
    case UP:

	    switch ( curCommand ) {
		case RIGHT:
			curDirec = RIGHT_DIR;
			break;
	    case DOWN:
			curDirec = DOWN_DIR;
			break;
	    case LEFT:
			curDirec = LEFT_DIR;
			break;
	    case UP:
			curDirec = UP_DIR;
			break;
		}

				/* if argments exists */
		if ( sscanf ( pList, "%f %19s", &dimen, params[0] ) >= 1 ) {
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
