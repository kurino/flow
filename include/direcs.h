/*
 * direcs.h
 */

#ifndef	_DIRECS_H_
#define	_DIRECS_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

/*
 *	typedefs
 */

/*
 *
 *		 U
 *		L R		Crockwise
 *		 D
 *
 */

typedef enum {
	UP_DIR = 0,
	RIGHT_DIR = 1,
	DOWN_DIR = 2,
	LEFT_DIR = 3,
	SIZE_OF_DIRECS = 4
}	Direcs;

/*
 *	externs
 */

#define	turnDirecRight(DIR)	(((DIR)+1)%SIZE_OF_DIRECS)
#define	turnDirecLeft(DIR)	(((DIR)+(SIZE_OF_DIRECS-1))%SIZE_OF_DIRECS)

/*
 *
 */

#endif

/*
 *
 */

