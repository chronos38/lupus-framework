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
			mData(new Char[1]),
			mLength(0),
			mCapacity(0)
		{
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
			const char* sourceLimit = source + sourceLength;
			Char* iterator = nullptr;
			UChar32 target = 0;
			UErrorCode status = U_ZERO_ERROR;
			UConverter* converter = ucnv_open(nullptr, &status);

			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if (U_FAILURE(status)) {
				throw NullPointerException(u_errorName(status));
			}

			// create buffer and set iterator
			mData = new Char[sourceLength + 1];
			iterator = mData;

			// read unicode characters
			while (source < sourceLimit) {
				target = ucnv_getNextUChar(converter, &source, sourceLimit, &status);

				if (U_FAILURE(status)) {
					throw FormatException(u_errorName(status));
				}

				// save unicode char and increment iterator
				*iterator = target;
				iterator++;
			}

			// terminate with zero and set length
			mData[sourceLength] = 0;
			mLength = mCapacity = static_cast<int>(sourceLength);
		}

		String::String(const Char* source)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");;
			}

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
			mLength = mCapacity = length;
		}

		String::String(const char* source, int startIndex, int length)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex is less than zero");
			}

			// variables
			size_t sourceLength = strlen(source);
			const char* sourceString = source + startIndex;
			const char* sourceLimit = source + startIndex + length;
			Char* iterator = nullptr;
			UChar32 target = 0;
			UErrorCode status = U_ZERO_ERROR;
			UConverter* converter = ucnv_open(nullptr, &status);
			
			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if (static_cast<size_t>(startIndex + length) > sourceLength) {
				throw ArgumentOutOfRangeException("length exceeds actual string length");
			} else if (U_FAILURE(status)) {
				throw NullPointerException(u_errorName(status));
			}

			// create buffer and set iterator
			mData = new Char[length + 1];
			iterator = mData;

			// read unicode characters
			while (sourceString < sourceLimit) {
				target = ucnv_getNextUChar(converter, &sourceString, sourceLimit, &status);

				if (U_FAILURE(status)) {
					throw FormatException(u_errorName(status));
				}

				// save unicode char and increment iterator
				*iterator = target;
				iterator++;
			}

			// terminate with zero and free not needed memory
			mData[length] = 0;
			mLength = mCapacity = static_cast<int>(length);
		}

		String::String(const Char* source, int startIndex, int length)
		{
			// check arguments
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex is less than zero");
			}

			// variables
			size_t sourceLength = GetLength(source);

			// in case the string is empty, apply it now
			if (!sourceLength) {
				*this = String();
				return;
			}

			// check for errors
			if (static_cast<size_t>(startIndex + length) > sourceLength) {
				throw ArgumentOutOfRangeException("length exceeds actual string length");
			}

			// create buffer
			mData = new Char[length + 1];

			// set internal buffer
			memcpy(mData, source + startIndex, sizeof(Char) * length);

			// terminate with zero and free not needed memory
			mData[length] = 0;
			mLength = mCapacity = static_cast<int>(length);
		}

		String::String(const String& string) :
			mData(new Char[string.Capacity() + 1]),
			mLength(string.Length()),
			mCapacity(string.Capacity())
		{
			// set variables
			if (mCapacity > mLength) {
				memset(mData + mLength, 0, sizeof(Char)* (mCapacity - mLength));
			}

			memcpy(mData, string.Data(), sizeof(Char) * mLength);
			mData[mLength] = 0;
		}

		String::String(String&& string) :
			String()
		{
			// variables
			Char* swapData = mData;
			int swapLength = mLength;
			int swapCapacity = mCapacity;

			// swap memory
			mData = string.mData;
			mLength = string.mLength;
			mCapacity = string.mCapacity;

			string.mData = swapData;
			string.mLength = swapLength;
			string.mCapacity = swapCapacity;
		}

		String::~String()
		{
			if (mData) {
				delete mData;
			}
		}

		String& String::Append(const String& string)
		{
			return ((*this) += string);
		}

		int String::Capacity() const
		{
			return mCapacity;
		}

		int String::Compare(const String& string, CaseSensitivity sensitivity) const
		{
			// check length
			if (mLength != string.Length()) {
				return (static_cast<int>(mLength) - static_cast<int>(string.Length()));
			}

			// variables
			const Char* data = string.Data();

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i] != data[i]) {
						return (mData[i] - data[i]).Unicode();
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i].ToLower() != data[i].ToLower()) {
						return (mData[i] - data[i]).Unicode();
					}
				}
				break;
			}

			return 0;
		}

		bool String::Contains(const String& string, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (string == "") {
				return true;
			} else if (mLength < string.Length()) {
				return false;
			} else if (mLength == string.Length()) {
				return (Compare(string, sensitivity) == 0);
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return (KnuthMorrisPrattSensitive(mData, mLength, string.Data(), string.Length()) != -1);
			case CaseSensitivity::CaseInsensitive:
				return (KnuthMorrisPrattInsensitive(mData, mLength, string.Data(), string.Length()) != -1);
			}
		}

		/*
		void String::CopyTo(uint sourceIndex, Char* destination, uint destinationIndex, uint count) const
		{
		}
		*/

		Char* String::Data()
		{
			return mData;
		}

		const Char* String::Data() const
		{
			return mData;
		}

		int String::IndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
				throw ArgumentOutOfRangeException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i].ToLower() == lower) {
						return i;
					}
				}
				break;
			}

			return -1;
		}

		int String::IndexOf(const String& string, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPrattSensitive(mData + startIndex, mLength - startIndex, string.Data(), string.Length());
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitive(mData + startIndex, mLength - startIndex, string.Data(), string.Length());
			}
		}

		/*
		int String::IndexOfAny(const Array<Char>& sequence, uint startIndex, CaseSensitivity sensitivity) const
		{
		}
		*/

		bool String::IsEmpty() const
		{
			return (mData[0] == 0);
		}

		int String::LastIndexOf(const Char& ch, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if ((mLength - startIndex) < 0) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// variables
			Char lower = ch.ToLower();

			// comput result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = (mLength - startIndex); i >= 0; i--) {
					if (mData[i] == ch) {
						return i;
					}
				}
				break;
			case CaseSensitivity::CaseInsensitive:
				for (int i = (mLength - startIndex); i >= 0; i--) {
					if (mData[i].ToLower() == lower) {
						return i;
					}
				}
				break;
			}

			return -1;
		}

		int String::LastIndexOf(const String& string, int startIndex, CaseSensitivity sensitivity) const
		{
			// check arguments
			if (startIndex >= mLength) {
				throw ArgumentNullException("startIndex exceeds string length");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than zero");
			}

			// compute result
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				return KnuthMorrisPrattSensitiveLast(mData + startIndex, mLength - startIndex, string.Data(), string.Length());
			case CaseSensitivity::CaseInsensitive:
				return KnuthMorrisPrattInsensitiveLast(mData + startIndex, mLength - startIndex, string.Data(), string.Length());
			}
		}

		int String::Length() const
		{
			return mLength;
		}

		String& String::Remove(int startIndex)
		{
			throw NotImplementedException();
		}

		String& String::Remove(int startIndex, int count)
		{
			throw NotImplementedException();
		}

		String& String::Replace(const Char& before, const Char& after, CaseSensitivity sensitivity)
		{
			switch (sensitivity) {
			case CaseSensitivity::CaseSensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i] == before) {
						mData[i] = after;
					}
				}
			case CaseSensitivity::CaseInsensitive:
				for (int i = 0; i < mLength; i++) {
					if (mData[i].ToLower() == before.ToLower()) {
						mData[i] = after;
					}
				}
			}

			return (*this);
		}

		String& String::Replace(const String& before, const String& after, CaseSensitivity sensitivity)
		{
			throw NotImplementedException();
		}

		Char& String::operator[](uint index)
		{
			if (index >= static_cast<uint>(mLength)) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			}

			return mData[index];
		}

		const Char& String::operator[](uint index) const
		{
			if (index >= static_cast<uint>(mLength)) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			}

			return mData[index];
		}

		Char& String::operator[](int index)
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return mData[index];
		}

		const Char& String::operator[](int index) const
		{
			if (index >= mLength) {
				throw ArgumentOutOfRangeException("index exceeds string length");
			} else if (index < 0) {
				throw ArgumentOutOfRangeException("index must be greater than zero");
			}

			return mData[index];
		}

		String& String::operator=(const Char* string)
		{
			// check argument
			if (!string) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables 
			int length = GetLength(string);

			// check if capacity is big enough
			if (mCapacity >= length) {
				// reset buffer
				memset(mData, 0, sizeof(Char) * mCapacity);

				// set new values
				memcpy(mData, string, sizeof(Char)* length);
				mData[length] = 0;
				mLength = length;
			} else {
				// reallocate buffer
				delete mData;
				mData = new Char[length + 1];

				// set new values
				memcpy(mData, string, sizeof(Char) * length);
				mData[length] = 0;
				mLength = mCapacity = length;
			}

			return (*this);
		}

		String& String::operator=(const String& string)
		{
			// variables 
			int length = string.Length();

			// check if capacity is big enough
			if (mCapacity >= length) {
				// reset buffer
				memset(mData, 0, sizeof(Char) * mCapacity);

				// set new values
				memcpy(mData, string.Data(), sizeof(Char) * length);
				mData[length] = 0;
				mLength = length;
			} else {
				// reallocate buffer
				delete mData;
				mData = new Char[length + 1];

				// set new values
				memcpy(mData, string.Data(), sizeof(Char) * length);
				mData[length] = 0;
				mLength = mCapacity = length;
			}

			return (*this);
		}

		String& String::operator=(String&& string)
		{
			// variables
			String tmp;

			// delete current buffer
			delete mData;

			// move memory
			mData = string.mData;
			mLength = string.mLength;
			mCapacity = string.mCapacity;

			string.mData = tmp.mData;
			string.mLength = tmp.mLength;
			string.mCapacity = tmp.mCapacity;

			return (*this);
		}

		String String::operator+(const String& string) const
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
			int length = string.Length();

			// check if capacity is big enough
			if (mCapacity >= length) {
				memcpy(mData + mLength, string.Data(), sizeof(Char) * length);
				mLength += length;
			} else {
				// new buffer
				Char* buffer = new Char[mLength * string.Length() + 1];
				
				// copy new buffer
				memcpy(buffer, mData, sizeof(Char) * mLength);
				memcpy(buffer + mLength, string.Data(), sizeof(Char) * length);
				buffer[mLength + length] = 0;

				// set result and delete buffer
				*this = buffer;
				delete buffer;
			}

			return (*this);
		}

		bool String::operator==(const String& string) const
		{
			return (this->Compare(string) == 0);
		}

		bool String::operator!=(const String& string) const
		{
			return (this->Compare(string) != 0);
		}

		int String::GetLength(const Char* string)
		{
			int result = 0;

			for (const Char* ch = string; (*ch) != 0; ch++) {
				result++;
			}

			return result;
		}

		int String::KnuthMorrisPrattSensitive(const Char* text, int textLength, const Char* search, int searchLength)
		{
			// variables
			int* n = new int[searchLength];
			int i = 0;
			int j = -1;

			// create prefix
			while (i < searchLength) {
				while (j >= 0 && search[i] != search[j]) {
					j = n[j];
				}
				i++;
				j++;
				n[i] = j;
			}

			// reset variables
			i = j = 0;

			// search
			while (i < textLength) {
				while (j >= 0 && text[i] != search[j]) {
					j = n[j];
				}
				i++;
				j++;

				if (j == searchLength) {
					delete n;
					return (i - j);
				}
			}

			delete n;
			return -1;
		}

		int String::KnuthMorrisPrattInsensitive(const Char* text, int textLength, const Char* search, int searchLength)
		{
			// variables
			int* n = new int[searchLength];
			int i = 0;
			int j = -1;

			// create prefix
			while (i < searchLength) {
				while (j >= 0 && search[i].ToLower() != search[j].ToLower()) {
					j = n[j];
				}
				i++;
				j++;
				n[i] = j;
			}

			// reset variables
			i = j = 0;

			// search
			while (i < textLength) {
				while (j >= 0 && text[i].ToLower() != search[j].ToLower()) {
					j = n[j];
				}
				i++;
				j++;

				if (j == searchLength) {
					delete n;
					return (i - j);
				}
			}

			delete n;
			return -1;
		}

		int String::KnuthMorrisPrattSensitiveLast(const Char* text, int textLength, const Char* search, int searchLength)
		{
			// TODO: implement reverse search logic
			throw NotImplementedException();
		}

		int String::KnuthMorrisPrattInsensitiveLast(const Char* text, int textLength, const Char* search, int searchLength)
		{
			// TODO: implement reverse search logic
			throw NotImplementedException();
		}
	}
}
