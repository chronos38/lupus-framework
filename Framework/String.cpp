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
			UErrorCode status = U_ZERO_ERROR;
			mConverter = ucnv_open(nullptr, &status);
			mData[0] = 0;
			
			if (!mConverter || U_FAILURE(status)) {
				throw NullPointerException("couldn't create unicode converter");
			}
		}

		String::String(const char* source)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("argument string must have a valid value");
			}

			// variables
			size_t sourceLength = strlen(source);
			int32_t resultLength = 0;
			UChar* destination = nullptr;
			UErrorCode status = U_ZERO_ERROR;
			mConverter = ucnv_open(nullptr, &status);

			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if (!mConverter || U_FAILURE(status)) {
				throw NullPointerException("couldn't create unicode converter");
			}

			// create buffer
			destination = new UChar[sourceLength];
			mData = new Char[sourceLength];

			// read unicode characters
			resultLength = ucnv_toUChars(mConverter, destination, sourceLength, source, sourceLength, &status);

			if (static_cast<size_t>(resultLength) != sourceLength || U_FAILURE(status)) {
				throw BufferOverflowException("resulting string length is unequal to requested string length");
			}

			// set internal buffer
			for (size_t i = 0; i < sourceLength; i++) {
				mData[i] = destination[i];
			}

			// terminate with zero and free not needed memory
			mData[resultLength] = 0;
			delete destination;
		}

		String::String(const char* source, int startIndex, int length)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("argument string must have a valid value");
			} else if (length < 0) {
				throw ArgumentOutOfRangeException("length must be minus one or greater than zero");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex is less than zero");
			} else if (startIndex >= length) {
				throw ArgumentOutOfRangeException("startIndex is equal to or greater than length");
			}

			// variables
			size_t sourceLength = strlen(source);
			int32_t resultLength = 0;
			UChar* destination = nullptr;
			UErrorCode status = U_ZERO_ERROR;
			mConverter = ucnv_open(nullptr, &status);
			
			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if (static_cast<size_t>(length) > sourceLength) {
				throw ArgumentOutOfRangeException("length exceeds actual string length");
			} else if (static_cast<size_t>(startIndex) >= sourceLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds actual string length");
			} else if (!mConverter || U_FAILURE(status)) {
				throw NullPointerException("couldn't create unicode converter");
			}

			// create buffer
			destination = new UChar[length];
			mData = new Char[length];

			// read unicode characters
			resultLength = ucnv_toUChars(mConverter, destination, length, source + startIndex, length, &status);

			if (static_cast<int>(resultLength) != length || U_FAILURE(status)) {
				throw BufferOverflowException("resulting string length is unequal to requested string length");
			}

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = destination[i];
			}

			// terminate with zero and free not needed memory
			mData[resultLength] = 0;
			delete destination;
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
			if (mConverter) {
				ucnv_close(mConverter);
			}
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