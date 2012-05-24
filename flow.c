/*

flow.c 22/1/93 (C) 2005 Terry Brown

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

/*

flow - a flow-chart -> LaTeX generator.  Parses a file in a flow-chart
specification language, then produces a corresponding LaTeX
pic environment.

*/

/*
 Version : +k ( 2012/05/02 - )
 */

#include <stdio.h>

/*
 *
 */

#include "version.h"
#include "flowcom.h"
#include "param.h"
#include "tempfile.h"
#include "infile.h"
#include "pic.h"
#include "getcommand.h"
#include "docommand.h"

/*
 *
 */

int main ( int argc, char *argv[] ) {
    Param	params;
    FlowCom	*comPtr = NULL;
	char	line [ LINE_LEN ];

	open_tempfile();
	open_infile ( ( argc > 1 ) ? argv[ 1 ] : NULL );

    tprintf ( "%% picture environment flowchart generated by flow " );
    tprintf ( "%s\n", VERSION );

	while ( readline_infile ( line, LINE_LEN ) != NULL ) {
		if ( ( comPtr = getCommand ( line, params ) ) != NULL ) {
			if ( !doCommand ( comPtr, params ) ) {
				return 10;
			}
		} else {
			break;
		}
	}

	close_infile();
	close_tempfile();

	apply_tempfile ( getPic(), ( argc > 2 ) ? argv[ 2 ] : NULL );

	remove_tempfile();

//	dumpFigure();

    return 0;    /* just to suppress the warning */
}
