// ia_rdrand.cpp: Implements the functions for working with the RDRAND instruction on (certain) Intel processors.
//
// Author: Stephen Higgins
// Blog: http://blog.viathefalcon.net/
// Twitter: @viathefalcon
//

// Includes
//

// Precompiled Headers
#include "Stdafx.h"

// Declarations
#include "ia_rdrand.h"

// Macros
//

// Defines the RDRAND instruction in terms of its opcode
#define rdrand_eax	__asm _emit 0x0F __asm _emit 0xC7 __asm _emit 0xF0

// Defines the bit mask used to examine the ecx register returned by cpuid.
// (The 30th bit is set.)
#define RDRAND_MASK	0x40000000

// Defines the result returned when the RDRAND instruction is supported by the host hardware
#define RDRAND_SUPPORTED 0

// Defines the result returned when the RDRAND instruction is unsupported by the host hardware
#define RDRAND_UNSUPPORTED 1

// Defines the result returned when whether or not the hardware supports the RDRAND instruction is unknown
#define RDRAND_SUPPORT_UNKNOWN 2

// Functions
//

// Packs the four characters in the given buffer into an integer and compares with the comparand;
// returns 0 if equal; 1 if not.
//
// Could do this with memcmp, of course, but don't want to link in the C/C++ runtime.
inline int packcmp(int comparand, __in_bcount(4) const char* buffer) {

	const int packed = *((int*) buffer);
	return (packed == comparand) ? 0 : 1;
}

// Queries CPUID to see if the RDRAND instruction is supported
bool rdrand_cpuid(void) {

	// Check if we are on Intel hardware
	int info[4] = { -1, -1, -1, -1 };
	__cpuid( info, 0 );
	if (packcmp( info[1], "Genu" ) != 0 ||
		packcmp( info[3], "ineI" ) != 0 ||
		packcmp( info[2], "ntel" ) != 0 ){
		return false;
	}

	// Query the feature itself
	__cpuid( info, 1 );
	return ((info[2] & RDRAND_MASK) == RDRAND_MASK); // info[2] == ecx
}

bool rdrand_supported(void) {

	// Caching the result is cheaper than re-invoking cpuid
	static unsigned supported = RDRAND_SUPPORT_UNKNOWN;
	if (supported == RDRAND_SUPPORT_UNKNOWN){
		supported = (rdrand_cpuid( ) ? RDRAND_SUPPORTED : RDRAND_UNSUPPORTED);
	}
	return (supported == RDRAND_SUPPORTED);
}

#ifndef _WIN64
bool rdrand(__deref_out unsigned* dest) {

	__asm {
			xor eax, eax		; Indicate to VC++ that we'll be using EAX, EDX
			xor edx, edx;

			rdrand_eax			; Get the random value into EAX
			jc rdrand_rslt		; If a value was available, jump down
			mov eax, 0			; Set the result (false)
			jmp rdrand_ret		; Jump over the next bit to get out of the function

	rdrand_rslt:
			mov edx, dest		; Move the address in the dest parameter into EDX
			mov [edx], eax		; Move the random value from EAX into the destination address (now in EDX)
			mov eax, 1			; Set the result (true)

	rdrand_ret:
			; Fall out here
	}

	// Return here with the result in EAX
	;
}
#endif
