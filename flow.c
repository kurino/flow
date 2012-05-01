#define VERSION "0.99f"

/*

flow.c 22/1/93 (C) 2005 Terry Brown

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*

flow - a flow-chart -> LaTeX generator.  Parses a file in a flow-chart
specification language, then produces a corresponding LaTeX
pic environment.

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef int bool;

#define TRUE 1
#define FALSE 0

typedef struct {float x,y;} coord;

typedef struct {char name[80];
		int Params;
		coord size;
		bool HasText;
	       } FlowCom;

#define ParamLen 120
#define LineLen 120

typedef char param[ParamLen];

#define MaxBoxes 2048  /* could not possibly have more than this */

#define Commands 16

FlowCom fcom[Commands] = {
  { "SetTrack", 1, {0,0}, FALSE },
  { "Up",       1, {0,0}, FALSE },
  { "Down",     1, {0,0}, FALSE },
  { "Left",     1, {0,0}, FALSE },
  { "Right",    1, {0,0}, FALSE },
  { "Box",      0, {4,2}, TRUE  },
  { "Oval",     0, {4,2}, TRUE  },
  { "Choice",   4, {4,4}, TRUE  },
  { "Tag",      0, {0,0}, FALSE },
  { "ToTag",    0, {0,0}, FALSE },
  { "Scale",    2, {0,0}, FALSE },
  { "Tilt",     0, {4,2}, TRUE  },
  { "Text",     0, {4,2}, TRUE  },
  { "TxtPos",   4, {0,0}, FALSE },
  { "Skip",     2, {0,0}, FALSE },
  { "%",        0, {0,0}, FALSE }
};

typedef enum {SetTrack,
	      Up,
	      Down,
	      Left,
	      Right,
	      Box,
	      Oval,
	      Choice,
	      Tag,
	      ToTag,
	      Scale,
	      Tilt,
	      Text,
	      TxtPos,
	      Skip,
	      Comment
	     }  TheCommands;

typedef enum {ArrowS, LineS, NoneS} trackSymb;
typedef enum {UpD, DownD, LeftD, RightD} direcs;

typedef struct ATAG {coord pos;
		coord size;
		struct ATAG *next;
	       } aTag;

typedef struct {
    coord min;
    coord max;
} boundingBox;


/* state / position tracking variables */

boundingBox pic = {{0,0},{0,0}};
coord Coords[MaxBoxes] = {{0,0}};  /* just initialise first coord */
int CurCoord = 0;
int CurTrack = ArrowS;
int CurDirec = DownD;
coord CurScale = {1.,1.};
coord CurSize = {0.,0.};
aTag *CurTag = NULL;
char CurPos[20] = "[c]";
char CurBoxPos[20] = "[c]";
char leader[20]="";
char tailer[20]="";
float TrackX = 1.;
float TrackY = 1.;
int InputLine = 0;
char line[LineLen];

float VertGap=1.;
float HorzGap=1.;

FILE *inFile, *outFile;  /* global input output streams */

int doText();

void checkBounds(boundingBox *b, coord *c) {

    if (b->min.x > c->x) b->min.x = c->x;
    if (b->max.x < c->x) b->max.x = c->x;
    if (b->min.y > c->y) b->min.y = c->y;
    if (b->max.y < c->y) b->max.y = c->y;
}
void checkBoundsRng(
    boundingBox *b, 
    float x,
    float y,
    float sx,
    float sy
    ) {

    if (b->min.x > x) b->min.x = x;
    if (b->max.x < x+sx) b->max.x = x+sx;
    if (b->min.y > y) b->min.y = y;
    if (b->max.y < y+sy) b->max.y = y+sy;
}

int getCommand(char line[], param plist) {
/*
tries to interpret the next line of inFile as a command, returns -1 if it can't
*/

    int i=0, command = -1;

    while (i<Commands) {

	if ( strncmp(fcom[i].name,line,strlen(fcom[i].name)) == 0) {
	   command = i;
	    break;
	}
	i++;
    }

    if (command == -1) {
	if (!feof(inFile) && line[0] != '\n')
	    fprintf(stderr,"flow error : can't interpret line %d\n",InputLine);
	return command;
    }

    strncpy(plist, line+strlen(fcom[command].name), ParamLen);

    return command;

}


