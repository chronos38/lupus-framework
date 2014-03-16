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

#include "..\..\String.hpp"

#ifdef LUPUS_WINDOWS_PLATFORM
#include "..\..\Char.hpp"
#include "..\..\Exception.hpp"
#include <Windows.h>
#include <cwchar>

namespace Lupus {
	namespace System {
		String::String(const char* source) :
			Object(),
			_data(nullptr)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			int length = MultiByteToWideChar(CP_UTF8, 0, source, -1, nullptr, 0);
			_data = new wchar_t[length];
			wmemset(_data, 0, length);

			// convert source string
			if (!MultiByteToWideChar(CP_UTF8, 0, source, -1, _data, length)) {
				throw FormatException("couldn't convert source string to (wchar_t*) format");
			}

			_data[length - 1] = L'\0';
			_length = _capacity = (length - 1);
		}

		String::String(const char* source, int startIndex, int length) :
			Object(),
			_data(nullptr)
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
			MultiByteToWideChar(CP_UTF8, 0, source + startIndex, length, nullptr, 0);
			_data = new wchar_t[length + 1];
			wmemset(_data, 0, length + 1);

			// convert source string
			if (!MultiByteToWideChar(CP_UTF8, 0, source + startIndex, length, _data, length)) {
				throw FormatException("couldn't convert source string to (wchar_t*) format");
			}

			_data[length] = L'\0';
			_length = _capacity = length;
		}

		String::String(const wchar_t* source) :
			Object(),
			_data(nullptr)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			size_t length = wcslen(source);

			// set internal buffer
			_data = new wchar_t[length + 1];
			wmemcpy(_data, source, length);
			_data[length] = L'\0';
			_length = _capacity = length;
		}

		String::String(const wchar_t* source, int startIndex, int length) :
			Object(),
			_data(nullptr)
		{
			// check source string
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			} else if (startIndex < 0) {
				throw ArgumentOutOfRangeException("startIndex must be greater than or equal to zero");
			} else if (length <= 0) {
				throw ArgumentOutOfRangeException("length must be greater than zero");
			} else if ((startIndex + length) > static_cast<int>(wcslen(source))) {
				throw ArgumentOutOfRangeException("startIndex plus length exceeds source length");
			}

			// set internal buffer
			_data = new wchar_t[length + 1];
			wmemcpy(_data, source + startIndex, length);
			_data[length] = L'\0';
			_length = _capacity = length;
		}

		Char& String::RefChar::operator=(char ch)
		{
			if (ch == '\0') {
				(*mRef) = L'\0';
				return (*this);
			}

			mbstate_t state = mbstate_t();

			if (mbrtowc(mRef, &ch, sizeof(ch), &state) != sizeof(ch)) {
				throw FormatException("couldn't convert character to wide character");
			}

			return (*this);
		}

		Char& String::RefChar::operator=(wchar_t wc)
		{
			(*mRef) = wc;
			return (*this);
		}
	}
}

#endif
