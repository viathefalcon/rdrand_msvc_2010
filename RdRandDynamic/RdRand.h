// RdRand.h: Declares the interface to the functions in the DLL.
//
// Author: Stephen Higgins
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RDRAND_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RDRAND_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RDRAND_EXPORTS
#define RDRAND_API extern "C" __declspec(dllexport)
#else
#define RDRAND_API __declspec(dllimport)
#endif

// Includes
//

// Pull in the headers from the static library to define the 'API'
#include "../RdRandStatic/ia_rdrand.h"

// Macros
//

// Previously, rdrand_uniform was exported from the static library as
// a function; we've since changed it to a macro which maps onto 
// the extended implementation. But we still want/need to export it as
// an actual function from this library, so we undefine the macro,
// and provide a trivial implementation.
#ifdef rdrand_uniform
#undef rdrand_uniform
#endif

// Functions
//

// Invokes RDRAND to generate a unsigned random integer,
// and bounds it uniformly to the range 0 <= value < bound.
//
// If no random value is available, returns the bound.
// (This is 32-bit even under 64-bit builds, but this maintains
// the previous API, and 64-bit clients can still call rdrand_uniform_ex(..))
RDRAND_API uint32_t RDRAND_CALLTYPE rdrand_uniform(uint32_t);
