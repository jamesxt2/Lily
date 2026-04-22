#pragma once

#include <memory>

#ifdef LL_PLATFORM_WINDOWS
#if LL_DYNAMIC_LINK
	#ifdef LL_BUILD_DLL
		#define LILY_API __declspec(dllexport)
	#else
		#define LILY_API __declspec(dllimport)
	#endif
#else
	#define LILY_API
#endif
#else
	#error Lily only supports Windows!
#endif

#ifdef LL_DEBUG
	#define LL_ENABLE_ASSERTS
#endif

#ifdef LL_ENABLE_ASSERTS
	#define LL_ASSERT(x, ...) { if(!(x)) { LL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LL_CORE_ASSERT(x, ...) { if(!(x)) { LL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LL_ASSERT(x, ...) 
	#define LL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Lily {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}