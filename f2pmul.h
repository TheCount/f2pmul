#ifndef F2PMUL_H_
#define F2PMUL_H_

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

static inline void f2pmul_abort() {
	fputs( "This should not happen.\n", stderr );
	abort();
}

/**
 * Polynomial over F2 of degree 127 or lower.
 *
 * Structure members are private.
 */
typedef struct F2PMul_128 {
	uint64_t data[2];
} F2PMul_128;

#define f2pmul_128_low( x ) ( &( x )->data[0] )

#define f2pmul_128_high( x ) ( &( x )->data[1] )

/**
 * Polynomial over F2 of degree 255 or lower.
 *
 * Structure members are private.
 */
typedef struct F2PMul_256 {
	uint64_t data[4];
} F2PMul_256;

#define f2pmul_256_low( x ) ( _Generic( ( x ), \
		const F2PMul_256 *: ( const F2PMul_128 * ) ( const char * ) ( x ), \
		F2PMul_256 *: ( F2PMul_128 * ) ( char * ) ( x ), \
		default: f2pmul_abort() \
	) )

#define f2pmul_256_mid( x ) ( _Generic( ( x ), \
		const F2PMul_256 *: ( const F2PMul_128 * ) ( const char * ) &( x )->data[1], \
		F2PMul_256 *: ( F2PMul_128 * ) ( char * ) &( x )->data[1], \
		default: f2pmul_abort() \
	) )

#define f2pmul_256_high( x ) ( _Generic( ( x ), \
		const F2PMul_256 *: ( const F2PMul_128 * ) ( const char * ) &( x )->data[2], \
		F2PMul_256 *: ( F2PMul_128 * ) ( char * ) &( x )->data[2], \
		default: f2pmul_abort() \
	) )

/**
 * Polynomial over F2 of degree 511 or lower.
 *
 * Structure members are private.
 */
typedef struct F2PMul_512 {
	uint64_t data[8];
} F2PMul_512;

#define f2pmul_512_low( x ) ( _Generic( ( x ), \
		const F2PMul_512 *: ( const F2PMul_256 * ) ( const char * ) ( x ), \
		F2PMul_512 *: ( F2PMul_256 * ) ( char * ) ( x ), \
		default: f2pmul_abort() \
	) )

#define f2pmul_512_mid( x ) ( _Generic( ( x ), \
		const F2PMul_512 *: ( const F2PMul_256 * ) ( char * ) &( x )->data[2], \
		F2PMul_512 *: ( F2PMul_256 * ) ( char * ) &( x )->data[2], \
		default: f2pmul_abort() \
	) )

#define f2pmul_512_high( x ) ( _Generic( ( x ), \
		const F2PMul_512 *: ( const F2PMul_256 * ) ( char * ) &( x )->data[4], \
		F2PMul_512 *: ( F2PMul_256 * ) ( char * ) &( x )->data[4], \
		default: f2pmul_abort() \
	) )

#define f2pmul_low( x ) _Generic( ( x ), \
		const F2PMul_512 *: f2pmul_512_low( x ), \
		F2PMul_512 *: f2pmul_512_low( x ), \
		const F2PMul_256 *: f2pmul_256_low( x ), \
		F2PMul_256 *: f2pmul_256_low( x ), \
		const F2PMul_128 *: f2pmul_128_low( x ), \
		F2PMul_128 *: f2pmul_128_low( x ) \
	)

#define f2pmul_mid( x ) _Generic( ( x ), \
		F2PMul_512 *: f2pmul_512_mid( x ), \
		F2PMul_256 *: f2pmul_256_mid( x ) \
	)

#define f2pmul_high( x ) _Generic( ( x ), \
		const F2PMul_512 *: f2pmul_512_high( x ), \
		F2PMul_512 *: f2pmul_512_high( x ), \
		const F2PMul_256 *: f2pmul_256_high( x ), \
		F2PMul_256 *: f2pmul_256_high( x ), \
		const F2PMul_128 *: f2pmul_128_high( x ), \
		F2PMul_128 *: f2pmul_128_high( x ) \
	)

#define f2pmul_add( dest, src ) _Generic( ( dest ), \
		F2PMul_256 *: f2pmul_256_add, \
		F2PMul_128 *: f2pmul_128_add \
	)( dest, src )

/**
 * Multiplies two F2 polynomials.
 *
 * @param prod Pointer to location to store the product.
 * @param x First factor.
 * @param y Second factor.
 */
#define f2pmul( prod, x, y ) _Generic( ( prod ), \
		F2PMul_512 *: f2pmul_256_256_512, \
		F2PMul_256 *: f2pmul_128_128_256, \
		F2PMul_128 *: f2pmul_64_64_128 \
	)( prod, x, y )

/**
 * Adds an F2 polynomial of degree 255 or lower to another.
 *
 * The destination location must not overlap with the source location.
 *
 * @param dest Pointer to destination polynomial.
 * @param src Pointer to source polynomial.
 */
