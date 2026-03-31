#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Lily {
	class LILY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define LL_CORE_TRACE(...) ::Lily::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LL_CORE_INFO(...)  ::Lily::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LL_CORE_WARN(...)  ::Lily::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LL_CORE_ERROR(...) ::Lily::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LL_CORE_FATAL(...) ::Lily::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define LL_TRACE(...) ::Lily::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LL_INFO(...)  ::Lily::Log::GetClientLogger()->info(__VA_ARGS__)
#define LL_WARN(...)  ::Lily::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LL_ERROR(...) ::Lily::Log::GetClientLogger()->error(__VA_ARGS__)
#define LL_FATAL(...) ::Lily::Log::GetClientLogger()->fatal(__VA_ARGS__)
