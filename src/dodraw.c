/*
 *	dodraw.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *
 */

#include "eos.h"
#include "integer.h"
#include "coord.h"
#include "errout.h"
#include "texpicture.h"
#include "vcell.h"
#include "vlist.h"
#include "strlist.h"
#include "token.h"
#include "drawfigure.h"
#include "figure.h"
#include "tempfile.h"
#include "argument.h"
#include "dofigure.h"
#include "dodraw.h"

/*
 *
 */

void putInnerCircle ( double cx, double cy, double r ) {

	putCirclePicture ( cx, cy, r * 2.0 );
}

void putInnerOval ( double cx, double cy, double rx, double ry ) {

	putOvalPicture ( cx, cy, rx * 2.0, ry * 2.0 );
}

void putInnerBezier ( double p0x, double p0y, double p1x, double p1y, double p2x, double p2y ) {

//  fprintf ( stderr, "(%f,%f) - (%f,%f) - (%f,%f)\n", p0x, p0y, p1x, p1y, p2x, p2y );

	putBezierPicture ( p0x, p0y, p1x, p1y, p2x, p2y );
}

void putInnerText ( double px, double py, char *text ) {

//  fprintf ( stderr, "(%f,%f) [%f,%f] %s\n", px, py, sx, sy, text );

	putBoxTitlePicture( px, py, 0, 0, text );
}

/*
 * @@@ How to get m/n ( which is nearest x/y and m,n in 0-15 ) from x/y ?
 */

void putInnerLine ( double sx, double sy, double ex, double ey ) {
	int	xs = doubleToInt100(ex) - doubleToInt100(sx);
	int	ys = doubleToInt100(ey) - doubleToInt100(sy);

//  fprintf ( stderr, "(%f,%f) - (%f,%f)\n", sx, sy, ex, ey );
	tdprintf ( "line (%f,%f) - (%f,%f)\n", sx, sy, ex, ey );

	if ( xs == 0 ) {
		putVerticalLinePicture ( sx, sy, ey - sy );
	} else if ( ys == 0 ) {
		putHorizontalLinePicture ( sx, sy, ex - sx );
	} else {
		int g = gcm ( xs, ys );

		//		fprintf ( stderr, "sx = %f, ex = %f, xs = %d\n", sx, ex, xs );
		//		fprintf ( stderr, "sy = %f, ey = %f, ys = %d\n", sy, ey, ys );
		//		fprintf ( stderr, "g = %d\n", g );

		if ( g > 1 ) {
			xs = xs / g;
			ys = ys / g;
		}

		if ( xs > TEX_INCLINATION_MAX )	{
			tdprintf ( "xs=%d\n", xs );
			errout ( W_ASPECT );
			xs = TEX_INCLINATION_MAX;
	    } else if ( - xs > TEX_INCLINATION_MAX )	{
			tdprintf ( "xs=%d\n", xs );
			errout ( W_ASPECT );
			xs = - TEX_INCLINATION_MAX;
		}

    	if ( ys > TEX_INCLINATION_MAX ) {
			tdprintf ( "ys=%d\n", ys );
			errout ( W_ASPECT );
			ys = TEX_INCLINATION_MAX;
	    } else if ( - ys > TEX_INCLINATION_MAX ) {
			tdprintf ( "ys=%d\n", ys );
			errout ( W_ASPECT );
			ys = - TEX_INCLINATION_MAX;
		}

		tdprintf ( "[Innerline] (%f,%f)[%d,%d]{%f}\n", sx, sy, xs, ys, ex - sx );

		putLinePicture ( sx, sy, xs, ys, ex - sx );
	}

}

/*
 *
 */

void drawInnerLine ( Coord curCoord, Coord curSize, double sx, double sy, double ex, double ey ) {

	if ( sx < 0.0 ) {
		sx = curCoord.x + curSize.x + sx;
	} else {
		sx = curCoord.x + sx;
	}

	if ( sy < 0.0 ) {
		sy = curCoord.y + curSize.y + sy;
	} else {
		sy = curCoord.y + sy;
	}

	if ( ex <= 0.0 ) {
		ex = curCoord.x + curSize.x + ex;
	} else {
		ex = curCoord.x + ex;
	}

	if ( ey <= 0.0 ) {
		ey = curCoord.y + curSize.y + ey;
	} else {
		ey = curCoord.y + ey;
	}

	putInnerLine ( sx, sy, ex, ey );

}

/*
 *
 */

void putInnerBox ( double sx, double sy, double ex, double ey )	{
  //  fprintf ( stderr, "(%f,%f)-(%f,%f)\n", sx, sy, ex, ey );

	putInnerLine ( sx, sy, sx, ey );
	putInnerLine ( ex, sy, ex, ey );

	putInnerLine ( sx, sy, ex, sy );
	putInnerLine ( sx, ey, ex, ey );
}

/*
 *
 */

enum {
  //
  POS_ER = -1,
  //
  POS_SX = 0,
  POS_SY = 1,
  POS_EX = 2,
  POS_EY = 3,
  //
  POS_MX = 4,
  POS_MY = 5,
  //
  POS_HXP = 6,
  POS_HXN = 7,
  POS_HYP = 8,
  POS_HYN = 9
  //
};