int doCommand(int command, param pList) {
/*
output the LaTeX bits for this command, updating the coords, coord list
etc. as required
*/

    static int init = 0;
    aTag *tempTag;
    char params[10][80];
    char *trackStr = "vector";
    float dimen,x,y,x1,y1;
    int i,xs,ys;
    coord t;
               
    dimen = 0.;
    
    params[0][0]=0;  /* so Up / Down / Left / Right can find *'s for line
			drawing                                            */


    if (CurTrack == LineS) trackStr = "line";

    if (fcom[command].HasText) {
	if ((command != Choice && sscanf(pList,"%f %f",&x,&y) == 2) ||
	    (command == Choice && sscanf(pList,"%s %s %s %s %f %f",
				       params[0],
				       params[0],
				       params[0],
				       params[0],
				       &x,&y) == 6)) {
	    fcom[command].size.x = x;
	    fcom[command].size.y = y;
	}
    }

    if (!init && CurSize.x == 0. && CurSize.y == 0.) {
	    CurSize.x = fcom[command].size.x*CurScale.x;
	    CurSize.y = fcom[command].size.y*CurScale.y;
    }

    if ( init && (fcom[command].size.x != 0 || fcom[command].size.y != 0 )) {

	switch (CurDirec) {

	case DownD :

            t.x = Coords[CurCoord].x+CurSize.x/2;
            t.y = Coords[CurCoord].y-CurSize.y;

            if (CurTrack != NoneS)
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		               t.x,
                       t.y,
                       trackStr,
                       0,-1,
                       VertGap);
                       
            checkBounds(&pic,&t);                       

            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   fcom[command].size.x*CurScale.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y
                                   - VertGap;
                                   
            checkBounds(&pic,Coords+CurCoord+1);
            
            break;

        case UpD :

            t.x = Coords[CurCoord].x+CurSize.x/2;
            t.y = Coords[CurCoord].y;
            
            if (CurTrack != NoneS)
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
                       t.x,
                       t.y,
                       trackStr,
		       0,1,
                       VertGap);

            checkBounds(&pic,&t);                       
            
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   fcom[command].size.x*CurScale.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y + 
                                   fcom[command].size.y*CurScale.y
				   + VertGap;
            checkBounds(&pic,Coords+CurCoord+1);
            
            break;

        case RightD :

            t.x = Coords[CurCoord].x+CurSize.x;
            t.y = Coords[CurCoord].y-CurSize.y/2;

            if (CurTrack != NoneS)
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
                       t.x,
                       t.y,
                       trackStr,
                       1,0,
                       HorzGap);

            checkBounds(&pic,&t);                       
            
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x
                                   + HorzGap;
            Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2 +
                                   fcom[command].size.y*CurScale.y / 2;

            checkBounds(&pic,Coords+CurCoord+1);
            
            break;

	case LeftD :

            t.x = Coords[CurCoord].x;
            t.y = Coords[CurCoord].y-CurSize.y/2;

            if (CurTrack != NoneS)
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
                       t.x,
                       t.y,
                       trackStr,
                       -1,0,
                       HorzGap);

            checkBounds(&pic,&t);                       
            
            Coords[CurCoord+1].x = Coords[CurCoord].x - 
                                   fcom[command].size.x*CurScale.x
				   - HorzGap;
	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2 +
				   fcom[command].size.y*CurScale.y / 2;

            checkBounds(&pic,Coords+CurCoord+1);
            
	    break;

	default:
	    break;
	}
	CurCoord++;
	CurSize.x = fcom[command].size.x*CurScale.x;
	CurSize.y = fcom[command].size.y*CurScale.y;

    }

    switch (command) {

    case Skip :
	if (sscanf(pList,"%f %f %f %f",&x,&y,&x1,&y1) == 4) {
	    VertGap = y;
	    HorzGap = x;
	    TrackX = x1;
	    TrackY = y1;
	}
	break;

    case TxtPos :
	CurPos[0]=CurBoxPos[0]=leader[0]=tailer[0]=0;
	sscanf(pList,"%s %s %s %s",CurPos,CurBoxPos,leader,tailer);
	break;

    case Box :
	init=1;
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\framebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
               Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	    doText();
	    fprintf(outFile,"}}}\n");
    
        checkBoundsRng(
            &pic,
            Coords[CurCoord].x,
            Coords[CurCoord].y-CurSize.y,
            CurSize.x,
            CurSize.y
        );

	break;

    case Tilt :
	init=1;
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	fprintf(outFile,"}}}\n");

	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+1./6.*CurSize.y,
		       Coords[CurCoord].y,
		       1,0,
		       CurSize.x);
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y,
		       Coords[CurCoord].y-CurSize.y,
		       1,0,
		       CurSize.x);
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y,
		       Coords[CurCoord].y-CurSize.y,
		       1,3,
		       CurSize.y*1./3.);
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x-1./6.*CurSize.y+CurSize.x,
		       Coords[CurCoord].y-CurSize.y,
		       1,3,
		       CurSize.y*1./3.);

    checkBoundsRng(
        &pic,
        Coords[CurCoord].x-1./6.*CurSize.y,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x + 1./6.*CurSize.y,
        CurSize.y
    );

	break;

    case Text :
	init=1;
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos);
	doText();
	fprintf(outFile,"}}}\n");

    checkBoundsRng(
        &pic,
        Coords[CurCoord].x,
        Coords[CurCoord].y-CurSize.y,
        CurSize.x,
        CurSize.y
    );
	break;

    case Oval :
	init=1;
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\oval(%3.4f,%3.4f)}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y-CurSize.y/2,
		       CurSize.x,
		       CurSize.y );
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos );
	doText();
	fprintf(outFile,"}}}\n");
    checkBoundsRng(
        &pic,
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
        fprintf(stderr,"Flow warning - illegal Choice aspect ratio\n");
        xs = 6;
    }
    if (ys>6) {
        fprintf(stderr,"Flow warning - illegal Choice aspect ratio\n");
        ys = 6;
    }
    
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x,
		      Coords[CurCoord].y-CurSize.y/2,
		      xs,ys,CurSize.x/2
		      );
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x,
		      Coords[CurCoord].y-CurSize.y/2,
		      xs,-ys,CurSize.x/2
		      );
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x+CurSize.x,
		      Coords[CurCoord].y-CurSize.y/2,
		      -xs,-ys,CurSize.x/2
		      );
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\line(%d,%d){%3.4f}}\n",
		      Coords[CurCoord].x+CurSize.x,
		      Coords[CurCoord].y-CurSize.y/2,
		      -xs,ys,CurSize.x/2
		      );
	fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(%3.4f,%3.4f)%s{\\shortstack%s{\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y,
		       CurSize.x,
		       CurSize.y,
		       CurBoxPos,
		       CurPos );
	doText();
        fprintf(outFile,"}}}\n");
        
        sscanf(pList,"%s %s %s %s",params[0],params[1],params[2],params[3]);

        if (params[0][0] != '.')
	    fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
                           Coords[CurCoord].x+
                           CurSize.x*0.65,
                           Coords[CurCoord].y,
                           params[0]
                          );
                           
        if (params[1][0] != '.')
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(0,0)[rt]{%s}}\n",
                           Coords[CurCoord].x,
                           Coords[CurCoord].y-
                           CurSize.y/2.*0.7,
                           params[1]
                          );
                           
        if (params[2][0] != '.')
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(0,0)[lt]{%s}}\n",
                           Coords[CurCoord].x+
			   CurSize.x,
                           Coords[CurCoord].y-
			   CurSize.y/2.*0.7,
                           params[2]
                          );
                           
        if (params[3][0] != '.')
            fprintf(outFile,"\\put(%3.4f,%3.4f){\\makebox(0,0)[lb]{%s}}\n",
                           Coords[CurCoord].x+
                           CurSize.x*0.65,
                           Coords[CurCoord].y-
                           CurSize.y,
                           params[3]
                          );
                           
    checkBoundsRng(
        &pic,
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

    case Scale :
        sscanf(pList,"%f %f",&CurScale.x,&CurScale.y);
        break;

    case Tag :
        tempTag = (aTag*)malloc(sizeof(aTag));
        tempTag->size.x = CurSize.x;
        tempTag->size.y = CurSize.y;
        tempTag->pos.x = Coords[CurCoord].x;
        tempTag->pos.y = Coords[CurCoord].y;
        tempTag->next = CurTag;
	CurTag = tempTag;
        break;

    case ToTag :
    
        if (CurTag == NULL) {
            fprintf(stderr,"flow error - Tag stack empty \n");
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
	    if (CurTrack != NoneS)
	    fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x,
		       Coords[CurCoord].y-CurSize.y/2,
		       (params[0][0]=='*')?"vector":"line",
		       1,0,
		       dimen);

	    Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x +
				   dimen;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2;

	    CurCoord++;

	    CurSize = fcom[command].size;
	}
        checkBounds(&pic,&(Coords[CurCoord]));
	break;

    case Down :
	CurDirec = DownD;

	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackY;
	    if (CurTrack != NoneS)
	    fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y-CurSize.y,
		       (params[0][0]=='*')?"vector":"line",
		       0,-1,
		       dimen);

	    Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
				   fcom[command].size.x / 2;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y
				   - dimen;

	    CurCoord++;

	    CurSize = fcom[command].size;
	}
        checkBounds(&pic,&(Coords[CurCoord]));

	break;

    case Left :
	CurDirec = LeftD;
	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackX;
	    if (CurTrack != NoneS)
	    fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x,
		       Coords[CurCoord].y-CurSize.y/2,
		       (params[0][0]=='*')?"vector":"line",
		       -1,0,
		       dimen);

	    Coords[CurCoord+1].x = Coords[CurCoord].x -
				   dimen;

	    Coords[CurCoord+1].y = Coords[CurCoord].y - CurSize.y/2;

	    CurCoord++;

	    CurSize = fcom[command].size;
	}
        checkBounds(&pic,&(Coords[CurCoord]));
	break;

    case Up :
	CurDirec = UpD;
	if (sscanf(pList,"%f %19s",&dimen,params[0])>=1) {
	    init=1;
	    dimen *= TrackY;
	    if (CurTrack != NoneS)
	    fprintf(outFile,"\\put(%3.4f,%3.4f){\\%s(%d,%d){%3.4f}}\n",
		       Coords[CurCoord].x+CurSize.x/2,
		       Coords[CurCoord].y,
                       (params[0][0]=='*')?"vector":"line",
                       0,1,
                       dimen);
                       
            Coords[CurCoord+1].x = Coords[CurCoord].x + CurSize.x/2 -
                                   fcom[command].size.x / 2;

            Coords[CurCoord+1].y = Coords[CurCoord].y +
                                   dimen;
                                   
            CurCoord++;
                                   
            CurSize = fcom[command].size;
        }
        checkBounds(&pic,&(Coords[CurCoord]));
        break;

    case Comment :
	break;

    default:
        fprintf(stderr,"flow error : unknown command %4d\n",command);
        return 0;
    }
    
    if (command != Scale) CurScale.x = CurScale.y = 1.;

    if (fcom[command].HasText == FALSE) {
        line[0]=0;
        fgets(line,LineLen,inFile);
        InputLine++;
    }

    return 1;

}

