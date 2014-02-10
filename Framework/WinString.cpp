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

#ifdef LUPUS_WINDOWS_PLATFORM
#include "Char.hpp"
#include "Exception.hpp"
#include <Windows.h>
#include <cwchar>

namespace lupus {
	namespace system {
		String::String(const char* source)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			int length = MultiByteToWideChar(CP_UTF8, 0, source, -1, nullptr, 0);
			wchar_t* converted = new wchar_t[length];
			mData = new Char[length];
			memset(converted, 0, sizeof(wchar_t) * length);

			// convert source string
			if (!MultiByteToWideChar(CP_UTF8, 0, source, -1, converted, length)) {
				throw FormatException("couldn't convert source string to (wchar_t*) format");
			}

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = converted[i];
			}

			mData[length - 1] = 0;
			mLength = mCapacity = (length - 1);
			delete converted;
		}

		String::String(const char* source, int startIndex, int length)
		{
			// check source string
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			}

			// variables
			{
				// check other arguments
				size_t sourceLength = strlen(source);

				if ((startIndex + length) > static_cast<int>(sourceLength)) {
					throw ArgumentOutOfRangeException("startIndex plus length exceeds source length");
				}
			}

			// variables
			int allocSize = MultiByteToWideChar(CP_UTF8, 0, source + startIndex, length, nullptr, 0);
			wchar_t* converted = new wchar_t[allocSize];
			memset(converted, 0, sizeof(wchar_t)* allocSize);
			mData = new Char[length + 1];

			// convert source string
			if (!MultiByteToWideChar(CP_UTF8, 0, source + startIndex, length, converted, length)) {
				throw FormatException("couldn't convert source string to (wchar_t*) format");
			}

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = converted[i + startIndex];
			}

			mData[length] = 0;
			mLength = mCapacity = length;
			delete converted;
		}

		String::String(const wchar_t* source)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			size_t length = wcslen(source);

			// set internal buffer
			mData = new Char[length + 1];

			for (size_t i = 0; i < length; i++) {
				mData[i] = source[i];
			}

			mData[length] = 0;
			mLength = mCapacity = length;
		}

		String::String(const wchar_t* source, int startIndex, int length)
		{
			// check source string
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			}

			// variables
			int limit = startIndex + length;
			{
				// check other arguments
				size_t sourceLength = wcslen(source);

				if (limit > static_cast<int>(sourceLength)) {
					throw ArgumentOutOfRangeException("startIndex plus length exceeds source length");
				}
			}

			// set internal buffer
			mData = new Char[length + 1];

			for (int i = 0; i < length; i++) {
				mData[i] = source[i + startIndex];
			}

			mData[length] = 0;
			mLength = mCapacity = length;
		}
	}
}

#endif
