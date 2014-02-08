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

#include "String.hpp"
#include "Char.hpp"
#include "Exception.hpp"
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/ucnv.h>

namespace lupus {
	namespace system {
		String::String() :
			mData(new Char[1])
		{
		}

		String::String(const char* str, int startIndex, int length)
		{
			// check arguments
			if (!str) {
				throw ArgumentNullException("argument string must have a valid value");
			}

			// variables
			UChar* destination = nullptr;
			UErrorCode status = U_ZERO_ERROR;
			UConverter* converter = ucnv_open(nullptr, &status);

			// check for errors
			if (!converter || U_FAILURE(status)) {
				throw NullPointerException("couldn't create unicode converter");
			}

			// conversion
			if (!length) {
			} else if (length < 0) {
			} else {
			}
		}

		String::String(const Char* str, int startIndex, int length)
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