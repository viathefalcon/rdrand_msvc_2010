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

// Invokes RDRAND to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
#ifdef _WIN64
extern "C" bool __fastcall rdrandx64(__deref_out unsigned*);

// Map rdrand to the name of the function exported from the assembled module
#define rdrand rdrandx64
#else
bool rdrand(__deref_out unsigned*);
#endif

// Invokes RDRAND to generate a 32-bit unsigned random number,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
#ifdef _WIN64
extern "C" unsigned rdrandx64_uniform(__in unsigned);

// Map rdrand_uniform to the name of the function exported from the assembled module
#define rdrand_uniform rdrandx64_uniform
#else
unsigned rdrand_uniform(__in unsigned);
#endif // _WIN64
