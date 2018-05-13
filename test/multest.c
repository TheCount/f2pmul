#include<stddef.h>

#include"f2pmul.h"

int main( void ) {
	F2PMul_256 x, y;
	F2PMul_512 p;
	for ( size_t i = 0; i != 4; ++i ) {
		x.data[i] = -1;
		y.data[i] = -1;
	}
	f2pmul( &p, &x, &y );
}
