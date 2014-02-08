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

#ifndef LUPUS_STRING_HPP
#define LUPUS_STRING_HPP

#include "Object.hpp"

namespace lupus {
	namespace system {
		// forwared declaration for char class
		class Char;

		/// String class used for internal string operations
		class LUPUS_API String : public Object
		{
		public:
			String();
			String(const char*, int startIndex = 0, int length = -1);
			String(const Char*, int startIndex = 0, int length = -1);
			String(const String&);
			String(String&&);
			virtual ~String();
			Char* Data();
			const Char* Data() const;
			String& operator=(const char*);
			String& operator=(const Char*);
			String& operator=(const String&);
			String& operator=(String&&);
			String operator+(const String&);
		private:
			Char* mData = nullptr;
			uint mLength = 0;
		};

		template <typename CharT>
		String operator+(const CharT* lhs, const String& rhs);

		template <typename CharT>
		String operator+(const String& lhs, const CharT* rhs);
	}
}

#include "String.inl"

#endif
