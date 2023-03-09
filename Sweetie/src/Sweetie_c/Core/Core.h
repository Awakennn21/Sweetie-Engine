#pragma once

////Exporting dll on engine side but importing dll on client side
//#ifdef SW_PLATFORM_WINDOWS
//	#ifdef SW_BUILD_DLL
//		#define SW_API __declspec(dllexport)
//	#else
//		#define SW_API __declspec(dllimport)
//	#endif 
//#else
//#error OnlyWindowsSupported!
//#endif

#ifdef SW_PLATFORM_WINDOWS
#define SW_API 
#else
#error OnlyWindowsSupported!
#endif

#ifdef SW_ENABLE_ASSERTS
#define SW_CORE_ASSERT(x, ...)\
{\
	if(!x)\
	{\
		SW_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__);\
		__debugbreak();\
	}\
}
#define SW_ASSERT(x, ...)\
{\
	if(!x)\
	{\
		SW_ERROR("Assertion Failed {0}", __VA_ARGS__);\
		__debugbreak();\
	}\
}
#else
#define SW_CORE_ASSERT(x, ...)
#define SW_ASSERT(x, ...)
#endif

//Bit map creating tool for event categories
#define BIT(x) (1 << x) 