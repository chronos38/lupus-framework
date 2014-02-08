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
#include "Integer.hpp"
#include "Exception.hpp"
#include <unicode/utypes.h>
#include <unicode/ucnv.h>

namespace lupus {
	namespace system {
		Char::Char()
		{
			UErrorCode status = U_ZERO_ERROR;
			mConverter = ucnv_open(nullptr, &status);

			if (!mConverter) {
				throw OutOfMemoryException("couldn't allocate memory for unicode converter");
			} else if (U_FAILURE(status)) {
				throw Exception("error: " + Integer::ToString(status));
				// TODO: add exceptions
			}


		}

		Char::Char(char ch)
		{
		}

		Char::Char(wchar_t wc)
		{
		}
	}
}
