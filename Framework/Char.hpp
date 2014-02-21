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

#ifndef LUPUS_CHAR_HPP
#define LUPUS_CHAR_HPP

#include "Object.hpp"
#if defined(LUPUS_WINDOWS_PLATFORM)
#include <cwchar>
// type
#define _lchar wchar_t
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
#define _strlen(str) wcslen(str)
#elif defined(LUPUS_UNIX_PLATFORM)
#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#endif

namespace Lupus {
	namespace System {
		/// Represents a unicode character
		class LUPUS_API Char : public Object
		{
		public:
			Char();
			Char(char);
			Char(const Char&);
			Char(Char&&);
			virtual ~Char();
			virtual bool IsBlank() const;
			virtual bool IsDigit() const;
			virtual bool IsGraph() const;
			virtual bool IsLetter() const;
			virtual bool IsLetterOrDigit() const;
			virtual bool IsLower() const;
			virtual bool IsPunct() const;
			virtual bool IsUpper() const;
			virtual bool IsSpace() const;
			virtual bool IsPrint() const;
			virtual bool IsControl() const;
			virtual bool IsHexadecimal() const;
			virtual Char ToLower() const;
			virtual Char ToUpper() const;
			virtual _lchar Value() const;
			virtual Char& operator=(char);
			virtual Char& operator=(const Char&);
			virtual Char operator+(const Char&) const;
			virtual Char operator-(const Char&) const;
			virtual Char& operator+=(int);
			virtual Char& operator-=(int);
			virtual Char& operator++();
			virtual Char& operator--();
			virtual bool operator==(const Char&) const;
			virtual bool operator!=(const Char&) const;
		public:
			static const int MaxValue;
			static const int MinValue;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			Char(wchar_t);
			Char& operator=(wchar_t);
#endif
		private:
			_lchar mValue;
		};

		template <typename T>
		bool operator==(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator==(const T& lhs, const Char& rhs);

		template <typename T>
		bool operator!=(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator!=(const T& lhs, const Char& rhs);

		template<typename T>
		Char operator+(const Char& lhs, const T& rhs);
		template <typename T>
		Char operator+(const T& lhs, const Char& rhs);

		template<typename T>
		Char operator-(const Char& lhs, const T& rhs);
		template <typename T>
		Char operator-(const T& lhs, const Char& rhs);
	}
}

#include "Char.inl"

#endif
