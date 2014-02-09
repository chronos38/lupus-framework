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
			InitializeConverter();
			mData[0] = 0;
		}

		String::String(const char* source)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
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
			mData = new Char[sourceLength + 1];

			// read unicode characters
			resultLength = ucnv_toUChars(mConverter, destination, sourceLength, source, sourceLength, &status);

			if (static_cast<size_t>(resultLength) != sourceLength || U_FAILURE(status)) {
				throw BufferOverflowException("resulting string length is unequal to requested string length");
			}

			// set internal buffer
			for (int32_t i = 0; i < resultLength; i++) {
				mData[i] = destination[i];
			}

			// terminate with zero and free not needed memory
			mData[resultLength] = 0;
			mLength = static_cast<uint>(resultLength);
			delete destination;
		}

		String::String(const Char* source)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");;
			}

			// initialize converter
			InitializeConverter();

			// variables
			uint length = GetLength(source);

			// in case the string is empty, apply it now
			if (!length) {
				*this = String();
				return;
			}

			// set values
			mData = new Char[length + 1];
			memcpy(mData, source, sizeof(Char) * length);
			mData[length] = 0;
			mLength = length;
		}

		String::String(const char* source, int startIndex, int length)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
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
			mData = new Char[length + 1];

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
			mData[length] = 0;
			mLength = static_cast<uint>(length);
			delete destination;
		}

		String::String(const Char* source, int startIndex, int length)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (length < 0) {
				throw ArgumentOutOfRangeException("length must be minus one or greater than zero");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex is less than zero");
			} else if (startIndex >= length) {
				throw ArgumentOutOfRangeException("startIndex is equal to or greater than length");
			}

			// initialize converter
			InitializeConverter();

			// variables
			size_t sourceLength = GetLength(source);

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
			}

			// create buffer
			mData = new Char[length + 1];

			// set internal buffer
			memcpy(mData, source + startIndex, sizeof(Char) * length);

			// terminate with zero and free not needed memory
			mData[length] = 0;
			mLength = static_cast<uint>(length);
		}

		String::String(const String& string) :
			mData(new Char[string.Length() + 1]),
			mLength(string.Length())
		{
			// initialize converter
			InitializeConverter();

			// set variables
			memcpy(mData, string.Data(), sizeof(Char) * mLength);
			mData[mLength] = 0;
		}

		String::String(String&& string) :
			String()
		{
			// initialize converter
			InitializeConverter();

			// variables
			Char* swapData = mData;
			uint swapLength = mLength;
			UConverter* swapConverter = mConverter;

			// swap memory
			mData = string.mData;
			mLength = string.mLength;
			mConverter = string.mConverter;

			string.mData = swapData;
			string.mLength = swapLength;
			string.mConverter = mConverter;
		}

		String::~String()
		{
			if (mConverter) {
				ucnv_close(mConverter);
			}

			if (mData) {
				delete mData;
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

		uint String::Length() const
		{
			return mLength;
		}

		Char& String::operator[](uint index)
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string size");
			}

			return mData[index];
		}

		const Char& String::operator[](uint index) const
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string size");
			}

			return mData[index];
		}

		String& String::operator=(const Char* string)
		{
			// variables 
			uint length = GetLength(string);

			// reallocate buffer
			delete mData;
			mData = new Char[length + 1];

			// set new values
			memcpy(mData, string, sizeof(Char) * length);
			mData[length] = 0;
			mLength = length;

			return (*this);
		}

		String& String::operator=(const String& string)
		{
			// variables 
			uint length = string.Length();

			// reallocate buffer
			delete mData;
			mData = new Char[length + 1];

			// set new values
			memcpy(mData, string.Data(), sizeof(Char)* length);
			mData[length] = 0;
			mLength = length;

			return (*this);
		}

		String& String::operator=(String&& string)
		{
			// variables
			String tmp;

			// move memory
			mData = string.mData;
			mLength = string.mLength;
			mConverter = string.mConverter;

			string.mData = tmp.mData;
			string.mLength = tmp.mLength;
			string.mConverter = tmp.mConverter;

			return (*this);
		}

		String String::operator+(const String& string)
		{
			// variables
			String result;
			Char* buffer = new Char[mLength + string.Length() + 1];

			// copy new buffer
			memcpy(buffer, mData, sizeof(Char) * mLength);
			memcpy(buffer + mLength, string.Data(), sizeof(Char) * string.Length());
			buffer[mLength + string.Length()] = 0;

			// set result and delete buffer
			result = buffer;
			delete buffer;

			return result;
		}

		String& String::operator+=(const String& string)
		{
			// variables
			Char* buffer = new Char[mLength * string.Length() + 1];

			// copy new buffer
			memcpy(buffer, mData, sizeof(Char) * mLength);
			memcpy(buffer + mLength, string.Data(), sizeof(Char) * string.Length());
			buffer[mLength + string.Length()] = 0;

			// set result and delete buffer
			*this = buffer;
			delete buffer;

			return (*this);
		}

		uint String::GetLength(const Char* string)
		{
			uint result = 0;

			for (const Char* ch = string; (*ch) != 0; ch++) {
				result++;
			}

			return result;
		}

		void String::InitializeConverter()
		{
			UErrorCode status = U_ZERO_ERROR;
			mConverter = ucnv_open(nullptr, &status);

			if (!mConverter || U_FAILURE(status)) {
				throw NullPointerException("couldn't create unicode converter");
			}
		}
	}
}