#include<assert.h>
#include<stddef.h>
#include<stdlib.h>

#include"f2pmul.h"

int main( int argc, char ** argv ) {
	F2PMul_512 p;
	F2PMul_256 r;
	for ( size_t i = 0; i != 7; ++i ) {
		p.data[i] = -1;
	}
	p.data[7] = ( ( uint64_t ) ( -1 ) ) >> 10;
	f2pmul_502_mod_251( &r, &p );
	assert( r.data[0] == 0xffffffffffffc083 );
	assert( r.data[1] == 0xffffffffffffffff );
	assert( r.data[2] == 0xffffffffffffffff );
	assert( r.data[3] == 0x7ffffffffffffff );

	r.data[0] = -1;
	r.data[3] = -1;
	f2pmul_256_mod_251( &r );
	assert( r.data[0] == 0xfffffffffffff1ec );
	assert( r.data[1] == 0xffffffffffffffff );
	assert( r.data[2] == 0xffffffffffffffff );
	assert( r.data[3] == 0x7ffffffffffffff );
}
