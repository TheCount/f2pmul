#include<stdio.h>
#include<string.h>

#define toggle( x ) ( x ) ^= '0' ^ '1'

int main( void ) {
	char output[251][502];

	for ( size_t i = 0; i != 251; ++i ) {
		memset( output[i], '0', 502 );
	}
	for ( size_t i = 0; i != 251; ++i ) {
		toggle( output[i][i] );
	}
	for ( size_t i = 251; i != 502; ++i ) {
		toggle( output[( i + 0 ) % 251][i] );
		toggle( output[( i + 2 ) % 251][i] );
		toggle( output[( i + 4 ) % 251][i] );
		toggle( output[( i + 7 ) % 251][i] );
	}
	for ( size_t i = 0; i != 251; ++i ) {
		for ( size_t j = 0; j != 502; j++ ) {
			putchar( output[i][j] );
		}
		puts( "" );
	}
}
