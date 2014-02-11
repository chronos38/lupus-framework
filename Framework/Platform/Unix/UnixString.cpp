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

#include "String.hpp"

#ifdef LUPUS_UNIX_PLATFORM
#include "Char.hpp"
#include "Exception.hpp"
#include <Windows.h>
#include <cwchar>

namespace Lupus {
	namespace System {
		String::String(const char* source)
		{
			// check argument
			if (!source) {
				throw ArgumentNullException("source string must have a valid value");
			}

			// variables
			int length = static_cast<int>(strlen(source));
			mData = new Char[length + 1];

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = source[i];
			}

			mData[length] = 0;
			mLength = mCapacity = length;
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
			mData = new Char[length + 1];

			{
				// check other arguments
				size_t sourceLength = strlen(source);

				if ((startIndex + length) > static_cast<int>(sourceLength)) {
					throw ArgumentOutOfRangeException("startIndex plus length exceeds source length");
				}
			}

			// set internal buffer
			for (int i = 0; i < length; i++) {
				mData[i] = source[i + startIndex];
			}

			mData[length] = 0;
			mLength = mCapacity = length;
			delete converted;
		}
	}
}

#endif
