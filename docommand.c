/*
 *	docommand.c
 */

#include <stdio.h>
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
static int curTrack = ArrowS;
static int curDirec = DownD;
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

int doCommand ( FlowCom *comPtr, Param pList ) {
/*
output the LaTeX bits for this command, updating the coords, Coord list
etc. as required
*/

    static int init = FALSE;
    ATag *tempTag;
    char params[ MAX_PARAMS ][ PARAM_LENGTH ];
    float dimen,x,y,x1,y1;
    int i,xs,ys;
    Coord t;
    Coord s;
	char leader[ SPACEING_LENGTH ];
	char tailer[ SPACEING_LENGTH ];
			   
    dimen = 0.;
    
    params[ 0 ][ 0 ] = EOS;  /* so Up / Down / Left / Right can find *'s for line drawing */

    if ( comPtr -> hasText ) {
	if (( comPtr -> command != Choice && sscanf(pList,"%f %f",&x,&y) == 2) ||
	    ( comPtr -> command == Choice && sscanf(pList,"%s %s %s %s %f %f",
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
	    case RightD:
		case DownD:
		case LeftD:
		case UpD:
			switch ( curDirec ) {
		    case RightD:
				dimen = horzGap;
				t.x = coords[curCoord].x + curSize.x;
				t.y = coords[curCoord].y - curSize.y / 2;
				s.x = horzGap;
				s.y = comPtr -> size.y * curScale.y / 2;
			break;

			case DownD:
				dimen = vertGap;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y - curSize.y;
				s.x = - comPtr -> size.x * curScale.x / 2;
				s.y = - vertGap;
				break;

			case LeftD:
				dimen = horzGap;
				t.x = coords[curCoord].x;
				t.y = coords[curCoord].y - curSize.y / 2;
				s.x = - comPtr -> size.x * curScale.x - horzGap;
				s.y =   comPtr -> size.y * curScale.y / 2;
				break;

			case UpD:
				dimen = vertGap;
				t.x = coords[curCoord].x + curSize.x / 2;
				t.y = coords[curCoord].y;
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

    switch ( comPtr -> command ) {

    case Skip:
		if ( sscanf ( pList, "%f %f %f %f", &x, &y, &x1, &y1 ) == 4 ) {
		    vertGap = y;
		    horzGap = x;
		    trackX = x1;
		    trackY = y1;
		}
		break;

    case TxtPos:
		curPos[ 0 ] = curBoxPos[ 0 ] = leader[ 0 ] = tailer[ 0 ] = EOS;
		sscanf ( pList,"%s %s %s %s", curPos, curBoxPos, leader, tailer );
		setSpace ( leader, tailer );
		break;

    case Box :
		init = TRUE;

		drawFramePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawBox ( coords[curCoord], curSize );

		break;

    case Tilt:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawTilt ( coords[curCoord], curSize );

		break;

    case Drum:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawDrum ( coords[curCoord], curSize );

		break;

    case Call:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawCall ( coords[curCoord], curSize );

		break;

    case Text:
		init = TRUE;

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
		drawBox ( coords[curCoord], curSize );

		break;

    case Oval:
		init = TRUE;

		drawOval ( coords[curCoord], curSize );
		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );

		break;

    case Choice:
		init = TRUE;
    
    	xs = (int)curSize.x; ys = (int)curSize.y; 
    
    	for ( i = (xs > ys) ? xs : ys; i > 1; i-- ) {
        	if ( (xs % i) == 0 && (ys % i) == 0 ) {
				xs /= i;
				ys /= i;
				i = (xs>ys) ? xs : ys;
	        }
	    }
    
    if (xs>6) {
		errout ( W_ASPECT );
        xs = 6;
    }
    if (ys>6) {
		errout ( W_ASPECT );
		ys = 6;
    }
    
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      coords[curCoord].x,
		      coords[curCoord].y-curSize.y/2,
		      xs,ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      coords[curCoord].x,
		      coords[curCoord].y-curSize.y/2,
		      xs,-ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      coords[curCoord].x+curSize.x,
		      coords[curCoord].y-curSize.y/2,
		      -xs,-ys,curSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      coords[curCoord].x+curSize.x,
		      coords[curCoord].y-curSize.y/2,
		      -xs,ys,curSize.x/2
		      );

		drawMakePut ( coords[curCoord], curSize, curBoxPos, curPos );
  
        sscanf(pList,"%s %s %s %s",params[0],params[1],params[2],params[3]);

        if (params[0][0] != '.')
	    tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
						   coords[curCoord].x+
						   curSize.x*0.65,
						   coords[curCoord].y,
						   params[0]
						  );
						   
        if (params[1][0] != '.')
			tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[rt]{%s}}\n",
						   coords[curCoord].x,
						   coords[curCoord].y-
						   curSize.y/2.*0.7,
						   params[1]
						  );
						   
        if (params[2][0] != '.')
			tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
						   coords[curCoord].x+
			   curSize.x,
						   coords[curCoord].y-
			   curSize.y/2.*0.7,
						   params[2]
						  );
						   
        if (params[3][0] != '.')
			tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lb]{%s}}\n",
						   coords[curCoord].x+
						   curSize.x*0.65,
						   coords[curCoord].y-
						   curSize.y,
						   params[3]
						  );
						   
    checkPicBoundsRng (
        coords[curCoord].x,
        coords[curCoord].y-curSize.y,
        curSize.x,
        curSize.y
    );
        break;

    case SetTrack:
        sscanf ( pList, "%s", params[ 0 ] );

		if ( !strcmp ( "arrow", params[ 0 ] ) ) {
			curTrack = ArrowS;
		} else if ( !strcmp ( "line", params[ 0 ] ) ) {
			curTrack = LineS;
		} else if ( !strcmp ( "none", params[ 0 ] ) ) {
			curTrack = NoneS;
		}
    
        break;

    case SetWidth:
        sscanf ( pList, "%s", params[ 0 ] );

		if ( !strcmp ( "thick", params [ 0 ] ) ) {
			set_linelinethickness ( LINE_WIDTH_THICK );
		} else if ( !strcmp ( "thin", params [ 0 ] ) ) {
			set_linelinethickness ( LINE_WIDTH_THIN );
		} else {
			set_linelinethickness ( atof ( params [ 0 ] ) );
		}
        break;

    case Scale:
        sscanf ( pList, "%f %f", &curScale.x, &curScale.y );
        break;

    case Tag:
        tempTag = xalloc( ATag );
        tempTag -> size.x = curSize.x;
        tempTag -> size.y = curSize.y;
        tempTag -> pos.x = coords[ curCoord ].x;
        tempTag -> pos.y = coords[ curCoord ].y;
        tempTag -> next = curTag;
		curTag = tempTag;
        break;

    case ToTag:
    
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
    case Right:
    case Down:
    case Left:
    case Up:

	    switch ( comPtr -> command ) {
		case Right:
			curDirec = RightD;
			break;
	    case Down:
			curDirec = DownD;
			break;
	    case Left:
			curDirec = LeftD;
			break;
	    case Up:
			curDirec = UpD;
			break;
		}

				/* if argments exists */
		if ( sscanf ( pList, "%f %19s", &dimen, params[0] ) >= 1 ) {
			init = TRUE;

			switch ( comPtr -> command ) {
			case Right:
				dimen *= trackX;
				t.x = coords[ curCoord ].x + curSize.x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = dimen;
				s.y = 0;
				break;

			case Down:
				dimen *= trackY;
				t.x = coords[ curCoord ].x + curSize.x / 2;
				t.y = coords[ curCoord ].y - curSize.y;
				s.x = - comPtr -> size.x / 2;
				s.y = - dimen;
				break;

			case Left:
				dimen *= trackX;
				t.x = coords[ curCoord ].x;
				t.y = coords[ curCoord ].y - curSize.y / 2;
				s.x = - dimen;
				s.y = 0;
				break;

			case Up:
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

    case Comment:
		break;

    default:
		errout ( E_UNKNOWN_COMMAND, comPtr -> command );
        return 0;
    }
    
    if ( comPtr -> command != Scale ) {
		curScale.x = curScale.y = 1.;
	}

    return 1;
}

/*
 *
 */