int doText() {
/*
output text for those commands that require it, spit out all lines that start
with white space (0x20, 0x09)
*/

    int i;

    line[0]=0;
    fgets(line,LineLen,inFile);
    InputLine++;

    while (!feof(inFile) && (
	   line[0] == 0x20 ||
	   line[0] == 0x09 )
	  ) {

	    line[strlen(line)-1]=0;
	    for (i=0; i<strlen(line) &&
		      (line[i] == 0x09 || line[i] == 0x20); i++);

           fprintf(outFile,"%s%s%s",leader,line+i,tailer);
	    line[0]=0;
	    fgets(line,LineLen,inFile);
	    InputLine++;

	   if (line[0] == 0x20 || line[0] == 0x09 )
	       fprintf(outFile,"\\\\\n");
	   else
	       fprintf(outFile,"\n");

       }

    return 1;
}

void applyPicWrapper(FILE *inFile, FILE *outFile) {

    char buf[1024];

    fprintf(outFile,"\\begin{picture}(%f,%f)(%f,%f)\n",
            pic.max.x - pic.min.x,
            pic.max.y - pic.min.y,
            pic.min.x,
            pic.min.y
          );
    
    while (!feof(inFile)) {
    
        fwrite(buf,fread(buf,1,1024,inFile),1,outFile);
    
    }
    
    fprintf(outFile,"\\end{picture}\n");
}

