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

void putInnerLine ( float sx, float sy, float ex, float ey ) {

	if ( sx == ex ) {
		if ( ey > sy ) {
			putVerticalLinePicture ( sx, sy, ey - sy );
		}
	} else if ( sy == ey ) {
		if ( ex > sx ) {
			putHorizontalLinePicture ( sx, sy, ex - sx );
		}
	} else {
		int	xs = (int)( ex - sx );
		int	ys = (int)( ey - sy );
		int g = gcm ( xs, ys );
		int l;

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

		if ( xs > ys ) {
			l = (int)( ex - sx );
		} else {
			l = (int)( ey - sy );
		}

		putLinePicture ( sx, sy, xs, ys, l );
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
  POS_SX = 0,
  POS_SY = 1,
  POS_EX = 2,
  POS_EY = 3,
  POS_ER = 4
};

static float posToLocateOffset ( int pos, Coord curCoord, Coord curSize, float ofs ) {
	float loc;

	switch ( pos ) {
	case POS_SX:
		loc = curCoord.x + ofs;
		break;
	case POS_SY:
		loc = curCoord.y - curSize.y + ofs;
		break;
	case POS_EX:
		loc = curCoord.x + curSize.x + ofs;
		break;
	case POS_EY:
		loc = curCoord.y + ofs;
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

static int tbl[3][4] = {
  /* 			POS_SX,	POS_SY,	POS_EX,	POS_EY		*/
  /* '.' */	{	POS_SX,	POS_SY,	POS_EX,	POS_EY	},
  /* 's' */	{	POS_SX,	POS_SY,	POS_SX,	POS_SY	},
  /* 'e' */	{	POS_EX,	POS_EY,	POS_EX,	POS_EY	}
};

static float getPosition ( char *ptr, int pos, Coord curCoord, Coord curSize ) {
	float	loc = posToLocate ( pos, curCoord, curSize );
	float	ofs = 0.0;
	int		sign = 1;

	switch ( *ptr ) {
	case '.':
	case 's':
	case 'e':
		switch ( *ptr ) {
		case '.':
			pos = tbl[0][pos];
			break;
		case 's':
			pos = tbl[1][pos];
			break;
		case 'e':
			pos = tbl[2][pos];
			break;
		}
		loc = posToLocate ( pos, curCoord, curSize );
		break;
	case '-':
		sign = -1;
		ptr++;
		// break;
	default:
		ofs = atof ( ptr );
		if ( sign > 0.0 ) {
			loc = posToLocateOffset ( tbl[1][pos], curCoord, curSize,   ofs );
		} else {
			loc = posToLocateOffset ( tbl[2][pos], curCoord, curSize, - ofs );
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
					char *q;
					for ( q = argv[ch-'0'-1]; *q != EOS; ) {
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

static void drawBody ( Coord curCoord, Coord curSize, StrList *slp, char *argv[] ) {
	char	*line;
	VCell	*vcp;
	char	token[ TOKEN_SIZE ];
	char	strbuf[ ARG_LINE ];

	if ( slp != NULL ) {
		for ( vcp = slp -> top; vcp != NULL; vcp = vcp -> next ) {
			line = (char *)(((VCell *) vcp) -> value);
			if ( line != NULL ) {

				line = sArgment ( strbuf, line, argv );

				if ( ( line = getToken ( token, line ) ) != NULL ) {
					if ( !strcmp ( "line", token ) ) {
						float p[4];
						int pos;

						for ( pos = POS_SX; pos <= POS_EY; pos++ ) {
							p[pos] = posToLocate ( pos, curCoord, curSize );
						}

						for ( pos = POS_SX; pos <= POS_EY; pos++ ) {
							if ( ( line = getToken ( token, line ) ) != NULL ) {
								p[pos] = getPosition ( token, pos, curCoord, curSize );
							} else {
								break;
							}
						}

						putInnerLine ( p[POS_SX], p[POS_SY], p[POS_EX], p[POS_EY] );

					}
				}
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

