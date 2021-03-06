#pragma once

#ifdef LUX_PLATFORM_WINDOWS
#if LUX_DYNAMIC_LINK
	#ifdef LUX_BUILD_DLL
		#define LUX_API __declspec(dllexport)
	#else
		#define LUX_API __declspec(dllimport)
	#endif // LUX_BUILD_DLL
#else 
	#define LUX_API
#endif
#else
	#error Lux only supports Windows!
#endif // LUX_PLATFORM_WINDOWS

#ifdef LUX_DEBUG
	#define LUX_ENABLE_ASSERTS
#endif // LUX_DEBUG

#ifdef LUX_ENABLE_ASSERTS
	#define LX_ASSERT(x, ...) { if(!(x)) { LX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define LX_CORE_ASSERT(x, ...) { if(!(x)) { LX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define LX_ASSERT(x, ...)
	#define LX_CORE_ASSERT(x, ...)
#endif // LUX_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define LX_BIND_METHOD(fn) std::bind(&fn, this, std::placeholders::_1)
