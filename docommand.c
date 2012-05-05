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
#include "docommand.h"

/*
 *
 */

#define MAX_BOXES 2048  /* could not possibly have more than this */

/* state / position tracking variables */

Coord Coords[MAX_BOXES] = {{0,0}};  /* just initialise first coord */
int CurCoord = 0;
int CurTrack = ArrowS;
int CurDirec = DownD;
Coord CurScale = {1.,1.};
Coord CurSize = {0.,0.};
ATag *CurTag = NULL;
char CurPos[20] = "[c]";
char CurBoxPos[20] = "[c]";
float TrackX = 1.;
float TrackY = 1.;

float VertGap=1.;
float HorzGap=1.;

int doCommand ( FlowCom *comPtr, Param pList ) {
/*
output the LaTeX bits for this command, updating the coords, Coord list
etc. as required
*/

    static int init = 0;
    ATag *tempTag;
    char params[10][80];
    char *trackStr = "vector";
    float dimen,x,y,x1,y1;
    int i,xs,ys;
    Coord t;
	char leader[ SPACEING_LENGTH ];
	char tailer[ SPACEING_LENGTH ];
               
    dimen = 0.;
    
    params[0][0]= EOS;  /* so Up / Down / Left / Right can find *'s for line
			drawing                                            */

    if (CurTrack == LineS) trackStr = "line";

    if (comPtr -> hasText) {
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

    if ( !init && CurSize.x == 0. && CurSize.y == 0. ) {
	    CurSize.x = comPtr -> size.x * CurScale.x;
	    CurSize.y = comPtr -> size.y * CurScale.y;
    }

    if ( init && ( comPtr -> size.x != 0 || comPtr -> size.y != 0 ) ) {

	switch ( CurDirec ) {

	case DownD :

            t.x = Coords[CurCoord].x+CurSize.x/2;
            t.y = Coords[CurCoord].y-CurSize.y;

            if (CurTrack != NoneS)	{
			  push_linethickness();
			  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		               t.x,
                       t.y,
                       trackStr,
                       0,-1,
                       VertGap);
			  pop_linethickness();
			}

            checkPicBounds ( &t );

            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   comPtr -> size.x*CurScale.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y
                                   - VertGap;
                                   
            checkPicBounds ( Coords + CurCoord + 1 );
            
            break;

        case UpD :

            t.x = Coords[CurCoord].x+CurSize.x/2;
            t.y = Coords[CurCoord].y;
            
            if (CurTrack != NoneS) {
			  push_linethickness();
			  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
					  t.x,
					  t.y,
					  trackStr,
					  0,1,
					  VertGap);
			  pop_linethickness();
			}

            checkPicBounds ( &t );
            
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   comPtr -> size.x*CurScale.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y + 
                                   comPtr -> size.y*CurScale.y
				   + VertGap;
            checkPicBounds ( Coords + CurCoord + 1 );
            
            break;

        case RightD :

            t.x = Coords[CurCoord].x+CurSize.x;
            t.y = Coords[CurCoord].y-CurSize.y/2;

            if (CurTrack != NoneS) {
			  push_linethickness();
			  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
                       t.x,
                       t.y,
                       trackStr,
                       1,0,
                       HorzGap);
			  pop_linethickness();
			}

            checkPicBounds ( &t );
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x
                                   + HorzGap;
            Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2 +
                                   comPtr -> size.y*CurScale.y / 2;

            checkPicBounds ( Coords + CurCoord + 1 );
            break;

	case LeftD :

            t.x = Coords[CurCoord].x;
            t.y = Coords[CurCoord].y-CurSize.y/2;

            if (CurTrack != NoneS) {
			  push_linethickness();
			  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
                       t.x,
                       t.y,
                       trackStr,
                       -1,0,
                       HorzGap);
			  pop_linethickness();
			}

            checkPicBounds ( &t );

            Coords[CurCoord+1].x = Coords[CurCoord].x - 
                                   comPtr -> size.x*CurScale.x
				   - HorzGap;
			Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2 +
				   comPtr -> size.y*CurScale.y / 2;

            checkPicBounds ( Coords + CurCoord + 1 );
            
	    break;

	default:
	    break;
	}
	CurCoord++;
	CurSize.x = comPtr -> size.x*CurScale.x;
	CurSize.y = comPtr -> size.y*CurScale.y;

    }

	tprintf("%%%s %f,%f\n",
		comPtr -> name,
		comPtr -> size.x,
			comPtr -> size.y );

    switch ( comPtr -> command ) {

    case Skip :
	if (sscanf(pList,"%f %f %f %f",&x,&y,&x1,&y1) == 4) {
	    VertGap = y;
	    HorzGap = x;
	    TrackX = x1;
	    TrackY = y1;
	}
	break;

    case TxtPos :
	CurPos[0]=CurBoxPos[0]=leader[0]=tailer[0]=EOS;
	sscanf(pList,"%s %s %s %s",CurPos,CurBoxPos,leader,tailer);
	setSpace ( leader,tailer );

	break;

    case Box :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\framebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
               Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	    doText();
	    tprintf("}}}\n");
    
        checkPicBoundsRng (
            Coords[CurCoord].x,
            Coords[CurCoord].y-CurSize.y,
            CurSize.x,
            CurSize.y
        );

	break;

    case Tilt :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	tprintf("}}}\n");

	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+1./6.*CurSize.y,
		       Coords[CurCoord].y,
		       1,0,
		       CurSize.x);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y,
		       Coords[CurCoord].y-CurSize.y,
		       1,0,
		       CurSize.x);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y,
		       Coords[CurCoord].y-CurSize.y,
		       1,3,
		       CurSize.y*1./3.);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y+CurSize.x,
		       Coords[CurCoord].y-CurSize.y,
		       1,3,
		       CurSize.y*1./3.);

    checkPicBoundsRng (
        Coords[CurCoord].x-1./6.*CurSize.y,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x + 1./6.*CurSize.y,
        CurSize.y
    );

	break;

    case Drum :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	tprintf("}}}\n");
	/* up */
	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)}\n",
		       Coords[CurCoord].x+CurSize.x/2.0,
		       Coords[CurCoord].y-0.5,
		       CurSize.x,1.0);
	/* down */
	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)[b]}\n",
		       Coords[CurCoord].x+CurSize.x/2.0,
		       Coords[CurCoord].y-CurSize.y+0.5,
		       CurSize.x,1.0);
	/* left */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y+0.5,
		       0,1,
		       CurSize.y-1.0);
	/* right */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x,
		       Coords[CurCoord].y-CurSize.y+0.5,
		       0,1,
		       CurSize.y-1.0);

    checkPicBoundsRng (
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y-1.5,
        CurSize.x,
        CurSize.y+2.0
    );

	break;

    case Call :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	tprintf("}}}\n");

	/* up */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y,
		       1,0,
		       CurSize.x);
	/* down */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       1,0,
		       CurSize.x);
	/* left */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       0,1,
		       CurSize.y);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+0.1,
		       Coords[CurCoord].y-CurSize.y,
		       0,1,
		       CurSize.y);
	/* right */
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x,
		       Coords[CurCoord].y-CurSize.y,
		       0,1,
		       CurSize.y);
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x-0.1,
		       Coords[CurCoord].y-CurSize.y,
		       0,1,
		       CurSize.y);

    checkPicBoundsRng (
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x,
        CurSize.y
    );

	break;

    case Text :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	tprintf("}}}\n");

    checkPicBoundsRng (
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x,
        CurSize.y
    );
	break;

    case Oval :
	init=1;
	tprintf("\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y-CurSize.y/2,
		       CurSize.x,
		       CurSize.y );
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos );
	doText();
	tprintf("}}}\n");
    checkPicBoundsRng (
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x,
        CurSize.y
    );

	break;

    case Choice :

	init=1;
    
    xs = (int)CurSize.x; ys = (int)CurSize.y; 
    
    for (i = (xs>ys) ? xs : ys; i>1; i--) {
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
		      Coords[CurCoord].x,
		      Coords[CurCoord].y-CurSize.y/2,
		      xs,ys,CurSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x,
		      Coords[CurCoord].y-CurSize.y/2,
		      xs,-ys,CurSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x+CurSize.x,
		      Coords[CurCoord].y-CurSize.y/2,
		      -xs,-ys,CurSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x+CurSize.x,
		      Coords[CurCoord].y-CurSize.y/2,
		      -xs,ys,CurSize.x/2
		      );
	tprintf("\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos );
	doText();
        tprintf("}}}\n");
        
        sscanf(pList,"%s %s %s %s",params[0],params[1],params[2],params[3]);

        if (params[0][0] != '.')
	    tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
                           Coords[CurCoord].x+
                           CurSize.x*0.65,
                           Coords[CurCoord].y,
                           params[0]
                          );
                           
        if (params[1][0] != '.')
            tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[rt]{%s}}\n",
                           Coords[CurCoord].x,
                           Coords[CurCoord].y-
                           CurSize.y/2.*0.7,
                           params[1]
                          );
                           
        if (params[2][0] != '.')
            tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
                           Coords[CurCoord].x+
			   CurSize.x,
                           Coords[CurCoord].y-
			   CurSize.y/2.*0.7,
                           params[2]
                          );
                           
        if (params[3][0] != '.')
            tprintf("\\put(%3.4f,%3.4f){\\makebox(0,0)[lb]{%s}}\n",
                           Coords[CurCoord].x+
                           CurSize.x*0.65,
                           Coords[CurCoord].y-
                           CurSize.y,
                           params[3]
                          );
                           
    checkPicBoundsRng (
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x,
        CurSize.y
    );
        break;

    case SetTrack :
        sscanf(pList,"%s",params[0]);
        
	if ( strcmp("arrow",params[0]) == 0)
            CurTrack = ArrowS;
	if ( strcmp("line",params[0]) == 0)
            CurTrack = LineS;
        if ( strcmp("none",params[0]) == 0)
            CurTrack = NoneS;
    
        break;

    case SetWidth :
        sscanf ( pList, "%s", params[ 0 ] );

		if ( strcmp ( "thick", params [ 0 ] ) == 0 ) {
			set_linelinethickness ( LINE_WIDTH_THICK );
		} else if ( strcmp ( "thin", params [ 0 ] ) == 0 ) {
			set_linelinethickness ( LINE_WIDTH_THIN );
		} else {
			set_linelinethickness ( atof ( params [ 0 ] ) );
		}
        break;

    case Scale :
        sscanf(pList,"%f %f",&CurScale.x,&CurScale.y);
        break;

    case Tag :
        tempTag = (ATag*)malloc(sizeof(ATag));
        tempTag->size.x = CurSize.x;
        tempTag->size.y = CurSize.y;
        tempTag->pos.x = Coords[CurCoord].x;
        tempTag->pos.y = Coords[CurCoord].y;
        tempTag->next = CurTag;
	CurTag = tempTag;
        break;

    case ToTag :
    
        if ( CurTag == NULL ) {
		  	errout ( E_TAG_STACK_EMPTY );
            break;
        }
        tempTag = CurTag;
        CurSize.x = tempTag->size.x;
        CurSize.y = tempTag->size.y;
        Coords[CurCoord].x = tempTag->pos.x;
        Coords[CurCoord].y = tempTag->pos.y;
        
        CurTag = tempTag->next;
        
        free(tempTag);
        
        break;

    case Right :
	CurDirec = RightD;
	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackX;
	    if (CurTrack != NoneS) {
		  push_linethickness();
		  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x,
		       Coords[CurCoord].y-CurSize.y/2,
		       (params[0][0]=='*')?"vector":"line",
		       1,0,
		       dimen);
		  pop_linethickness();
		}

	    Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x +
				   dimen;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2;

	    CurCoord++;

	    CurSize = comPtr -> size;
	}
        checkPicBounds ( &( Coords[ CurCoord ] ) );
	break;

    case Down :
	CurDirec = DownD;

	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackY;
	    if (CurTrack != NoneS)	{
		  push_linethickness();
		  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y-CurSize.y,
		       (params[0][0]=='*')?"vector":"line",
		       0,-1,
		       dimen);
		  pop_linethickness();
		}

	    Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
				   comPtr -> size.x / 2;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y
				   - dimen;

	    CurCoord++;

	    CurSize = comPtr -> size;
	}
        checkPicBounds ( &( Coords[ CurCoord ] ) );

	break;

    case Left :
	CurDirec = LeftD;
	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackX;
	    if (CurTrack != NoneS) {
		  push_linethickness();
		  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y/2,
		       (params[0][0]=='*')?"vector":"line",
		       -1,0,
		       dimen);
		  pop_linethickness();
		}

	    Coords[CurCoord+1].x = Coords[CurCoord].x -
				   dimen;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2;

	    CurCoord++;

	    CurSize = comPtr -> size;
	}
        checkPicBounds ( &( Coords[ CurCoord ] ) );
	break;

    case Up :
	CurDirec = UpD;
	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackY;
	    if (CurTrack != NoneS) {
  		  push_linethickness();
		  tprintf("\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y,
                       (params[0][0]=='*')?"vector":"line",
                       0,1,
                       dimen);
  		  pop_linethickness();
		}
                       
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   comPtr -> size.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y +
                                   dimen;
                                   
            CurCoord++;
                                   
            CurSize = comPtr -> size;
        }
        checkPicBounds ( &( Coords[ CurCoord ] ) );
        break;

    case Comment :
	break;

    default:
		errout ( E_UNKNOWN_COMMAND, comPtr -> command );
        return 0;
    }
    
    if ( comPtr -> command != Scale ) {
		CurScale.x = CurScale.y = 1.;
	}

    return 1;
}

/*
 *
 */
