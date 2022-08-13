#pragma once
#include "Core.h"
#include "spdlog/spdlog.h" 
#include "spdlog/fmt/ostr.h"

namespace Sweetie
{
	class SW_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;



	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return ClientLogger; }

	};
}

//----------------------------Logging macros----------------------------------
#define SW_CORE_ERROR(...)   ::Sweetie::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SW_CORE_WARN(...)    ::Sweetie::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SW_CORE_INFO(...)    ::Sweetie::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SW_CORE_TRACE(...)   ::Sweetie::Log::GetCoreLogger()->trace(__VA_ARGS__)


#define SW_ERROR(...)        ::Sweetie::Log::GetClientLogger()->error(__VA_ARGS__)
#define SW_WARN(...)         ::Sweetie::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SW_INFO(...)         ::Sweetie::Log::GetClientLogger()->info(__VA_ARGS__)
#define SW_TRACE(...)        ::Sweetie::Log::GetClientLogger()->trace(__VA_ARGS__)
//----------------------------------------------------------------------------
  