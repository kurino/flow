/*
 * errout.h
 */

#ifndef	_ERROUT_H_
#define	_ERROUT_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

typedef	enum	{
  //
  W_ASPECT,
  //
  E_INTERPRET_LINE,
  E_TAG_STACK_EMPTY,
  E_TOO_MANY_UNGET,
  E_UNKNOWN_COMMAND,
  //
  E_OPEN_TEMPFILE,
  E_TEMPFILE_NOT_OPENED,
  E_OPEN_INPUT,
  E_OPEN_OUTPUT,
  //
  E_UNKNOWN_ERROR
  //
} ErrorCode;

/*
 *	typedefs
 */

/*
 *	externs
 */

extern void errout ( ErrorCode code, ... );

/*
 *
 */

#endif

/*
 *
 */

