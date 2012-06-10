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
#include "dofigure.h"
#include "token.h"
#include "getcommand.h"

/*
 *
 */

static	FlowCom fcom[] = {
  { "SetTrack", 1, {0,0}, FALSE,	SET_TRACK	},
  { "Up",       1, {0,0}, FALSE,	UP			},
  { "Down",     1, {0,0}, FALSE,	DOWN		},
  { "Left",     1, {0,0}, FALSE,	LEFT		},
  { "Right",    1, {0,0}, FALSE,	RIGHT		},
  { "Box",      0, {4,2}, TRUE,		BOX			},
  { "Oval",     0, {4,2}, TRUE,		OVAL		},
  { "Choice",   4, {4,4}, TRUE,		CHOICE		},
  { "Tag",      0, {0,0}, FALSE,	TAG			},
  { "ToTag",    0, {0,0}, FALSE,	TO_TAG		},
  { "Scale",    2, {0,0}, FALSE,	SCALE		},
  { "Tilt",     0, {4,2}, TRUE,		TILT		},
  { "Text",     0, {4,2}, TRUE,		TEXT		},
  { "TxtPos",   4, {0,0}, FALSE,	TXT_POS		},
  { "Skip",     2, {0,0}, FALSE,	SKIP		},
  { "Drum",     0, {4,4}, TRUE,		DRUM		},
  { "Call",     0, {4,2}, TRUE,		CALL		},
  { "SetWidth", 1, {0,0}, FALSE,	SET_WIDTH	},
  { "Turn",		1, {0,0}, FALSE,	TURN		},
  { "Figure",	1, {0,0}, FALSE,	FIGURE		},
  { "Draw",		1, {0,0}, FALSE,	DRAW		},
  { "%",        0, {0,0}, FALSE,	COMMENT		},
  { NULL,       0, {0,0}, FALSE,	NOT_COMMAND	}
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
tries to interpret the next line of inFile as a command, returns NULL if it can't
*/
	FlowCom *command = NULL;
	Figure *figure = NULL;
	int i;
 	int l;
	char token[ TOKEN_SIZE ];
	char *pPtr = getToken ( token, line );

	if ( pPtr != NULL ) {

		/* searching pre define command */
		for ( i = 0; fcom[ i ].name != NULL; i++ ) {
			if ( !strcmp ( fcom[ i ].name, token ) ) {
				if ( fcom[ i ].command == DRAW ) {
					if ( ( pPtr = getToken ( token, pPtr ) ) != NULL ) {
						command = getFigureCommand ( token );
					}
				} else {
				    command = fcom + i;
				}
				break;
			}
		}

		/* searching figure */
		if ( fcom[ i ].name == NULL ) {
			command = getFigureCommand ( token );
		}

		if ( command != NULL ) {
			strcpy ( plist, pPtr );
			return command;
		}
    }

	if ( !eof_infile() && line[0] != EOS ) {
		errout ( E_INTERPRET_LINE, get_input_line(), line );
	}

	return NULL;
}


/*
 *
 */