static inline void f2pmul_256_add( F2PMul_256 * restrict dest, const F2PMul_256 * src ) {
	dest->data[0] ^= src->data[0];
	dest->data[1] ^= src->data[1];
	dest->data[2] ^= src->data[2];
	dest->data[3] ^= src->data[3];
}

/**
 * Adds an F2 polynomial of degree 127 or lower to another.
 *
 * The destination location must not overlap with the source location.
 *
 * @param dest Pointer to destination polynomial.
 * @param src Pointer to source polynomial.
 */
static inline void f2pmul_128_add( F2PMul_128 * restrict dest, const F2PMul_128 * src ) {
	dest->data[0] ^= src->data[0];
	dest->data[1] ^= src->data[1];
}

/**
 * Multiplies two F2 polynomials of degree 255 or lower.
 *
 * The product location must not overlap with the factor locations.
 * The factor locations may overlap.
 *
 * @param prod Pointer to location to store the product.
 * @param x Pointer to first factor.
 * @param y Pointer to second factor.
 */
static inline void f2pmul_256_256_512( F2PMul_512 * restrict prod, const F2PMul_256 * x, const F2PMul_256 * y );

/**
 * Multiplies two F2 polynomials of degree 127 or lower.
 *
 * The product location must not overlap with the factor locations.
 * The factor locations may overlap.
 *
 * @param prod Pointer to location to store the product.
 * @param x Pointer to first factor.
 * @param y Pointer to second factor.
 */
static inline void f2pmul_128_128_256( F2PMul_256 * restrict prod, const F2PMul_128 * x, const F2PMul_128 * y );

/**
 * Multiplies two F2 polynomials of degree 63 or lower.
 *
 * @param prod Pointer to location to store the product.
 * @param x First factor.
 * @param y Second factor.
 */
static inline void f2pmul_64_64_128( F2PMul_128 * prod, uint64_t x, uint64_t y );

/**
 * Multiplies two F2 polynomials of degree 31 or lower.
 *
 * @param x First factor.
 * @param y Second factor.
 *
 * @return The product is returned.
 */
static inline uint64_t f2pmul_32_32_64( uint32_t x, uint32_t y ) {
	uint64_t acc = x;
	uint64_t result = 0;
	while ( y != 0 ) {
		if ( y & 1 ) {
			result ^= acc;
		}
		y >>= 1;
		acc <<= 1;
	}

	return result;
}

static inline void f2pmul_64_64_128( F2PMul_128 * prod, uint64_t x, uint64_t y ) {
	uint64_t acc;
	*f2pmul_low( prod ) = f2pmul_32_32_64( x, y );
	*f2pmul_high( prod ) = f2pmul_32_32_64( x >> 32, y >> 32 );
	acc = f2pmul_32_32_64( x >> 32, y );
	acc ^= f2pmul_32_32_64( x, y >> 32 );
	*f2pmul_low( prod ) ^= acc << 32;
	*f2pmul_high( prod ) ^= acc >> 32;
}

static inline void f2pmul_128_128_256( F2PMul_256 * restrict prod, const F2PMul_128 * x, const F2PMul_128 * y ) {
	F2PMul_128 acc;
	F2PMul_128 * prodLow = f2pmul_low( prod );
	F2PMul_128 * prodMid = f2pmul_mid( prod );
	F2PMul_128 * prodHigh = f2pmul_high( prod );
	const uint64_t * xLow = f2pmul_low( x );
	const uint64_t * xHigh = f2pmul_high( x );
	const uint64_t * yLow = f2pmul_low( y );
	const uint64_t * yHigh = f2pmul_high( y );
	f2pmul( prodLow, *xLow, *yLow );
	f2pmul( prodHigh, *xHigh, *yHigh );
	f2pmul( &acc, *xLow, *yHigh );
	f2pmul_add( prodMid, &acc );
	f2pmul( &acc, *xHigh, *yLow );
	f2pmul_add( prodMid, &acc );
}

static inline void f2pmul_256_256_512( F2PMul_512 * restrict prod, const F2PMul_256 * x, const F2PMul_256 * y ) {
	F2PMul_256 acc;
	F2PMul_256 * prodLow = f2pmul_low( prod );
	F2PMul_256 * prodMid = f2pmul_mid( prod );
	F2PMul_256 * prodHigh = f2pmul_high( prod );
	const F2PMul_128 * xLow = f2pmul_low( x );
	const F2PMul_128 * xHigh = f2pmul_high( x );
	const F2PMul_128 * yLow = f2pmul_low( y );
	const F2PMul_128 * yHigh = f2pmul_high( y );
	f2pmul( prodLow, xLow, yLow );
	f2pmul( prodHigh, xHigh, yHigh );
	f2pmul( &acc, xLow, yHigh );
	f2pmul_add( prodMid, &acc );
	f2pmul( &acc, xHigh, yLow );
	f2pmul_add( prodMid, &acc );
}

#endif
