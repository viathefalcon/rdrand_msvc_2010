// RdRand.h:
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
#define RDRAND_API __declspec(dllexport)
#else
#define RDRAND_API __declspec(dllimport)
#endif

// Includes
//

// Pull in the headers from the static library to define the 'API'
#include "../RdRandStatic/ia_rdrand.h"
