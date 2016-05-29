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
#ifdef _WIN64
RDRAND_API bool RDRAND_CALLTYPE rdrandx64(__deref_out uint32_ptr);

// Map rdrand to the name of the function exported from the assembled module
#define rdrand rdrandx64
#else
RDRAND_API bool RDRAND_CALLTYPE rdrand(__deref_out uint32_ptr);
#endif

// Invokes RDRAND to generate a 32-bit unsigned random number,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
#ifdef _WIN64
RDRAND_API uint32_t RDRAND_CALLTYPE rdrandx64_uniform(__in uint32_t);

// Map rdrand_uniform to the name of the function exported from the assembled module
#define rdrand_uniform rdrandx64_uniform
#else
RDRAND_API unsigned RDRAND_CALLTYPE rdrand_uniform(__in unsigned);
#endif // _WIN64

} // extern "C"
