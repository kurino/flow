/*
 *	errout.c
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
 *
 */

#include "bool.h"
#include "errout.h"

/*
 *
 */

#define	FLOW_WRNIG	10000
#define	FLOW_ERROR	20000

#define	toErr(X)	((X)+FLOW_ERROR)
#define	toWrn(X)	((X)+FLOW_WRNIG)

/*
 *
 */

typedef	struct	{
  ErrorCode	code;
  char 		*fmt;
  int 		type;
  Bool 		exit;
} ErrorInformation;

/*
 *
 */

static ErrorInformation	errTab[] = {

  /* warning */

	{	W_ASPECT,
		"illegal Choice aspect ratio\n",
		FLOW_WRNIG, FALSE	},

  /* error */

	{	E_INTERPRET_LINE,
		"can't interpret line %d\n",
		FLOW_ERROR, FALSE	},

	{	E_TAG_STACK_EMPTY,
		"Tag stack empty\n",
		FLOW_ERROR, FALSE	},

	{	E_TOO_MANY_UNGET,
		"too many unget line(%s)\n",
		FLOW_ERROR, FALSE	},

	{	E_UNKNOWN_COMMAND,
		"unknown command %4d\n",
		FLOW_ERROR, FALSE	},

	/* error exit */

	{	E_OPEN_TEMPFILE,
		"Couldn't open temp file %s\n",
		FLOW_ERROR, TRUE	},

	{	E_TEMPFILE_NOT_OPENED,
		"Tempfile not opened\n",
		FLOW_ERROR, TRUE	},

	{	E_OPEN_INPUT,
		"Couldn't open input file %s\n",
		FLOW_ERROR, TRUE	},

	{	E_OPEN_OUTPUT,
		"Couldn't open output file %s\n",
		FLOW_ERROR, TRUE	},

	{	E_UNKNOWN_ERROR,
		"Unknown Error Detected\n",
		FLOW_ERROR, TRUE	}
};

#define	ERROR_SIZE	(sizeof(errTab)/sizeof(*errTab))

/*
 *
 */

void errout ( ErrorCode code, ... ) {
	va_list ap;
	int index = ERROR_SIZE - 1;

	va_start ( ap, code );

	if ( 0 <= code && code < ERROR_SIZE - 1 ) {
	  index = code;
	}

	switch ( errTab[ index ].type ) {
	defaut:
	  // break;
	case FLOW_ERROR:
	  fprintf ( stderr, "Flow Error (%d) : ", toErr ( code ) );
	  break;
	case FLOW_WRNIG:
	  fprintf ( stderr, "Flow Warning (%d) : ", toWrn ( code ) );
	  break;
	}

	vfprintf ( stderr, errTab[ index ].fmt, ap );

	va_end( ap );

	if ( errTab[ index ].exit ) {
		exit ( toErr ( code ) );
	}
}

/*
 *
 */