int main(int argc, char **argv) {

    param params;
    int command=0;
    char tmpfileNm[80];


    inFile = stdin; outFile = stdout;
    
    tmpnam(tmpfileNm);
    outFile = fopen(tmpfileNm,"w");

    if (argc > 1) {
	inFile = fopen(argv[1],"r");
	if (inFile == NULL) {
	    fprintf(stderr,"Couldn't open input file %s\n",argv[1]);
	    exit(0);
	}
    }

    line[0]=0;
    fgets(line,LineLen,inFile);
    InputLine++;

    fprintf(outFile,"%% picture environment flowchart generated by flow ");
    fprintf(outFile,"%s\n",VERSION);

    while (command != -1) {

	command = getCommand(line,params);

	if (command != -1)
	     if (!doCommand(command, params)) return 10;
    }

    fclose(inFile);
    fclose(outFile);

    outFile = stdout;
    if (argc > 2) {
	outFile = fopen(argv[2],"w");
	if (outFile == NULL) {
	    fprintf(stderr,"Couldn't open output file %s\n",argv[2]);
	    fclose(inFile);
	    exit(0);
	}
    }
    
    inFile = fopen(tmpfileNm,"r");
    
    applyPicWrapper(inFile,outFile);
    if (outFile != stdout) fclose(outFile);
    fclose(inFile);
    remove(tmpfileNm);

    exit(0);

    return 0;    /* just to suppress the warning */

}
