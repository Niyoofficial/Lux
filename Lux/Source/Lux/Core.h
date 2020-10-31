#pragma once

#ifdef LUX_PLATFORM_WINDOWS
	#ifdef LUX_BUILD_DLL
		#define LUX_API __declspec(dllexport)
	#else
		#define LUX_API __declspec(dllimport)
	#endif // LUX_BUILD_DLL
#else
	#error Lux only supports Windows!
#endif // LUX_PLATFORM_WINDOWS
