// DLLMain.cpp : Defines the entry point for the DLL application.
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
#include "RdRand.h"

// Functions
//

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

uint32_t RDRAND_CALLTYPE rdrand_uniform(uint32_t bound) {
	return (uint32_t) rdrand_uniform_ex( 0, bound );
}

#ifndef _DEBUG
// So as not to have to link with the Visual C++ runtime, we provide our own entry-point.
extern "C" BOOL WINAPI _DllMainCRTStartup(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	return DllMain( hinstDLL, fdwReason, lpReserved );
}
#endif