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
		String::String(const wchar_t* source) :
			_data(nullptr)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			size_t length = wcslen(source);
			int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, source, length, NULL, 0, NULL, NULL);

			if (size <= 0) {
				throw EncodingException("invalid string encoding");
			}

			// set internal buffer
			_data = new char[size + 1];

			if (size != WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, source, length, _data, size, NULL, NULL)) {
				throw EncodingException("couldn't convert all characters");
			}

			// set internal buffer
			_data[length] = 0;
			_length = _capacity = length;
		}

		String::String(const wchar_t* source, int startIndex, int length) :
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

			// variables
			int size = WideCharToMultiByte(CP_UTF8, 0, source + startIndex, length, NULL, 0, NULL, NULL);

			if (size <= 0) {
				throw EncodingException("invalid string encoding");
			}

			// set internal buffer
			_data = new char[size + 1];

			if (size != WideCharToMultiByte(CP_UTF8, 0, source + startIndex, length, _data, size, NULL, NULL)) {
				throw EncodingException("couldn't convert all characters");
			}

			// set internal buffer
			_data[length] = 0;
			_length = _capacity = length;
		}
	}
}

#endif
