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
#define _ltolower towlower
#define _ltoupper towupper
// types
#define _lisalnum iswalnum
#define _lisalpha iswalpha
#define _lisblank iswblank
#define _liscntrl iswcntrl
#define _lisdigit iswdigit
#define _lisgraph iswgraph
#define _lislower iswlower
#define _lisprint iswprint
#define _lispunct iswpunct
#define _lisspace iswspace
#define _lisupper iswupper
#define _lisxdigit iswxdigit
// memory manipulation
#define _lmemcpy(dst, src, len) wmemcpy_s(dst, len, src, len)
#define _lmemmove(dst, src, len) wmemmove_s(dst, len, src, len)
#define _lmemcmp wmemcmp
#define _lmemchr wmemchr
#define _lmemset wmemset
// length
#define _lstrlen wcslen
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
#define _ltolower tolower
#define _ltoupper toupper
// types
#define _lisalnum isalnum
#define _lisalpha isalpha
#define _lisblank isblank
#define _liscntrl iscntrl
#define _lisdigit isdigit
#define _lisgraph isgraph
#define _lislower islower
#define _lisprint isprint
#define _lispunct ispunct
#define _lisspace isspace
#define _lisupper isupper
#define _lisxdigit isxdigit
// memory manipulation
#define _lmemcpy memcpy
#define _lmemmove memmove
#define _lmemcmp memcmp
#define _lmemchr memchr
#define _lmemset memset
// length
#define _lstrlen strlen
// i/o
#define _lsprintf snprintf
#define _lsscanf sscanf
#endif

// lock logic
#define lock(object, code) object.Lock(); code; object.Unlock()

namespace Lupus {
	/// single signed byte
	typedef char byte;
	/// single unsigned byte
	typedef unsigned char ubyte;
	/// 16-bit unsigned integer
	typedef unsigned short ushort;
	/// 32-bit unsigned integer
	typedef unsigned int uint;
	/// >=32-bit unsigned integer
	typedef unsigned long ulong;
	/// >=64-bit signed integer
	typedef long long llong;
	/// >=64-bit unsigned integer
	typedef unsigned long long ullong;
	/// 128-bit float point number
	typedef long double real;

	namespace System {
		/// conversion base for integer
		enum class IntegerBase {
			Octal,
			Decimal,
			Hexadecimal
		};
		/// sensitivity flag
		enum class CaseSensitivity {
			CaseSensitive,
			CaseInsensitive
		};
		/// string split flag
		enum class StringSplitOptions {
			None,
			RemoveEmptyEntries
		};
	}
}

#endif
