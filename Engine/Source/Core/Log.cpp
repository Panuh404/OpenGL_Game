#include "Quiet_PCH.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>

namespace Quiet
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		// Serialize Log
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Quiet.log", true));

		// Set Format of the Logging
		logSinks[0]->set_pattern("%^[%T] %n: %v%$");

		// Logger Parameters
		s_Logger = std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
		register_logger(s_Logger);
		s_Logger->set_level(spdlog::level::trace);
		s_Logger->flush_on(spdlog::level::trace);
	}
}