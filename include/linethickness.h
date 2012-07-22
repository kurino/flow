/*
 * linethickness.h
 */

#ifndef	_LINETHICKNESS_H_
#define	_LINETHICKNESS_H_	1

/*
 *	includes
 */

/*
 *	constants
 */

#define	LINE_WIDTH_THICK	0.8
#define	LINE_WIDTH_THIN		0.4

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	void set_linelinethickness ( double width );
extern	void push_linethickness ( void );
extern	void pop_linethickness ( void );

/*
 *
 */

#endif

/*
 *
 */

