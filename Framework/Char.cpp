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
#include <unicode/uchar.h>
#include <climits>

namespace lupus {
	namespace system {
		Char::Char() :
			mValue(0)
		{
		}

		Char::Char(char ch) :
			mValue(ch)
		{
		}

		Char::Char(wchar_t ch) :
			mValue(ch)
		{
		}

		Char::Char(ushort ch) :
			mValue(ch)
		{
		}

		Char::Char(uint ch) :
			mValue(ch)
		{
		}

		bool Char::IsBlank() const
		{
			return (u_isblank(mValue) == TRUE);
		}

		bool Char::IsDigit() const
		{
			return (u_isdigit(mValue) == TRUE);
		}

		bool Char::IsGraph() const
		{
			return (u_isgraph(mValue) == TRUE);
		}

		bool Char::IsLetter() const
		{
			return (u_isalpha(mValue) == TRUE);
		}

		bool Char::IsLetterOrDigit() const
		{
			return (IsLetter() || IsDigit());
		}

		bool Char::IsLower() const
		{
			return (u_islower(mValue) == TRUE);
		}

		bool Char::IsPunct() const
		{
			return (u_ispunct(mValue) == TRUE);
		}

		bool Char::IsTitle() const
		{
			return (u_istitle(mValue) == TRUE);
		}

		bool Char::IsUpper() const
		{
			return (u_isupper(mValue) == TRUE);
		}

		bool Char::IsWhiteSpace() const
		{
			return (u_isWhitespace(mValue) == TRUE);
		}

		Char Char::ToLower() const
		{
			return static_cast<uint>(u_tolower(mValue));
		}

		Char Char::ToUpper() const
		{
			return static_cast<uint>(u_toupper(mValue));
		}

		Char Char::ToTitle() const
		{
			return static_cast<uint>(u_totitle(mValue));
		}
	}
}
