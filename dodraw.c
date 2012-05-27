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
#include "coord.h"
#include "errout.h"
#include "texpicture.h"
#include "vcell.h"
#include "vlist.h"
#include "strlist.h"
#include "token.h"
#include "drawfigure.h"
#include "figure.h"
#include "dofigure.h"
#include "dodraw.h"

/*
 *
 */

#define	ARGS		10
#define	ARG_LINE	1024

/*
 *
 */

static int gcm ( int a, int b ) {

	if ( a < 0 ) {
		return gcm ( -a, b );
	} else if ( b < 0 ) {
		return gcm ( a, -b );
	} else if ( b > 0 ) {
		return gcm ( b, a % b );
	} else {
		return a;
	}
}


/*
 *
 */

void putInnerCircle ( float cx, float cy, float r ) {

	putCirclePicture ( cx, cy, r * 2.0 );
}

void putInnerOval ( float cx, float cy, float rx, float ry ) {

	putOvalPicture ( cx, cy, rx * 2.0, ry * 2.0 );
}

void putInnerBezier ( float p0x, float p0y, float p1x, float p1y, float p2x, float p2y ) {

	putBezierPicture ( p0x, p0y, p1x, p1y, p2x, p2y );
}

/*
 *
 */

void putInnerLine ( float sx, float sy, float ex, float ey ) {

  //  fprintf ( stderr, "(%f,%f) - (%f,%f)\n", sx, sy, ex, ey );

	if ( sx == ex ) {
		if ( ey > sy ) {
			putVerticalLinePicture ( sx, sy, ey - sy );
		} else {
			putVerticalLinePicture ( sx, ey, sy - ey );
		}
	} else if ( sy == ey ) {
		if ( ex > sx ) {
			putHorizontalLinePicture ( sx, sy, ex - sx );
		} else {
			putHorizontalLinePicture ( ex, sy, sx - ex );
		}
	} else {
		float px = sx;
		float py = sy;
		float l;
		int	xs = (int)( ex - sx );
		int	ys = (int)( ey - sy );
		int g = gcm ( xs, ys );

		if ( g > 1 ) {
			xs = xs / g;
			ys = ys / g;
		}

		if ( xs > TEX_INCLINATION_MAX )	{
			errout ( W_ASPECT );
			xs = TEX_INCLINATION_MAX;
	    }
    	if ( ys > TEX_INCLINATION_MAX ) {
			errout ( W_ASPECT );
			ys = TEX_INCLINATION_MAX;
	    }

		l = ex - sx;

		if ( l < 0 ) {
		  xs = -xs;
		  ys = -ys;
		  l = -l;
		  px = ex;
		  py = ey;
		}

		putLinePicture ( px, py, xs, ys, l );
	}

}

/*
 *
 */

