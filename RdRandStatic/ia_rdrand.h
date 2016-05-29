// ia_rdrand.h: Declares the types and functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// Macros
//

#ifdef _WIN64
#define RDRAND_CALLTYPE __fastcall
#else
#define RDRAND_CALLTYPE __stdcall
#endif

#ifndef RDRAND_API
#define RDRAND_API
#endif

// Types
//
typedef unsigned __int32 uint32_t, *uint32_ptr;

extern "C" {

// Functions
//

// Returns true if the host CPU supports the RDRAND instruction
RDRAND_API bool RDRAND_CALLTYPE rdrand_supported(void);

// Invokes RDRAND to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
RDRAND_API bool RDRAND_CALLTYPE rdrand_next(__deref_out uint32_ptr);

// Invokes RDRAND to generate a 32-bit unsigned random number,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
RDRAND_API unsigned RDRAND_CALLTYPE rdrand_uniform(__in unsigned);

} // extern "C"
