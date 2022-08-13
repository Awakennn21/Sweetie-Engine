#include "pch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Sweetie
{
	std::shared_ptr<spdlog::logger> Log::CoreLogger;
	std::shared_ptr<spdlog::logger> Log::ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n:%$ %v");

		CoreLogger = spdlog::stderr_color_mt("SWEETIE");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stderr_color_mt("APP");
		ClientLogger->set_level(spdlog::level::trace);
	}
}
