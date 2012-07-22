/*
 *	domacro.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 *
 */

#include "eos.h"
#include "token.h"

#include "param.h"
#include "infile.h"
#include "flowcom.h"
#include "getcommand.h"
#include "strlist.h"

#include "macro.h"
#include "macrolist.h"
#include "domacro.h"

/*
 *
 */

static	MacroList	*table = NULL;

/*
 *
 */

int	doMacro ( char *pline ) {
	char	name [ TOKEN_SIZE ];
	char	token [ TOKEN_SIZE ];
	char	line [ LINE_LEN ];
	int		argc = 0;
    Param	params;

	if ( ( pline = getToken ( name, pline ) ) != NULL ) {

		if ( table == NULL ) {
			table = allocMacroList();
		}

		if ( table != NULL ) {
			StrList	*slp = allocStrList();

			while ( readline_infile ( line, LINE_LEN ) != NULL ) {

				if ( isspace ( *line ) ) {
					appendStrList ( slp, line );
				} else {
					FlowCom	*comPtr = getCommand ( line, params );

					if ( comPtr != NULL ) {
						if ( comPtr -> command == ENDMACRO ) {
							if ( ( pline = getToken ( token, pline ) ) != NULL ) {
								argc = atoi ( token );
						  	}

							appendMacroList ( table, allocMacro ( name, argc, slp ) );
							return 0;
						} else {
							appendStrList ( slp, line );
						}
					}
				}
			}
		}
	}

	return 1;
}

/*
 *
 */

void	doExpand ( char *pline ) {
	char	name [ TOKEN_SIZE ];

	if ( ( pline = getToken ( name, pline ) ) != NULL ) {

		if ( table != NULL ) {
			Macro *mp = findMacroList ( table, name );
			if ( mp != NULL ) {
				Argument *agp = allocArgument ( pline );

				if ( agp != NULL ) {
					insert_infile ( mp -> body, agp );
					freeArgument ( agp );
				}
			}
		}
	}
}

/*
 *
 */

Macro	*findMacro ( char *name ) {

	return findMacroList ( table, name );

}

/*
 *
 */