static double posToLocateOffset ( int pos, Coord curCoord, Coord curSize, double ofs ) {
	double loc;

	switch ( pos ) {
	case POS_SX:
		loc = curCoord.x + ofs;
		break;
	case POS_EY:
		loc = curCoord.y - curSize.y - ofs;
		break;
	case POS_EX:
		loc = curCoord.x + curSize.x + ofs;
		break;
	case POS_SY:
		loc = curCoord.y - ofs;
		break;
	case POS_MX:
		loc = curCoord.x + (curSize.x/2) + ofs;
		break;
	case POS_MY:
		loc = curCoord.y - (curSize.y/2) - ofs;
		break;
	case POS_HXP:
	case POS_HYP:
		loc = ofs;
		break;
	case POS_HXN:
		loc = curSize.x/2 + ofs;
		break;
	case POS_HYN:
		loc = curSize.y/2 + ofs;
		break;
	}

	return loc;
}

static double posToLocate ( int pos, Coord curCoord, Coord curSize ) {

	return posToLocateOffset ( pos, curCoord, curSize, 0.0 );
}

/*
 *
 */

#define	TBL_S	0		/* s */
#define	TBL_E	1		/* e */
#define	TBL_M	2		/* m */
#define	TBL_P	3		/* . */

static int tbl[4][10] = {
//POS_SX,POS_SY,POS_EX,POS_EY,POS_MX,POS_MY,POS_HXP,POS_HXN,POS_HYP,POS_HYN
 {POS_SX,POS_SY,POS_SX,POS_SY,POS_MX,POS_MY,POS_HXP,POS_HXP,POS_HYP,POS_HYP},//s
 {POS_EX,POS_EY,POS_EX,POS_EY,POS_MX,POS_MY,POS_HXN,POS_HXN,POS_HYN,POS_HYN},//e
 {POS_MX,POS_MY,POS_MX,POS_MY,POS_MX,POS_MY,POS_HXP,POS_HXN,POS_HYP,POS_HYN},//m
 {POS_SX,POS_SY,POS_EX,POS_EY,POS_MX,POS_MY,POS_HXN,POS_HXN,POS_HYN,POS_HYN} //.
};

static double getPosition ( char *ptr, int pos, Coord curCoord, Coord curSize ) {
	double	loc = posToLocate ( pos, curCoord, curSize );
	double	ofs = 0.0;
	int		sign = 1;

	switch ( *ptr ) {
	case '.':

	case 's':
	case 't':
	case 'l':

	case 'm':
	case 'c':

	case 'e':
	case 'b':
	case 'r':
		switch ( *ptr ) {
		case 's':
		case 'l':
		case 't':
			pos = tbl[TBL_S][pos];
			break;
		case 'e':
		case 'r':
		case 'b':
			pos = tbl[TBL_E][pos];
			break;
		case 'c':
		case 'm':
			pos = tbl[TBL_M][pos];
			break;
		case '.':
		 	pos = tbl[TBL_P][pos];
			break;
		}
		loc = posToLocate ( pos, curCoord, curSize );
		break;
	case '-':
	case 'B':
	case 'R':
	case 'E':
		sign = -1;	// negative
		// break;
	case 'S':
	case 'T':
	case 'L':
	case '+':
		ptr++;		// skip sign
		// break;
	default:		// maybe number..
		ofs = atof ( ptr );
		if ( sign > 0 ) {
			loc = posToLocateOffset ( tbl[TBL_S][pos], curCoord, curSize,   ofs );
		} else {
			loc = posToLocateOffset ( tbl[TBL_E][pos], curCoord, curSize, - ofs );
		}
		break;
	}

	return loc;
}

/*
 *
 */

static char *parseParameter ( double param[], int initial[], int format[], char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	char	token[ TOKEN_SIZE ];
	int		i;

	for ( i = 0; initial[ i ] != POS_ER; i++ ) {
		param[ i ] = posToLocate ( initial[ i ], curCoord, curSize );
	}

	for ( i = 0; format[ i ] != POS_ER; i++ ) {
	  if ( ( line = getToken ( token, line ) ) != NULL ) {
		param[ i ] = getPosition ( token, format[ i ], curCoord, curSize );
	  } else {
		break;
	  }
	}

	return line;
}

/*
 *
 */

#define	AS(X)	((sizeof(X)/sizeof(X[0]))-1)	/* Array Size */

static void drawLineBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int f[] = { POS_SX, POS_SY, POS_EX, POS_EY, POS_ER };
	double p[AS(f)];

	parseParameter ( p, f, f, line, agp, curCoord, curSize );

	putInnerLine ( p[0], p[1], p[2], p[3] );
}

static void drawCircleBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int i[] = { POS_HXN, POS_MX, POS_MY, POS_ER };
	static int f[] = { POS_HXP, POS_MX, POS_MY, POS_ER };
	double p[AS(i)];

	parseParameter ( p, i, f, line, agp, curCoord, curSize );

	putInnerCircle ( p[1], p[2], p[0] );
}

