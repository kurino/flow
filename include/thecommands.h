/*
 * thecommands.h
 */

#ifndef	_THECOMMANDS_H_
#define	_THECOMMANDS_H_	1

/*
 *	includes
 */

#include "direcs.h"

/*
 *	constants
 */

#define	dir2command(X)	(X)
#define	command2dir(X)	(X)

/*
 *	typedefs
 */

typedef enum {
	/* Direction Command is same as Direction itself */

	UP = UP_DIR,
	RIGHT = RIGHT_DIR,
	DOWN = DOWN_DIR,
	LEFT = LEFT_DIR,

	/* Other Commands  */

	SET_TRACK = SIZE_OF_DIRECS,

	BOX,
	OVAL,
	CHOICE,
	TAG,
	TO_TAG,
	SCALE,
	TILT,
	TEXT,
	TXT_POS,
	SKIP,
	DRUM,
	CALL,
	SET_WIDTH,
	TURN,

	FIGURE,
	DRAW,

	MARK,
	GO,

	MACRO,
	ENDMACRO,
	EXPAND,

	COMMENT,
	NOT_COMMAND
}  TheCommands;

/*
 *	externs
 */

/*
 *
 */

#endif

/*
 *
 */

