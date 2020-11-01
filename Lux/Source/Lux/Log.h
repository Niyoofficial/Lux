#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Lux
{
	class LUX_API Log
	{
	public:
		static void Init();

		template<typename T>
		static void Core_Trace_Internal(const T& msg) { Log::s_CoreLogger->trace(msg); }
		template<typename T>
		static void Core_Info_Internal(const T& msg) { Log::s_CoreLogger->info(msg); }
		template<typename T>
		static void Core_Warn_Internal(const T& msg) { Log::s_CoreLogger->warn(msg); }
		template<typename T>
		static void Core_Error_Internal(const T& msg) { Log::s_CoreLogger->error(msg); }
		template<typename T>
		static void Core_Critical_Internal(const T& msg) { Log::s_CoreLogger->critical(msg); }

		template<typename T>
		static void Trace_Internal(const T& msg) { Log::s_ClientLogger->trace(msg); }
		template<typename T>
		static void Info_Internal(const T& msg) { Log::s_ClientLogger->info(msg); }
		template<typename T>
		static void Warn_Internal(const T& msg) { Log::s_ClientLogger->warn(msg); }
		template<typename T>
		static void Error_Internal(const T& msg) { Log::s_ClientLogger->error(msg); }
		template<typename T>
		static void Critical_Internal(const T& msg) { Log::s_ClientLogger->critical(msg); }

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

//Core log macros
#define LX_CORE_TRACE(...)	::Lux::Log::Core_Trace_Internal(__VA_ARGS__)
#define LX_CORE_INFO(...)	::Lux::Log::Core_Info_Internal(__VA_ARGS__)
#define LX_CORE_WARN(...)	::Lux::Log::Core_Warn_Internal(__VA_ARGS__)
#define LX_CORE_ERROR(...)	::Lux::Log::Core_Error_Internal(__VA_ARGS__)
#define LX_CORE_FATAL(...)	::Lux::Log::Core_Critical_Internal(__VA_ARGS__)

//Client log macros
#define LX_TRACE(...)		::Lux::Log::Trace_Internal(__VA_ARGS__)
#define LX_INFO(...)		::Lux::Log::Info_Internal(__VA_ARGS__)
#define LX_WARN(...)		::Lux::Log::Warn_Internal(__VA_ARGS__)
#define LX_ERROR(...)		::Lux::Log::Error_Internal(__VA_ARGS__)
#define LX_FATAL(...)		::Lux::Log::Critical_Internal(__VA_ARGS__)
