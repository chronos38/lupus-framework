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

#include "Char.hpp"
#include "String.hpp"

namespace lupus {
	namespace system {
		String::String()
		{
		}

		String::String(const char* str, int startIndex, int length)
		{
		}

		String::String(const wchar_t* wcs, int startIndex, int length)
		{
		}

		String::String(const String& string)
		{
		}

		String::String(String&& string)
		{
		}

		String::~String()
		{
		}

		Char* String::Data()
		{
			return mData;
		}

		const Char* String::Data() const
		{
			return mData;
		}

		String& String::operator=(Char ch)
		{
			return (*this);
		}

		String& String::operator=(const Char* str)
		{
			return (*this);
		}

		String& String::operator=(const String& string)
		{
			return (*this);
		}

		String& String::operator=(String&& string)
		{
			return (*this);
		}

		String String::operator+(const String& string)
		{
			String result;
			return result;
		}
	}
}