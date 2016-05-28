// ia_rdrand.h: Declares the types and functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// Functions
//

// Returns true if the host CPU supports the RDRAND instruction
bool rdrand_supported(void);

// Invokes rdrand to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
#ifdef _WIN64
extern "C" bool __fastcall rdrandx64(__deref_out unsigned*);

// Map rdrand to the name of the function exported from the assembled module
#define rdrand(param) rdrandx64( (param) )
#else
bool rdrand(__deref_out unsigned*);
#endif
