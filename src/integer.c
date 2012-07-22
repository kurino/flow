/*
 *	integer.c
 */

#include "integer.h"

/*
 *
 */

int doubleToInt100 ( double x ) {
	 int sign = 1;

	 if ( x < 0 ) {
	   x = -x;
	   sign = -1;
	 }

	 return sign * (((int)((x)*1000)+5)/10);
}


/*
 *
 */

double int100ToDouble ( int x ) {

	return (double)x/100.0;
}

/*
 *
 */

int gcm ( int a, int b ) {

	if ( a < 0 ) {
		return gcm ( -a, b );
	} else if ( b < 0 ) {
		return gcm ( a, -b );
	} else if ( b > 0 ) {
		return gcm ( b, a % b );
	} else {
		return a;
	}
}

/*
 *
 */

