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

// Local Project Headers
#include "ia_rdrand.h"

// Functions
//

// Gives the entry-point for the application
int main(int argc, const char* argv[]) {

	if (rdrand_supported( )){
		if (argc < 2){
			printf( "Usage: RdRand.exe [number of random numbers to generate]\n" );
		}
		printf( "RDRAND is supported on this host.\n" );

		const unsigned iterations = argc > 1 ? (unsigned) abs( atoi( argv[1] ) ) : 32U;
		unsigned counter = 0;
		for( unsigned u = 0; u < iterations; u++ ){
			unsigned value = 0;
			if (rdrand( &value )){
				printf( "RDRAND returned: %u\n", value );
				counter++;
			}else{
				printf( "RDRAND did not return a value.\n" );
			}
		}
		printf( "Generated %u random numbers.\r", counter );

		for (unsigned u = 0; u < iterations; u++){
			const unsigned r = rdrand_uniform( iterations );
			printf( "%u) Generated %u with bound of %u\n", u, r, iterations );
			if (r >= iterations){
				break;
			}
		}
	}else{
		printf( "RDRAND is not supported on this host." );
	}
	return 0;
}
