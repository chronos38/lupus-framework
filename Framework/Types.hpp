/* Copyright © 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LUPUS_TYPES_HPP
#define LUPUS_TYPES_HPP

#if defined(__linux) || defined(__linux__) || defined(__gnu_linx)
#  define LUPUS_LINUX_PLATFORM
#elif defined(__APPLE__) || defined(__MACH__)
#  define LUPUS_APPLE_PLATTFORM
#elif defined(_WIN32) || defined(_WIN64)
#  define LUPUS_WINDOWS_PLATFORM
#endif

#if defined(__unix) || defined(__unix__) || defined(LUPUS_APPLE_PLATFORM) || defined(LUPUS_LINUX_PLATFORM) || defined(__CYGWIN__)
#  define LUPUS_UNIX_PLATFORM
#endif

#if !(defined(LUPUS_WINDOWS_PLATFORM) || defined(LUPUS_UNIX_PLATFORM))
#  error platform not supported
#endif

#if defined(LUPUS_WINDOWS_PLATFORM)
#  ifdef LUPUS_DLL_EXPORT
#    ifdef __GNUC__
#      define LUPUS_API __attribute__ ((dllexport))
#    else
#      define LUPUS_API __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      define LUPUS_API __attribute__ ((dllimport))
#    else
#      define LUPUS_API __declspec(dllimport)
#    endif
#  endif
#else
#  if __GNUC__ >= 4
#    define LUPUS_API __attribute__ ((visibility ("default")))
#  else
#    define LUPUS_API
#  endif
#endif

namespace Lupus {
	// standard types
	typedef char byte;
	typedef unsigned char ubyte;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;
	typedef long long llong;
	typedef unsigned long long ullong;
	typedef long double real;

	namespace System {
		// enumerations
		enum class IntegerBase {
			Octal,
			Decimal,
			Hexadecimal
		};
		enum class CaseSensitivity {
			CaseSensitive,
			CaseInsensitive
		};
		enum class StringSplitOptions {
			None,
			RemoveEmptyEntries
		};
	}
}

#endif
