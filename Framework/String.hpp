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
		class Char;

		class LUPUS_API String : public Object
		{
		public:
			String();
			String(const char*, int startIndex = 0, int length = -1);
			String(const wchar_t*, int startIndex = 0, int length = -1);
			String(const Char*, int startIndex = 0, int length = -1);
			String(const String&);
			String(String&&);
			virtual ~String();
			Char* Data();
			const Char* Data() const;
		private:
			Char* mData;
			uint mLength;
		};
	}
}

#endif