void drawInnerLine ( Coord curCoord, Coord curSize, float sx, float sy, float ex, float ey ) {

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

static float posToLocateOffset ( int pos, Coord curCoord, Coord curSize, float ofs ) {
	float loc;

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

static float posToLocate ( int pos, Coord curCoord, Coord curSize ) {

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

static float getPosition ( char *ptr, int pos, Coord curCoord, Coord curSize ) {
	float	loc = posToLocate ( pos, curCoord, curSize );
	float	ofs = 0.0;
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
	  sign = -1;	// negative
		// break;
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

#define	FORMAT_CHAR	'%'

static	char	*sArgment ( char *buf, char *src, char *argv[] ) {
	int ch;
	char *p = buf;

	while ( ( ch = *src++ ) != EOS ) {
		if ( ch == FORMAT_CHAR ) {
			if ( *src != EOS ) {
				ch = *src++;
				if ( isdigit ( ch ) ) {
					char *q = argv[ ch - '0' - 1 ];

					while ( *q != EOS ) {
						*p++ = *q++;
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

static void parseParameter ( float param[], int initial[], int format[], char *line, char *argv[], Coord curCoord, Coord curSize ) {
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

}

/*
 *
 */

static void drawLineBody ( char *line, char *argv[], Coord curCoord, Coord curSize ) {
	static int f[] = { POS_SX, POS_SY, POS_EX, POS_EY, POS_ER };
	float p[4];

	parseParameter ( p, f, f, line, argv, curCoord, curSize );

	putInnerLine ( p[0], p[1], p[2], p[3] );
}

static void drawCircleBody ( char *line, char *argv[], Coord curCoord, Coord curSize ) {
	static int i[] = { POS_HXN, POS_MX, POS_MY, POS_ER };
	static int f[] = { POS_HXP, POS_MX, POS_MY, POS_ER };
	float p[3];

	parseParameter ( p, i, f, line, argv, curCoord, curSize );

	putInnerCircle ( p[1], p[2], p[0] );
}

static void drawOvalBody ( char *line, char *argv[], Coord curCoord, Coord curSize ) {
	static int i[] = { POS_HXN, POS_HYN, POS_MX, POS_MY, POS_ER };
	static int f[] = { POS_HXP, POS_HYP, POS_MX, POS_MY, POS_ER };
	float p[4];

	parseParameter ( p, i, f, line, argv, curCoord, curSize );

	putInnerOval ( p[2], p[3], p[0], p[1] );
}

static void drawBezierBody ( char *line, char *argv[], Coord curCoord, Coord curSize ) {
	static int i[] = {POS_SX, POS_SY, POS_MX, POS_EY, POS_EX, POS_SY, POS_ER};
	static int f[] = {POS_SX, POS_SY, POS_MX, POS_EY, POS_EX, POS_SY, POS_ER};
	float p[6];

	parseParameter ( p, i, f, line, argv, curCoord, curSize );

	putInnerBezier ( p[0], p[1], p[2], p[3], p[4], p[5] );
}

/*
 *
 */

typedef	void (*DrawFunc)( char *line, char *argv[], Coord curCoord, Coord curSize );

static struct	{
  char *name;
  DrawFunc	drawFunc;
} figureTable [] = {
	{	"line",		drawLineBody	},
	{	"circle",	drawCircleBody	},
	{	"oval",		drawOvalBody	},
	{	"bezier",	drawBezierBody	},
	{	NULL,		NULL			}
};

static void doDrawBody ( char *line, char *argv[], Coord curCoord, Coord curSize ) {
	char	token[ TOKEN_SIZE ];
	char	strbuf[ ARG_LINE ];
	int		i;

	line = sArgment ( strbuf, line, argv );

	if ( ( line = getToken ( token, line ) ) != NULL ) {
		for ( i = 0; figureTable[i].name != NULL; i++ ) {
			if ( !strcmp ( figureTable[i].name, token ) ) {
				figureTable[i].drawFunc ( line, argv, curCoord, curSize );
				break;
			}
		}
	}
}

/*
 * drawBody
 */

static void drawBody ( Coord curCoord, Coord curSize, StrList *slp, char *argv[] ) {
	char	*line;
	VCell	*vcp;

	if ( slp != NULL ) {
		for ( vcp = slp -> top; vcp != NULL; vcp = vcp -> next ) {
			line = (char *)(((VCell *) vcp) -> value);
			if ( line != NULL ) {
			  doDrawBody ( line, argv, curCoord, curSize );
			}
		}
	}
}

/*
 *
 */

static	char	**sepArgs ( char *args[ARGS+1], char *argv, char *params ) {
	int	i;

	*argv = EOS;
	for ( i = 0; i < ARGS; i++ ) {
		args[i] = argv;
		if ( params != NULL ) {
			if ( ( params = getToken ( argv, params ) ) != NULL ) {
				argv += strlen ( argv ) + 1;
			} else {
				*argv = EOS;
			}
		}
	}

	args[ARGS] = NULL;

	return args;
}

/*
 *
 */

void	doDraw ( char *name, char *pList, Coord curCoord, Coord curSize, char *curBoxPos, char *curPos ) {
	Figure	*find = findFigure ( name );
	char	*argv[ARGS+1];
	char	args[ARG_LINE];

	sepArgs ( argv, args, pList );

	if ( find != NULL ) {
		if ( find -> command -> hasText ) {
			drawMakePut ( curCoord, curSize, curBoxPos, curPos );
		}

		drawBody ( curCoord, curSize, find -> body, argv );

		checkTextPicBoundsRng ( curCoord, curSize );

	}

}

/*
 *
 */

