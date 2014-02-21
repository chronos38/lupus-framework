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
#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#  define LUPUS_WINDOWS_PLATFORM
#endif

#if defined(__unix) || defined(__unix__) || defined(LUPUS_APPLE_PLATFORM) || defined(LUPUS_LINUX_PLATFORM)
#  define LUPUS_UNIX_PLATFORM
#endif

#if defined(LUPUS_WINDOWS_PLATFORM)
#  ifdef LUPUS_DLL_EXPORT
#    ifdef __GNUC__
#      undef LUPUS_WINDOWS_PLATFORM
#      define LUPUS_API __attribute__ ((dllexport))
#    else
#      define LUPUS_API __declspec(dllexport)
#    endif
#  else
#    ifdef __GNUC__
#      undef LUPUS_WINDOWS_PLATFORM
#      define LUPUS_API __attribute__ ((dllimport))
#    else
#      define LUPUS_API __declspec(dllimport)
#    endif
#  endif
#elif defined(LUPUS_UNIX_PLATFORM)
#  if __GNUC__ >= 4
#    define LUPUS_API __attribute__ ((visibility ("default")))
#  else
#    define LUPUS_API
#  endif
#else
#  error platform not supported
#endif

#if defined(LUPUS_WINDOWS_PLATFORM)
#include <cwchar>
// type
#define _lchar wchar_t
#define _lstring(x) L##x
// conversion
#define _ltolower(c) towlower(c)
#define _ltoupper(c) towupper(c)
// types
#define _lisalnum(c) iswalnum(c)
#define _lisalpha(c) iswalpha(c)
#define _lisblank(c) iswblank(c)
#define _liscntrl(c) iswcntrl(c)
#define _lisdigit(c) iswdigit(c)
#define _lisgraph(c) iswgraph(c)
#define _lislower(c) iswlower(c)
#define _lisprint(c) iswprint(c)
#define _lispunct(c) iswpunct(c)
#define _lisspace(c) iswspace(c)
#define _lisupper(c) iswupper(c)
#define _lisxdigit(c) iswxdigit(c)
// memory manipulation
#define _lmemcpy(dst, src, len) wmemcpy_s(dst, len, src, len)
#define _lmemmove(dst, src, len) wmemmove_s(dst, len, src, len)
#define _lmemcmp(rhs, lhs, len) wmemcmp(rhs, lhs, len)
#define _lmemchr(src, val, len) wmemchr(src, val, len)
#define _lmemset(src, val, len) wmemset(src, val, len)
// length
#define _lstrlen(str) wcslen(str)
// i/o
#define _lsprintf swprintf_s
#define _lsscanf swscanf_s
#elif defined(LUPUS_UNIX_PLATFORM)
#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
// type
#define _lchar char
#define _lstring(x) x
// conversion
#define _ltolower(c) tolower(c)
#define _ltoupper(c) toupper(c)
// types
#define _lisalnum(c) isalnum(c)
#define _lisalpha(c) isalpha(c)
#define _lisblank(c) isblank(c)
#define _liscntrl(c) iscntrl(c)
#define _lisdigit(c) isdigit(c)
#define _lisgraph(c) isgraph(c)
#define _lislower(c) islower(c)
#define _lisprint(c) isprint(c)
#define _lispunct(c) ispunct(c)
#define _lisspace(c) isspace(c)
#define _lisupper(c) isupper(c)
#define _lisxdigit(c) isxdigit(c)
// memory manipulation
#define _lmemcpy(dst, src, len) memcpy(dst, len, src, len)
#define _lmemmove(dst, src, len) memmove(dst, len, src, len)
#define _lmemcmp(rhs, lhs, len) memcmp(rhs, lhs, len)
#define _lmemchr(src, val, len) memchr(src, val, len)
#define _lmemset(src, val, len) memset(src, val, len)
// length
#define _lstrlen(str) strlen(str)
// i/o
#define _lsprintf snprintf
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
