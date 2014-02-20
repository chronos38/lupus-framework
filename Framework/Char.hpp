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
			virtual bool IsBlank() const final;
			virtual bool IsDigit() const final;
			virtual bool IsGraph() const final;
			virtual bool IsLetter() const final;
			virtual bool IsLetterOrDigit() const final;
			virtual bool IsLower() const final;
			virtual bool IsPunct() const final;
			virtual bool IsUpper() const final;
			virtual bool IsSpace() const final;
			virtual bool IsPrint() const final;
			virtual bool IsControl() const final;
			virtual bool IsHexadecimal() const final;
			virtual Char ToLower() const final;
			virtual Char ToUpper() const final;
			Char& operator=(char);
			Char& operator=(const Char&);
			Char operator+(const Char&) const;
			Char operator-(const Char&) const;
			Char& operator+=(int);
			Char& operator-=(int);
			Char& operator++();
			Char& operator--();
			bool operator==(const Char&) const;
			bool operator!=(const Char&) const;
		public:
			static const int MaxValue;
			static const int MinValue;
#if defined(LUPUS_WINDOWS_PLATFORM)
		public:
			Char(wchar_t);
			virtual wchar_t Value() const final;
			Char& operator=(wchar_t);
		private:
			wchar_t mValue;
#elif defined(LUPUS_UNIX_PLATFORM)
		public:
			virtual char Value() const final;
		private:
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
