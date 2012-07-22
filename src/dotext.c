/*
 *	dotext.c
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 *
 */

#include "eos.h"
#include "tempfile.h"
#include "infile.h"
#include "dotext.h"

/*
 *
 */

/*
 *
 */

static	char leader[ SPACEING_LENGTH ] = "";
static	char tailer[ SPACEING_LENGTH ] = "";

/*
 *
 */

void setSpace ( char *l, char *t ) {

  strncpy ( leader, l, SPACEING_LENGTH - 1 );
  leader [ SPACEING_LENGTH - 1 ] = EOS;

  strncpy ( tailer, t, SPACEING_LENGTH - 1 );
  tailer [ SPACEING_LENGTH - 1 ] = EOS;
}

/*
 *
 */

void	doText ( void ) {

/*
output text for those commands that require it, spit out all lines that start
with white space (0x20, 0x09)
*/

	char line[ LINE_LEN ];
    int	l;

	for ( l = 0; readline_infile ( line, LINE_LEN ) != NULL; l++ ) {
		if ( isspace ( line[ 0 ] ) ) {
			int	i;

			for ( i = 1; isspace ( line[ i ] ); i++ ) {
				// do nothing
			}

			if ( l > 0 ) {
				tprintf ( "\\\\\n" );
			}

			tprintf ( "%s%s%s", leader, line + i, tailer );

		} else {
			unget_infile ( line );
			break;
		}
	}

	if ( l > 0 ) {
		tprintf ( "\n" );
	}

}


/*
 *
 */
