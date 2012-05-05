/*
 * infile.h
 */

#ifndef	_INFILE_H_
#define	_INFILE_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

#define LINE_LEN 120

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	void	open_infile ( char *fileName );
extern	void	close_infile ( void );
extern	char	*readline_infile ( char *line, int size );
extern	int		eof_infile ( void );
extern	int		get_input_line ( void );
extern	void	unget_infile ( char *line );

/*
 *
 */

#endif

/*
 *
 */

