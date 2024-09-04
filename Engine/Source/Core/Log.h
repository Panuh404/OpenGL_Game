#pragma once

#include "spdlog/spdlog.h"

namespace Quiet
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

//-----------------------------------------------------------------------------
// [MACROS] Logger
//-----------------------------------------------------------------------------
#define LOG_INFO(...)		::Quiet::Log::GetLogger()->info(__VA_ARGS__);
#define LOG_WARN(...)		::Quiet::Log::GetLogger()->warn(__VA_ARGS__);
#define LOG_TRACE(...)		::Quiet::Log::GetLogger()->trace(__VA_ARGS__);
#define LOG_ERROR(...)		::Quiet::Log::GetLogger()->error(__VA_ARGS__);
#define LOG_CRITICAL(...)	::Quiet::Log::GetLogger()->critical(__VA_ARGS__);