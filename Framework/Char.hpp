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

namespace lupus {
	namespace system {
		/// Represents a unicode character
		class LUPUS_API Char : public Object
		{
		public:
			Char();
			Char(char);
			Char(wchar_t);
			Char(short);
			Char(ushort);
			Char(int);
			Char(uint);
			bool IsBlank() const;
			bool IsDigit() const;
			bool IsGraph() const;
			bool IsLetter() const;
			bool IsLetterOrDigit() const;
			bool IsLower() const;
			bool IsPunct() const;
			bool IsTitle() const;
			bool IsUpper() const;
			bool IsWhiteSpace() const;
			Char ToLower() const;
			Char ToUpper() const;
			Char ToTitle() const;
			ushort Unicode() const;
		private:
			ushort mValue;
		};

		template <typename T>
		bool operator==(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator==(const T& lhs, const Char& rhs);

		template <typename T>
		bool operator!=(const Char& lhs, const T& rhs);
		template <typename T>
		bool operator!=(const T& lhs, const Char& rhs);
	}
}

#include "Char.inl"

#endif
