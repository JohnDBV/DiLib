#ifndef __DI_INTERNAL_H__
#define __DI_INTERNAL_H__

#include <string_view>

namespace di
{
	namespace internal
	{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		static const char slash = '\\';
#else
		static const char slash = '/';
#endif

		std::string_view getCppCompilerMessage();
	}
}

#endif

