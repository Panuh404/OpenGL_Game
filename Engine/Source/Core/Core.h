#pragma once

//-----------------------------------------------------------------------------
// [PLATFORM] Windows
//-----------------------------------------------------------------------------
#ifdef _WIN32
	// Windows x64/x86
	#ifdef _WIN64
		// Windows x64
		#define QT_PLATFORM_WINDOWS
	#else
		// Windows x86
		#error "x86 Builds are not supported!"
	#endif

//-----------------------------------------------------------------------------
// [PLATFORM] LINUX
//-----------------------------------------------------------------------------
#elif defined(__linux__)
	#define QT_PLATFORM_LINUX
	#error "Linux is not supported!"

//-----------------------------------------------------------------------------
// [PLATFORM] OTHER
//-----------------------------------------------------------------------------
#else
	// Unknown compiler/platform
	#error "Unknown platform!"
#endif

//-----------------------------------------------------------------------------
// [DEBUG]
//----------------------------------------------------------------------------- 
#ifdef QT_DEBUG
	#define QT_ENABLE_ASSERTS
#endif

//-----------------------------------------------------------------------------
// [ASSERTIONS] For Visual Studio Only
//----------------------------------------------------------------------------- 
#ifdef QT_ENABLE_ASSERTS
	#define QT_ASSERT(x, ...)		{ if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QT_ASSERT(x, ...)
#endif

//-----------------------------------------------------------------------------
// [BINDS]
//----------------------------------------------------------------------------- 
#define BIT(x) (1 << x)
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
