// RdRand.cpp: Defines the entry-point for the application.
//
// Author: Stephen Higgins
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// Includes
//

// C Standard Library Headers
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Library Headers
#include "RdRand.h"

// Macros
//

#define println(fmt, ...) do { printf( fmt,  __VA_ARGS__ ); printf( "\r\n" ); } while (0)

// Functions
//

// Gives the entry-point for the application
int main(int argc, const char* argv[]) {

	if (rdrand_supported( )){
		if (argc < 2){
			println( "Usage: RdRand.exe [number of random numbers to generate]" );
		}
		println( "RDRAND is supported on this host." );

		const uint32_t iterations = argc > 1 ? (uint32_t) abs( atoi( argv[1] ) ) : 32U;
		uint32_t counter = 0;
		for( uint32_t u = 0; u < iterations; u++ ){
			uint32_t value = 0;
			if (rdrand( &value )){
				println( "RDRAND returned: %u", value );
				counter++;
			}else{
				println( "RDRAND did not return a value." );
			}
		}
		println( "Generated %u random numbers.", counter );

		for (uint32_t bound = iterations, u = 0; u < bound; u++){
			const uint32_t r = rdrand_uniform( bound );
			if (r >= bound){
				println( "%u) Generated a value (%u) equal to or greater than the bound (%u)!?", u, r, bound );
				break;
			}
			println( "%u) Generated %u with bound of %u", u, r, bound );
		}
	}else{
		println( "RDRAND is not supported on this host." );
	}
	return 2;
}