static void drawOvalBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int i[] = { POS_HXN, POS_HYN, POS_MX, POS_MY, POS_ER };
	static int f[] = { POS_HXP, POS_HYP, POS_MX, POS_MY, POS_ER };
	double p[AS(i)];

	parseParameter ( p, i, f, line, agp, curCoord, curSize );

	putInnerOval ( p[2], p[3], p[0], p[1] );
}

static void drawBezierBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int i[] = {POS_SX, POS_SY, POS_SX, POS_EY, POS_EX, POS_SY, POS_ER};
	static int f[] = {POS_SX, POS_SY, POS_SX, POS_EY, POS_EX, POS_SY, POS_ER};
	double p[AS(i)];

	tdprintf ( "bezier %s\n", line );

	parseParameter ( p, i, f, line, agp, curCoord, curSize );

	putInnerBezier ( p[0], p[1], p[2], p[3], p[4], p[5] );
}

static void drawTextBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int i[] = {POS_SX, POS_SY, POS_ER};
	static int f[] = {POS_SX, POS_SY, POS_ER};
	double p[AS(i)];

	tdprintf ( "text %s\n", line );

	line = parseParameter ( p, i, f, line, agp, curCoord, curSize );

	putInnerText ( p[0], p[1], line );
}

static void drawBoxBody ( char *line, Argument *agp, Coord curCoord, Coord curSize ) {
	static int i[] = {POS_SX, POS_SY, POS_EX, POS_EY, POS_ER};
	static int f[] = {POS_SX, POS_SY, POS_EX, POS_EY, POS_ER};
	double p[AS(i)];

	tdprintf ( "box %s\n", line );

	parseParameter ( p, i, f, line, agp, curCoord, curSize );

	putInnerBox ( p[0], p[1], p[2], p[3] );
}

/*
 *
 */

static void drawBody ( Coord curCoord, Coord curSize, StrList *slp, Argument *agp, StrList *rec );

static	void doDrawFigure ( Figure *find, char *pList, Coord curCoord, Coord curSize, StrList *rec ) {
	Argument	*agp;

	if ( ( agp = allocArgument ( pList ) ) != NULL ) {
		drawBody ( curCoord, curSize, find -> body, agp, rec );
		freeArgument ( agp );
	}
}
/*
 *
 */

typedef	void (*DrawFunc)( char *line, Argument *agp, Coord curCoord, Coord curSize );

static struct	{
  char *name;
  DrawFunc	drawFunc;
} figureTable [] = {
	{	"line",		drawLineBody	},
	{	"circle",	drawCircleBody	},
	{	"oval",		drawOvalBody	},
	{	"bezier",	drawBezierBody	},
	{	"text",		drawTextBody	},
	{	"box",		drawBoxBody		},
	{	NULL,		NULL			}
};

static void doDrawBody ( char *line, Argument *agp, Coord curCoord, Coord curSize, StrList *rec ) {
	char	token[ TOKEN_SIZE ];
	char	strbuf[ ARG_LINE ];

	line = assingArgument ( strbuf, line, agp );

	if ( ( line = getToken ( token, line ) ) != NULL ) {
		Figure	*find;
		int		i;

		for ( i = 0; figureTable[i].name != NULL; i++ ) {
			if ( !strcmp ( figureTable[i].name, token ) ) {
				figureTable[i].drawFunc ( line, agp, curCoord, curSize );
				return;
			}
		}

		if ( ( find = findFigure ( token ) ) != NULL ) {
			if ( findStrList ( rec, token ) == NULL ) {
				insertStrList ( rec, token );
				tdprintf ( "FIGURE %s\n", token );
				doDrawFigure ( find, line, curCoord, curSize, rec );
				removeTopStrList ( rec );
			} else {
				errout ( E_RECURSIVE_FIGURE, token );
			}
		} else {
			errout ( E_UNDEFINED_FIGURE, token );
		}
	}
}

/*
 * drawBody
 */

static void drawBody ( Coord curCoord, Coord curSize, StrList *slp, Argument *agp, StrList *rec ) {
	char	*line;
	VCell	*vcp;

	if ( slp != NULL ) {
		for ( vcp = slp -> top; vcp != NULL; vcp = vcp -> next ) {
			line = (char *)(((VCell *) vcp) -> value);
			if ( line != NULL ) {
				doDrawBody ( line, agp, curCoord, curSize, rec );
			}
		}
	}
}

/*
 *
 */

void	doDraw ( char *name, char *pList, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {
	Figure	*find = findFigure ( name );
	StrList	*rec = allocStrList();

	if ( find != NULL ) {
		if ( find -> command -> hasText ) {
			drawMakePut ( curCoord, curSize, curBoxPos, curPos );
		}

		insertStrList ( rec, name );
		tdprintf ( "FIGURE %s\n", name );
		doDrawFigure ( find, pList, curCoord, curSize, rec );
		removeTopStrList ( rec );

		checkTextPicBoundsRng ( curCoord, curSize );

	}

	freeStrList ( rec );

}

/*
 *
 */

