// ia_rdrand.h: Declares the types and functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins
// @viathefalcon
//

#ifndef __IA_RAND_H__
#define __IA_RAND_H__

// Macros
//

#ifdef _WIN64
#define RDRAND_CALLTYPE __fastcall
#else
#define RDRAND_CALLTYPE __stdcall
#endif

#ifndef RDRAND_API
#define RDRAND_API extern "C" 
#endif

// Invokes RDRAND to generate a unsigned random integer,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
#define rdrand_uniform(bound) rdrand_uniform_ex( 0, (bound) )

// Types
//

typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t, *uint32_ptr;
typedef unsigned __int64 uint64_t, *uint64_ptr;

// Functions
//

// Returns true if the host CPU supports the RDRAND instruction
RDRAND_API bool RDRAND_CALLTYPE rdrand_supported(void);

// Invokes RDRAND to generate a 32-bit unsigned random number
// Returns true if a random value was available; false otherwise
RDRAND_API bool RDRAND_CALLTYPE rdrand_next(__deref_out uint32_ptr);

#ifdef _WIN64
// Invokes RDRAND to generate a 64-bit unsigned random number,
// such that lower <= value < upper
//
// If no random value is available, returns the upper bound.
RDRAND_API uint64_t RDRAND_CALLTYPE rdrand_uniform_ex(__in uint64_t, __in uint64_t);
#else
// Invokes RDRAND to generate a 32-bit unsigned random number,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
RDRAND_API uint32_t RDRAND_CALLTYPE rdrand_uniform_ex(__in uint32_t, __in uint32_t);
#endif

#endif // __IA_RAND_H__