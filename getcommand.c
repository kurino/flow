/*
 *	getcommand.c
 */

#include <stdio.h>
#include <string.h>

/*
 *
 */

#include "eos.h"
#include "errout.h"
#include "bool.h"
#include "coord.h"
#include "flowcom.h"
#include "getcommand.h"

/*
 *
 */

static	FlowCom fcom[] = {
  { "SetTrack", 1, {0,0}, FALSE,	SetTrack	},
  { "Up",       1, {0,0}, FALSE,	Up			},
  { "Down",     1, {0,0}, FALSE,	Down		},
  { "Left",     1, {0,0}, FALSE,	Left		},
  { "Right",    1, {0,0}, FALSE,	Right		},
  { "Box",      0, {4,2}, TRUE,		Box			},
  { "Oval",     0, {4,2}, TRUE,		Oval		},
  { "Choice",   4, {4,4}, TRUE,		Choice		},
  { "Tag",      0, {0,0}, FALSE,	Tag			},
  { "ToTag",    0, {0,0}, FALSE,	ToTag		},
  { "Scale",    2, {0,0}, FALSE,	Scale		},
  { "Tilt",     0, {4,2}, TRUE,		Tilt		},
  { "Text",     0, {4,2}, TRUE,		Text		},
  { "TxtPos",   4, {0,0}, FALSE,	TxtPos		},
  { "Skip",     2, {0,0}, FALSE,	Skip		},
  { "Drum",     0, {4,4}, TRUE,		Drum		},
  { "Call",     0, {4,2}, TRUE,		Call		},
  { "SetWidth", 1, {0,0}, FALSE,	SetWidth	},
  { "%",        0, {0,0}, FALSE,	Comment		},
  { NULL,       0, {0,0}, FALSE,	NotCommand	}
};

/*
 *
 */

#define COMMANDS (sizeof(fcom)/sizeof(*fcom))

/*
 *
 */

FlowCom *getCommand ( char line[], Param plist ) {
/*
tries to interpret the next line of inFile as a command, returns -1 if it can't
*/
	FlowCom *command = NULL;
	int i;
 	int l;

	for ( i = 0; fcom[ i ].name != NULL; i++ ) {
		l = strlen ( fcom[ i ].name );
		if ( !strncmp ( fcom[ i ].name, line, l ) ) {
		    strncpy ( plist, line + l, PARAM_LEN );
		    return fcom + i;
		}
    }

	if ( !eof_infile() && line[0] != EOS ) {
	  errout ( E_INTERPRET_LINE, get_input_line() );
	}

	return NULL;
}


/*
 *
 */

