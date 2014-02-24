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

#include "..\..\Char.hpp"

#ifdef LUPUS_WINDOWS_PLATFORM
#include "..\..\String.hpp"
#include "..\..\Integer.hpp"
#include "..\..\Exception.hpp"
#include <cwchar>
#include <cwctype>

namespace Lupus {
	namespace System {
		const int Char::MaxValue = WCHAR_MAX;
		const int Char::MinValue = WCHAR_MIN;

		Char::Char(char ch) :
			Object(),
			mValue(0)
		{
			if (ch == '\0') {
				return;
			}

			mbstate_t state = mbstate_t();

			if (mbrtowc(&mValue, &ch, sizeof(ch), &state) != sizeof(ch)) {
				throw FormatException("couldn't convert character to wide character");
			}
		}

		Char::Char(wchar_t ch) :
			Object(),
			mValue(ch)
		{
		}

		Char& Char::operator=(char ch)
		{
			if (ch == '\0') {
				mValue = L'\0';
				return (*this);
			}

			mbstate_t state = mbstate_t();

			if (mbrtowc(&mValue, &ch, sizeof(ch), &state) != sizeof(ch)) {
				throw FormatException("couldn't convert character to wide character");
			}

			return (*this);
		}

		Char& Char::operator=(wchar_t wc)
		{
			mValue = wc;
			return (*this);
		}
	}
}

#endif
