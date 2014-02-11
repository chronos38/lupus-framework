/* This file is part of LupusFramwork.
 *
 * LupusFramwork is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LupusFramwork is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LupusFramwork.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LUPUS_CHAR_HPP
#define LUPUS_CHAR_HPP

#include "Object.hpp"

namespace Lupus {
	namespace System {
		/// Represents a unicode character
		class LUPUS_API Char : public Object
		{
		public:
			Char();
			Char(int);
			bool IsBlank() const;
			bool IsDigit() const;
			bool IsGraph() const;
			bool IsLetter() const;
			bool IsLetterOrDigit() const;
			bool IsLower() const;
			bool IsPunct() const;
			bool IsUpper() const;
			bool IsSpace() const;
			bool IsPrint() const;
			bool IsControl() const;
			bool IsHexadecimal() const;
			Char ToLower() const;
			Char ToUpper() const;
			int Value() const;
			Char operator+(const Char&) const;
			Char operator-(const Char&) const;
			Char& operator+=(const Char&);
			Char& operator-=(const Char&);
			bool operator==(const Char&) const;
			bool operator!=(const Char&) const;
		public:
			static const int MaxValue;
			static const int MinValue;
		private:
#if defined(LUPUS_WINDOWS_PLATFORM)
			wchar_t mValue;
#elif defined(LUPUS_UNIX_PLATFORM)
			char mValue;
#endif
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
