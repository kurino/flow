/*
 * token.h
 */

#ifndef	_TOKEN_H_
#define	_TOKEN_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

#define	TOKEN_SIZE	128

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	char	*skipSpace ( char *ptr );
extern	char	*getToken ( char *word, char *line );
extern	char	*skipToken ( char *ptr );

/*
 *
 */

#endif

/*
 *
 */

