/*
 * dofigure.h
 */

#ifndef	_DOFIGURE_H_
#define	_DOFIGURE_H_	1

/*
 *	includes
 */

#include "figure.h"
#include "flowcom.h"

/*
 *	constants
 */

/*
 *	typedefs
 */

/*
 *	externs
 */

extern	void	doFigure ( char *pList );
extern	void	dumpFigure ( void );
extern	Figure	*findFigure ( char *name );
extern	FlowCom	*getFigureCommand ( char *name );

/*
 *
 */

#endif

/*
 *
 */

