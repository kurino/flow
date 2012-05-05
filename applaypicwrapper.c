/*
 *	applaypicwrapper.c
 */

#include <stdio.h>

/*
 *
 */

#include "boundingbox.h"
#include "applaypicwrapper.h"

/*
 *
 */

void applyPicWrapper ( FILE *inFile, FILE *outFile, BoundingBox pic ) {

    char buf[ BUFSIZE ];

    fprintf ( outFile,"\\begin{picture}(%f,%f)(%f,%f)\n",
            pic.max.x - pic.min.x,
            pic.max.y - pic.min.y,
            pic.min.x,
            pic.min.y
          );
    
    while ( !feof ( inFile ) )	{
		fwrite ( buf, fread ( buf, 1, BUFSIZE, inFile ), 1, outFile );
    }

    fprintf ( outFile, "\\end{picture}\n" );
}

/*
 *
 */
