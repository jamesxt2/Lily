#pragma once

#ifdef LL_PLATFORM_WINDOWS
	#ifdef LL_BUILD_DLL
		#define LILY_API __declspec(dllexport)
	#else
		#define LILY_API __declspec(dllimport)
	#endif
#else
	#error Lily only supports Windows!
#endif

#define BIT(x) (1 << x)