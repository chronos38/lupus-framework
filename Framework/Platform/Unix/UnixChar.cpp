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

#ifdef LUPUS_UNIX_PLATFORM
#include "Integer.hpp"
#include "Exception.hpp"
#include <climits>
#include <cctype>

namespace Lupus {
	namespace System {
		const int Char::MaxValue = CHAR_MAX;
		const int Char::MinValue = CHAR_MIN;

		Char::Char(int ch) :
			mValue(static_cast<char>(ch))
		{
		}

		bool Char::IsBlank() const
		{
			return (isblank(mValue) != 0);
		}

		bool Char::IsDigit() const
		{
			return (isdigit(mValue) != 0);
		}

		bool Char::IsGraph() const
		{
			return (isgraph(mValue) != 0);
		}

		bool Char::IsLetter() const
		{
			return (isalpha(mValue) != 0);
		}

		bool Char::IsLetterOrDigit() const
		{
			return (isalnum(mValue) != 0);
		}

		bool Char::IsLower() const
		{
			return (islower(mValue) != 0);
		}

		bool Char::IsPunct() const
		{
			return (ispunct(mValue) != 0);
		}

		bool Char::IsUpper() const
		{
			return (isupper(mValue) != 0);
		}

		bool Char::IsSpace() const
		{
			return (isspace(mValue) != 0);
		}

		bool Char::IsPrint() const
		{
			return (isprint(mValue) != 0);
		}

		bool Char::IsControl() const
		{
			return (iscntrl(mValue) != 0);
		}

		bool Char::IsHexadecimal() const
		{
			return (isxdigit(mValue) != 0);
		}

		Char Char::ToLower() const
		{
			return (tolower(mValue));
		}

		Char Char::ToUpper() const
		{
			return (toupper(mValue));
		}
	}
}

#endif
